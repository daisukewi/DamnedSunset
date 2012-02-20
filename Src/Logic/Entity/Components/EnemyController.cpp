/**
@file EnemyController.cpp

Contiene la implementación del componente que controla el movimiento 
del enemigo.
 
@see Logic::CEnemyController
@see Logic::IComponent

@author Luis Mendoza
@date Enero, 2012
*/

#include "EnemyController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "BaseSubsystems/Math.h"

// Includes para pruebas de paso de mensajes a componentes de IA
#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/AStarRoute.h"


namespace Logic
{
	IMP_FACTORY(CEnemyController);
	
	//---------------------------------------------------------

	bool CEnemyController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		_moving = false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CEnemyController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CEnemyController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CEnemyController::accept(IMessage *message)
	{
		bool accepted = !message->getType().compare("MAStarRoute");
		if (accepted) message->addPtr();

		return accepted;

	} // accept
	
	//---------------------------------------------------------

	void CEnemyController::process(IMessage *message)
	{
		MAStarRoute *m_route = static_cast <MAStarRoute*> (message);
		switch (m_route->getAction())
		{
		case RouteAction::FINISHED_ROUTE:
			// Hemos terminado el movimiento actual así que tenemos que
			// calcular una nueva ruta.
			_moving = false;
			break;
		}
		message->removePtr();
	} // process
	
	//---------------------------------------------------------

	void CEnemyController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		// Si no se está moviendo calculamos un nuevo punto de destino y llevamos al enemigo para allá.
		// Cuando la distancia al objetivo es pequeña volvemos a hacer el mismo proceso.
		if (!_moving)
		{
			Vector3 destino = Vector3 ( rand() % 200 - 100, 1.0f, rand() % 200 - 100);

			MAStarRoute *m = new MAStarRoute();
			m->setAction(RouteAction::START_ROUTE);
			m->setRouteDestination(destino);
			_entity->emitMessage(m, this);

			_moving = true;
		}

	} // tick

} // namespace Logic

