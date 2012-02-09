/**
@file SteeringMovement.cpp

Contiene la declaraci�n de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cin�ticos o din�micos.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#include "SteeringMovement.h"

#include "Map/MapEntity.h"

#include "AI/Movement.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/AvatarWalk.h"

namespace Logic 
{

	IMP_FACTORY(CSteeringMovement);

	//---------------------------------------------------------
	/**
	Destructor
	*/
	CSteeringMovement::~CSteeringMovement()
	{
		if (_currentMovement != 0)
			delete _currentMovement;
		if (_yaw != 0)
			delete _yaw;
	}

	//---------------------------------------------------------
	/**
	Inicializaci�n del componente, utilizando la informaci�n extra�da de
	la entidad le�da del mapa (Maps::CEntity). Toma del mapa los atributos
	speed, angularSpeed, accel y angularAccel, que indican los valores m�ximos 
	de velocidad y aceleraci�n lineales y angulares. El atributo tolerance indica
	la distancia a la que se considera que se ha alcanzado una posici�n.

	@param entity Entidad a la que pertenece el componente.
	@param map Mapa L�gico en el que se registrar� el objeto.
	@param entityInfo Informaci�n de construcci�n del objeto le�do del
	fichero de disco.
	@return Cierto si la inicializaci�n ha sido satisfactoria.
	*/
	bool CSteeringMovement::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("speed"))
			_maxLinearSpeed = entityInfo->getFloatAttribute("speed");
		if(entityInfo->hasAttribute("angularSpeed"))
			_maxAngularSpeed = entityInfo->getFloatAttribute("angularSpeed");
		if(entityInfo->hasAttribute("accel"))
			_maxLinearAccel = entityInfo->getFloatAttribute("accel");
		if(entityInfo->hasAttribute("angularAccel"))
			_maxAngularAccel = entityInfo->getFloatAttribute("angularAccel");
		if (entityInfo->hasAttribute("movementTolerance"))
			_tolerance = entityInfo->getFloatAttribute("movementTolerance");

			// En yaw guardamos el movimiento correspondiente a la rotaci�n de la entidad.
			// En este caso suponemos que la entidad siempre se mueve hacia adelante, 
			// as� que hacemos que siempre est� alineado con su vector de velocidad.

		_yaw = AI::IMovement::getMovement(AI::IMovement::MOVEMENT_KINEMATIC_ALIGN_TO_SPEED, 
			_maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel); 
		_yaw->setEntity(entity);

		return true;

	} // spawn

	//---------------------------------------------------------
	/**
	M�todo llamado en cada frame que actualiza el estado del componente.
	<p>
	Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.

	@param msecs Milisegundos transcurridos desde el �ltimo tick.
	*/
	void CSteeringMovement::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// En este m�todo se realiza un movimiento b�sico usando un steering movement
		// El steering movement calcula las velocidades y aceleraciones lineales y angulares y,
		// con esta informaci�n se env�an mensajes a la f�sica, el avatar controller y las animaciones
		
		// Variables �tiles:
		// _maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel: velocidades y aceleraciones lineales y angulares.
		// _tolerance: distancia a la que se considera que se ha llegado al punto de destino.
		// _arrived: �ha llegado al destino?
		// _currentTarget: punto de destino del movimiento actual.
		// _target: nuevo punto de destino que se ha establecido en el m�todo process, pero que a�n no es el actual.
		// _currentMovementType, _movType: lo mismo con el tipo de movimiento. Son valores sacados del enumerado IMovement::EnmMovementType 
		// _currentMovement: instancia de IMovement correspondiente al movimiento actual.
		// _yaw: instancia de IMovement correspondiente al movimiento de giro actual. De momento s�lo hay un posible valor
		//		(MOVEMENT_KINEMATIC_ALIGN_TO_SPEED) que establecemos en el spawn.
		// _currentProperties: esta variable sirve de entrada y de salida para los steering behaviours. En ella se almacena la informaci�n
		//		de velocidad entre los ticks.

		// En cada tick tenemos que:
		// Comprobar si hay que cambiar de movimiento o destino
		//		Si es as�, sacar el nuevo movimiento de la factor�a (puede ser NULL ==> parado)
		//		Asignarle el nuevo destino y la entidad al movimiento
		//		Actualizar la variable _arrived para indicar que no hemos llegado a destino
		//		Si tiene que cambiar la animaci�n notificarlo con un mensaje

		// Comprobamos si hemos llegado al destino
		// Podemos usar positionEquals (IMPORTANTE: usar la _tolerance)
		//		Si es as�, enviar un mensaje FINISHED_MOVE para indicar que hemos llegado

		// Si tenemos que movernos (no hemos llegado al destino y nuestro movimiento no es NULL)
		//		Invocar al m�todo move del movimiento actual. 
		//		Le pasamos la variable _currentProperties, que contiene las velocidades actuales y en la que recogemos las nuevas velocidades y aceleraciones
		//		Calcular la nueva posici�n y notificarla a la f�sica para que nos mueva (mensaje MAvatarWalk)
		//		Actualizar las velocidades usando la aceleraci�n que hemos obtenido en _currentProperties
		//		Las velocidades que tenemos que actualizar tambi�n est�n en _currentProperties para pas�rselas en el siguiente tick al movimiento


		// Comprobamos si hay que cambiar de movimiento o destino
		if (_movType != _currentMovementType || _currentTarget != _target) {
			if (_currentMovement != 0) {
				delete _currentMovement;
			}
			_currentMovementType = _movType;
			_currentTarget = _target;
			_currentMovement = AI::IMovement::getMovement(_currentMovementType, _maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel);
			// Si hay un nuevo movimiento
			if (_currentMovement != 0) {
				// Ajustamos el target
				_arrived = false;
				_currentMovement->setEntity(_entity);
				_currentMovement->setTarget(_currentTarget);
				// Y la animaci�n
				sendAnimationMessage("Walk");
			} else {
				// Si no hay movimiento paramos la animaci�n
				sendAnimationMessage("Idle");
			}
		}

		_arrived = _entity->getPosition().positionEquals(_target, _tolerance);
		/*if (_arrived) {
			// Enviar un mensaje para informar de que hemos llegado a destino
			TMessage message;
			message._type = Message::FINISHED_MOVE;
			message._bool = true;
			_entity->emitMessage(message, this);
		}*/

		// Si nos estamos desplazando calculamos la pr�xima posici�n
		if (!_arrived && _currentMovement != 0) {
	
			_currentMovement->move(msecs, _currentProperties);
			// Calculamos la rotaci�n
			_yaw->move(msecs, _currentProperties);

			// Enviar un mensaje para que el componente f�sico mueva el personaje
			Logic::MAvatarWalk *m = new Logic::MAvatarWalk();
			m->setMovement(_currentProperties.linearSpeed * msecs);
			_entity->emitMessage(m);
			
			// Acelerar
			_currentProperties.linearSpeed += _currentProperties.linearAccel * msecs;
			// Clipping
			double speedValue = _currentProperties.linearSpeed.length();
			if (speedValue > _maxLinearSpeed) {
				_currentProperties.linearSpeed *= (_maxLinearSpeed / speedValue);
			}

			_currentProperties.angularSpeed += _currentProperties.angularAccel * msecs;
			if (_currentProperties.angularSpeed > _maxAngularSpeed) 
				_currentProperties.angularSpeed = Ogre::Math::Sign(_currentProperties.angularSpeed) * _maxAngularSpeed;

		}
		else {
			// Si no hay movimiento paramos la animaci�n
			sendAnimationMessage("Idle");
		}

	} // tick

	//---------------------------------------------------------
	/**
	Env�a un mensaje para cambiar la animaci�n actual.

	@param animation Nueva animaci�n.
	*/
	void CSteeringMovement::sendAnimationMessage(std::string animation) 
	{
		MSetAnimation *m = new MSetAnimation();

		m->setAnimationName(animation);
		m->setLoop(true);

		_entity->emitMessage(m, this);
	}

	//---------------------------------------------------------
	/**
	Este componente s�lo acepta mensajes MMoveSteering.
	*/
	bool CSteeringMovement::accept(IMessage *message)
	{
		return (message->getType().compare("MMoveSteering") == 0);
	} // accept

	//---------------------------------------------------------
	/**
	Si se recibe un mensaje MMoveSteering, almacena el vector como 
	destino del movimiento y el tipo de movimiento.
	*/
	void CSteeringMovement::process(IMessage *message)
	{
		if (!message->getType().compare("MMoveSteering"))
		{
			MMoveSteering *m = static_cast <MMoveSteering*> (message);
			// Anotamos el vector de desplazamiento para usarlo posteriormente en 
			// el m�todo tick. De esa forma, si recibimos varios mensajes AVATAR_MOVE
			// en el mismo ciclo s�lo tendremos en cuenta el �ltimo.
			_target = m->getTarget();
			_movType = m->getMovementType();

			// Orientamos la entidad hacia el punto de destino
			float yaw = atan((_target.x - _entity->getPosition().x) / (_target.z - _entity->getPosition().z));
			if ((_target.z - _entity->getPosition().z) >= 0)
				yaw += Math::PI;
			_entity->setYaw(yaw);
		}

	} // process

	//---------------------------------------------------------

}