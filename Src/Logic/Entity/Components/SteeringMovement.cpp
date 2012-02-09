/**
@file SteeringMovement.cpp

Contiene la declaración de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cinéticos o dinámicos.

@author Gonzalo Flórez
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
	Inicialización del componente, utilizando la información extraída de
	la entidad leída del mapa (Maps::CEntity). Toma del mapa los atributos
	speed, angularSpeed, accel y angularAccel, que indican los valores máximos 
	de velocidad y aceleración lineales y angulares. El atributo tolerance indica
	la distancia a la que se considera que se ha alcanzado una posición.

	@param entity Entidad a la que pertenece el componente.
	@param map Mapa Lógico en el que se registrará el objeto.
	@param entityInfo Información de construcción del objeto leído del
	fichero de disco.
	@return Cierto si la inicialización ha sido satisfactoria.
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

			// En yaw guardamos el movimiento correspondiente a la rotación de la entidad.
			// En este caso suponemos que la entidad siempre se mueve hacia adelante, 
			// así que hacemos que siempre esté alineado con su vector de velocidad.

		_yaw = AI::IMovement::getMovement(AI::IMovement::MOVEMENT_KINEMATIC_ALIGN_TO_SPEED, 
			_maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel); 
		_yaw->setEntity(entity);

		return true;

	} // spawn

	//---------------------------------------------------------
	/**
	Método llamado en cada frame que actualiza el estado del componente.
	<p>
	Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.

	@param msecs Milisegundos transcurridos desde el último tick.
	*/
	void CSteeringMovement::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// En este método se realiza un movimiento básico usando un steering movement
		// El steering movement calcula las velocidades y aceleraciones lineales y angulares y,
		// con esta información se envían mensajes a la física, el avatar controller y las animaciones
		
		// Variables útiles:
		// _maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel: velocidades y aceleraciones lineales y angulares.
		// _tolerance: distancia a la que se considera que se ha llegado al punto de destino.
		// _arrived: ¿ha llegado al destino?
		// _currentTarget: punto de destino del movimiento actual.
		// _target: nuevo punto de destino que se ha establecido en el método process, pero que aún no es el actual.
		// _currentMovementType, _movType: lo mismo con el tipo de movimiento. Son valores sacados del enumerado IMovement::EnmMovementType 
		// _currentMovement: instancia de IMovement correspondiente al movimiento actual.
		// _yaw: instancia de IMovement correspondiente al movimiento de giro actual. De momento sólo hay un posible valor
		//		(MOVEMENT_KINEMATIC_ALIGN_TO_SPEED) que establecemos en el spawn.
		// _currentProperties: esta variable sirve de entrada y de salida para los steering behaviours. En ella se almacena la información
		//		de velocidad entre los ticks.

		// En cada tick tenemos que:
		// Comprobar si hay que cambiar de movimiento o destino
		//		Si es así, sacar el nuevo movimiento de la factoría (puede ser NULL ==> parado)
		//		Asignarle el nuevo destino y la entidad al movimiento
		//		Actualizar la variable _arrived para indicar que no hemos llegado a destino
		//		Si tiene que cambiar la animación notificarlo con un mensaje

		// Comprobamos si hemos llegado al destino
		// Podemos usar positionEquals (IMPORTANTE: usar la _tolerance)
		//		Si es así, enviar un mensaje FINISHED_MOVE para indicar que hemos llegado

		// Si tenemos que movernos (no hemos llegado al destino y nuestro movimiento no es NULL)
		//		Invocar al método move del movimiento actual. 
		//		Le pasamos la variable _currentProperties, que contiene las velocidades actuales y en la que recogemos las nuevas velocidades y aceleraciones
		//		Calcular la nueva posición y notificarla a la física para que nos mueva (mensaje MAvatarWalk)
		//		Actualizar las velocidades usando la aceleración que hemos obtenido en _currentProperties
		//		Las velocidades que tenemos que actualizar también están en _currentProperties para pasárselas en el siguiente tick al movimiento


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
				// Y la animación
				sendAnimationMessage("Walk");
			} else {
				// Si no hay movimiento paramos la animación
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

		// Si nos estamos desplazando calculamos la próxima posición
		if (!_arrived && _currentMovement != 0) {
	
			_currentMovement->move(msecs, _currentProperties);
			// Calculamos la rotación
			_yaw->move(msecs, _currentProperties);

			// Enviar un mensaje para que el componente físico mueva el personaje
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
			// Si no hay movimiento paramos la animación
			sendAnimationMessage("Idle");
		}

	} // tick

	//---------------------------------------------------------
	/**
	Envía un mensaje para cambiar la animación actual.

	@param animation Nueva animación.
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
	Este componente sólo acepta mensajes MMoveSteering.
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
			// el método tick. De esa forma, si recibimos varios mensajes AVATAR_MOVE
			// en el mismo ciclo sólo tendremos en cuenta el último.
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