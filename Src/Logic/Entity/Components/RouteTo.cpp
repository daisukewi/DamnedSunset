#include "RouteTo.h"

#include "Map/MapEntity.h"
#include "Logic/Entity/Entity.h"

#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/MoveSteering.h"

namespace Logic 
{

	//---------------------------------------------------------

	IMP_FACTORY(CRouteTo);

	//---------------------------------------------------------
	/**
	Inicializaci�n del componente

	@param entity Entidad a la que pertenece el componente.
	@param map Mapa L�gico en el que se registrar� el objeto.
	@param entityInfo Informaci�n de construcci�n del objeto le�do del
	fichero de disco.
	@return Cierto si la inicializaci�n ha sido satisfactoria.
	*/
	bool CRouteTo::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		return true;

	} // spawn

	//---------------------------------------------------------
	/**
	M�todo llamado en cada frame que actualiza el estado del componente.
	<p>
	Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.

	@param msecs Milisegundos transcurridos desde el �ltimo tick.
	*/
	void CRouteTo::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		// En este m�todo se gestiona el seguimiento de la ruta.
		// Realmente no se ocupa de mover la entidad, sino de controlar cu�ndo se ha 
		// llegado a un waypoint y notificar a SteeringMovement (que es quien mueve) 
		// del siguiente punto al que moverse y el tipo de movimiento a hacer.
		// El componente almacena su estado en las variables:
		// _target: destino final
		// _currentRoute: ruta actual (vector de posiciones)
		// _currentNode: posici�n de destino actual (�ndice del vector de posiciones)
		//
		// Lo primero que hay que hacer es recalcular la ruta si es necesario (usar la variable _recalculateRoute, que se establece en process)
		// Para recalcular la ruta usamos los m�todos del servidor (getAStarRoute)
		// La posici�n de destino tambi�n se almacena en el m�todo process en _target
		//
		// A continuaci�n tenemos que comprobar si hemos llegado ya al �ltimo punto de la ruta (variable _arrived).
		// Si no, comprobamos si hay que pasar al siguiente punto de la ruta.
		// Sabemos que tenemos que cambiar de punto al procesar un mensaje FINISHED_MOVE (variable _nextWaypoint).
		// Si hay que cambiar de nodo incrementamos el contador (_currentNode) y comprobamos si ya hemos terminado
		// la ruta. Distinguimos 2 (o 3) casos:
		//		� El punto al que hemos llegado era el �ltimo ==> 
		//			actualizamos _arrive 
		//			enviamos un mensaje para parar al componente de movimiento
		//			enviamos un mensaje para indicar que hemos terminado de seguir la ruta (FINISHED_ROUTE)
		//		� El punto al que hemos llegado era el pen�ltimo ==> (esto es opcional y puramente est�tico)
		//			enviamos un mensaje al componente de movimiento para hacer un movimiento de tipo ARRIVE al �ltimo punto
		//		� En otro caso ==> 
		//			enviamos un mensaje al componente de movimiento para hacer un movimiento de tipo SEEK al �ltimo punto

		if (_recalculateRoute) {
			if (_currentRoute != 0) delete _currentRoute;
			_currentRoute = AI::CServer::getSingletonPtr()->getAStarRoute(_entity->getPosition(), _target);
			_recalculateRoute = false;

			// Si no se puede calcular la ruta enviamos un mensaje de fallo
			if (_currentRoute == 0) {
				_arrived = true;
				/*TMessage message;
				message._type = Message::FINISHED_ROUTE;
				message._bool = false;
				_entity->emitMessage(message, this);*/
			} else {
				_currentNode = 0;
				_arrived = false;
				// Si hay ruta hacemos que vaya al primer punto
				//sendMoveMessage((*_currentRoute)[0], AI::IMovement::MOVEMENT_KINEMATIC_SEEK);
				sendMoveMessage((*_currentRoute)[0], AI::IMovement::MOVEMENT_DYNAMIC_SEEK);
			}
		}

		if (!_arrived) {
			if (_nextWaypoint) {
				_nextWaypoint = false;
				// Pasamos al siguiente nodo
				_currentNode++;
				if (_currentNode >= _currentRoute->size()) {
					// Era el �ltimo nodo ==> parar
					_arrived = true;
					sendMoveMessage(_target, AI::IMovement::MOVEMENT_NONE);
					// Enviar un mensaje para notificar que hemos llegado la destino
					/*TMessage message;
					message._type = Message::FINISHED_ROUTE;
					message._bool = true;
					_entity->emitMessage(message, this);*/
				} else if (_currentNode == _currentRoute->size() - 1) {
					// Es el pen�ltimo nodo. Nos acercamos con Arrive
					//sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_KINEMATIC_ARRIVE);
					sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE);
				} else {
					// Nos movemos al siguiente
					//sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_KINEMATIC_SEEK);
					sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_DYNAMIC_SEEK);
				}
			}
		}
	} // tick

	//---------------------------------------------------------
	/** 
	Env�a un mensaje CMoveSteering.

	@param target Destino.
	@movementType Tipo de movimiento.
	*/
	void CRouteTo::sendMoveMessage(Vector3 target, int movementType)
	{
		CMoveSteering *m = new CMoveSteering();

		m->setTarget(Vector3(target.x, 0.0,target.z));
		m->setMovementType(movementType);

		_entity->emitMessage(m, this);
	}

	//---------------------------------------------------------
	/**
	Este componente s�lo acepta mensajes de tipo MWayTo.
	*/
	bool CRouteTo::accept(IMessage *message)
	{
		return false;//message._type == Message::FINISHED_MOVE;
	} // accept

	//---------------------------------------------------------
	/**
	 Si se recibe un mensaje de tipo MWayTo, almacena el vector como 
	 destino del movimiento.
	 Si recibe FINISHED_MOVE pasamos al siguiente punto de la ruta
	*/
	void CRouteTo::process(IMessage *message)
	{
		/*switch(message._type)
		{
			case Message::ROUTE_TO:
				// Comprobamos el bool para saber si tenemos que
				// calcular una nueva ruta o detenernos
				if (message._bool) {
					// Anotamos el vector de desplazamiento para usarlo posteriormente en 
					// el m�todo tick. De esa forma, si recibimos varios mensajes ROUTE_TO
					// en el mismo ciclo s�lo tendremos en cuenta el �ltimo.
					_target = message._vector3;
					_recalculateRoute = true;
				} else {
					// Dejamos de avanzar por la ruta
					_recalculateRoute = false;
					_arrived = true;
					// Eliminamos la ruta
					if (_currentRoute != 0) {
						delete _currentRoute;
						_currentRoute = 0;
					}
					// Y enviamos un mensaje para parar
					sendMoveMessage(_target, AI::IMovement::MOVEMENT_NONE);
				}
				break;
			case Message::FINISHED_MOVE:
				// Hemos terminado el movimiento actual as� que tenemos que pasar al
				// siguiente punto de la ruta (si existe)
				_nextWaypoint = true;
				break;
		}*/

	} // process

} //namespace Logic 