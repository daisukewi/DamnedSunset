#include "RouteTo.h"

#include "Map/MapEntity.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"
#include "Logic/Maps/GridMap.h"

#include "AI/Server.h"
#include "AI/Movement.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/AStarRoute.h"
#include "Logic/Entity/Messages/SetAnimation.h"

namespace Logic 
{

	//---------------------------------------------------------

	IMP_FACTORY(CRouteTo);

	//---------------------------------------------------------
	/**
	Inicialización del componente

	@param entity Entidad a la que pertenece el componente.
	@param map Mapa Lógico en el que se registrará el objeto.
	@param entityInfo Información de construcción del objeto leído del
	fichero de disco.
	@return Cierto si la inicialización ha sido satisfactoria.
	*/
	bool CRouteTo::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		return true;

	} // spawn

	//---------------------------------------------------------
	/**
	Método llamado en cada frame que actualiza el estado del componente.
	<p>
	Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.

	@param msecs Milisegundos transcurridos desde el último tick.
	*/
	void CRouteTo::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		// En este método se gestiona el seguimiento de la ruta.
		// Realmente no se ocupa de mover la entidad, sino de controlar cuándo se ha 
		// llegado a un waypoint y notificar a SteeringMovement (que es quien mueve) 
		// del siguiente punto al que moverse y el tipo de movimiento a hacer.
		// El componente almacena su estado en las variables:
		// _target: destino final
		// _currentRoute: ruta actual (vector de posiciones)
		// _currentNode: posición de destino actual (índice del vector de posiciones)
		//
		// Lo primero que hay que hacer es recalcular la ruta si es necesario (usar la variable _recalculateRoute, que se establece en process)
		// Para recalcular la ruta usamos los métodos del servidor (getAStarRoute)
		// La posición de destino también se almacena en el método process en _target
		//
		// A continuación tenemos que comprobar si hemos llegado ya al último punto de la ruta (variable _arrived).
		// Si no, comprobamos si hay que pasar al siguiente punto de la ruta.
		// Sabemos que tenemos que cambiar de punto al procesar un mensaje FINISHED_MOVE (variable _nextWaypoint).
		// Si hay que cambiar de nodo incrementamos el contador (_currentNode) y comprobamos si ya hemos terminado
		// la ruta. Distinguimos 2 (o 3) casos:
		//		· El punto al que hemos llegado era el último ==> 
		//			actualizamos _arrive 
		//			enviamos un mensaje para parar al componente de movimiento
		//			enviamos un mensaje para indicar que hemos terminado de seguir la ruta (FINISHED_ROUTE)
		//		· El punto al que hemos llegado era el penúltimo ==> (esto es opcional y puramente estético)
		//			enviamos un mensaje al componente de movimiento para hacer un movimiento de tipo ARRIVE al último punto
		//		· En otro caso ==> 
		//			enviamos un mensaje al componente de movimiento para hacer un movimiento de tipo SEEK al último punto

		if (_recalculateRoute) {
			if (_currentRoute != 0) delete _currentRoute;
			_currentRoute = AI::CServer::getSingletonPtr()->getAStarRoute(_entity->getPosition(), _target);
			_recalculateRoute = false;

			// Si no se puede calcular la ruta enviamos un mensaje de fallo
			if (_currentRoute == 0) {
				_arrived = true;
				MAStarRoute *m = new MAStarRoute();
				m->setAction(RouteAction::FINISHED_ROUTE);
				m->setRouteFailed(true);
				_entity->emitMessage(m, this);
				// Paramos la animación
				sendAnimationMessage("Idle");
			} else {
				_currentNode = 0; //Indicamos que vamos a empezar en el primer nodo.
				_currentNode = getNextRoutePoint(); //Nos devuelve el siguiente nodo al que debemos viajar.
				_arrived = false;
				_nextWaypoint = false;
				// Si hay ruta hacemos que vaya al primer punto
				//sendMoveMessage((*_currentRoute)[0], AI::IMovement::MOVEMENT_KINEMATIC_SEEK);
				sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_DYNAMIC_SEEK, true);
			}
		}

		if (!_arrived) {
			if (_nextWaypoint) {
				_nextWaypoint = false;
				// Pasamos al siguiente nodo
				_currentNode = getNextRoutePoint();
				if (_currentNode >= _currentRoute->size()) {
					// Era el último nodo ==> parar
					_arrived = true;
					sendMoveMessage(_target, AI::IMovement::MOVEMENT_NONE);
					// Enviar un mensaje para notificar que hemos llegado al destino
					MAStarRoute *m = new MAStarRoute();
					m->setAction(RouteAction::FINISHED_ROUTE);
					m->setRouteFailed(false);
					_entity->emitMessage(m, this);
					// Paramos la animación
					sendAnimationMessage("Idle");

				//} else if (_currentNode == _currentRoute->size() - 1) {
				//	// Es el penúltimo nodo. Nos acercamos con Arrive
				//	//sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_KINEMATIC_ARRIVE);
				//	sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE);

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
	Envía un mensaje MMoveSteering.

	@param target Destino.
	@movementType Tipo de movimiento.
	*/
	void CRouteTo::sendMoveMessage(Vector3 target, int movementType, bool isFirstMove)
	{
		MMoveSteering *m = new MMoveSteering();

		m->setTarget(Vector3(target.x, 0.0, target.z));
		m->setMovementType(movementType);
		m->setFirstMoveOfRoute(isFirstMove);

		_entity->emitMessage(m, this);
	}

	//---------------------------------------------------------

	void CRouteTo::sendAnimationMessage(std::string animation)
	{
		MSetAnimation *m = new MSetAnimation();

		m->setAnimationName(animation);
		m->setLoop(true);

		_entity->emitMessage(m, this);
	}

	//---------------------------------------------------------
	/**
	Este componente sólo acepta mensajes de tipo MRouteTo.
	*/
	bool CRouteTo::accept(IMessage *message)
	{
		bool accepted = !message->getType().compare("MAStarRoute");
		if (accepted) message->addPtr();

		return accepted;

	} // accept

	//---------------------------------------------------------
	/**
	 Si se recibe un mensaje de tipo MWayTo, almacena el vector como 
	 destino del movimiento.
	 Si recibe FINISHED_MOVE pasamos al siguiente punto de la ruta
	*/
	void CRouteTo::process(IMessage *message)
	{
		if (!message->getType().compare("MAStarRoute"))
		{
			MAStarRoute *m_route = static_cast <MAStarRoute*> (message);
			switch (m_route->getAction())
			{
			// Comprobamos si tenemos que calcular una nueva ruta o detenernos
			case RouteAction::START_ROUTE:
				// Anotamos el vector de desplazamiento para usarlo posteriormente en 
				// el método tick. De esa forma, si recibimos varios mensajes ROUTE_TO
				// en el mismo ciclo sólo tendremos en cuenta el último.
				_target = m_route->getRouteDestination();
				_recalculateRoute = true;
				break;

			case RouteAction::STOP_ROUTE:
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
				break;

			case RouteAction::FINISHED_MOVE:
				// Hemos terminado el movimiento actual así que tenemos que pasar al
				// siguiente punto de la ruta (si existe)
				_nextWaypoint = true;
				break;
			}
		}
		message->removePtr();

	} // process

	int CRouteTo::getNextRoutePoint()
	{
		// Si hemos llegado al último nodo, salimos.
		if (_currentNode >= _currentRoute->size() - 1)
			return _currentRoute->size();

		// Guardamos la posición actual y el índice del último nodo.
		float dist;
		Vector3 direction, colPoint;
		Vector3 from = _entity->getPosition();
		int next_node = _currentRoute->size() - 1;

		TGridTile tile = _entity->getMap()->getGridMap()->getTileFromPosition(from.z, from.x);

		std::cout << "\n>> I'm in " << tile->GetRow() << ", " << tile->GetCol() << "\n";

		bool found = false;
		while (!found && next_node > _currentNode + 1)
		{
			Vector3 tilePos = (*_currentRoute)[next_node];
			direction = tilePos - from;
			direction.y = 0;
			dist = direction.length();

			tile = _entity->getMap()->getGridMap()->getTileFromPosition(tilePos.z, tilePos.x);

			std::cout << "\n>> Travelling to " << tile->GetRow() << ", " << tile->GetCol() << "\n";

			// Lanzamos un rayo desde nuestra posición hasta el siguiente nodo
			// y comprobamos si colisiona con algún edificio.
			CEntity *colisionEnt = Physics::CServer::getSingletonPtr()->raycastGroup(
				Ray( from, direction / dist ),
				&colPoint,
				Physics::TPhysicGroup::PG_BUILDING,
				dist );
			found = colisionEnt == NULL;

			if (!found)
			{
				tile = _entity->getMap()->getGridMap()->getTileFromPosition(colPoint.z, colPoint.x);
				std::cout << ">>>> Found Building in " << tile->GetRow() << ", " << tile->GetCol() << " --> Avoiding it.\n";
			}
			else
			{
				std::cout << ">>>> Empty node in (" << tilePos.x << ", 0, " <<tilePos.z << ")\n";
			}
			
			// Si hay un objeto entre el siguiente nodo y nosotros,
			// probamos con el nodo inferior.
			if (!found)
				--next_node;
		}

		return next_node;

	} // optimizeRoute

} //namespace Logic 