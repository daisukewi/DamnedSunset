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

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/Server.h"

// Includes para pruebas de paso de mensajes a componentes de IA
#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/AStarRoute.h"
#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/EntityDeath.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/ActivarComponente.h"


namespace Logic
{
	IMP_FACTORY(CEnemyController);
	
	//---------------------------------------------------------

	bool CEnemyController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		_attacking = _moving = !(rand() % 2);

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
		accepted |= !message->getType().compare("MEntityDeath");

		return accepted;

	} // accept
	
	//---------------------------------------------------------

	void CEnemyController::process(IMessage *message)
	{
		if (!message->getType().compare("MAStarRoute"))
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
		}
		else if (!message->getType().compare("MEntityDeath"))
		{
			MAStarRoute *m_stop = new MAStarRoute();
			m_stop->setAction(RouteAction::STOP_ROUTE);
			_entity->emitMessage(m_stop, this);

			MActivarComponente *m_deactComp = new MActivarComponente();
			m_deactComp->setActivar(false);
			m_deactComp->setNombreComponente("CAttack");
			_entity->emitMessage(m_deactComp, this);

			MActivarComponente *m_deactComp1 = new MActivarComponente();
			m_deactComp1->setActivar(false);
			m_deactComp1->setNombreComponente("CLife");
			_entity->emitMessage(m_deactComp1, this);

			MActivarComponente *m_deactComp2 = new MActivarComponente();
			m_deactComp2->setActivar(false);
			m_deactComp2->setNombreComponente("CBillboardSelected");
			_entity->emitMessage(m_deactComp2, this);

			MActivarComponente *m_deactComp3 = new MActivarComponente();
			m_deactComp3->setActivar(false);
			m_deactComp3->setNombreComponente("CPhysicCharacter");
			_entity->emitMessage(m_deactComp3, this);

			MActivarComponente *m_deactComp4 = new MActivarComponente();
			m_deactComp4->setActivar(false);
			m_deactComp4->setNombreComponente("CSteeringMovement");
			_entity->emitMessage(m_deactComp4, this);

			MActivarComponente *m_deactComp5 = new MActivarComponente();
			m_deactComp5->setActivar(false);
			m_deactComp5->setNombreComponente("CRouteTo");
			_entity->emitMessage(m_deactComp5, this);

			MActivarComponente *m_deactComp6 = new MActivarComponente();
			m_deactComp6->setActivar(false);
			m_deactComp6->setNombreComponente("CSelectable");
			_entity->emitMessage(m_deactComp6, this);

			MActivarComponente *m_deactComp7 = new MActivarComponente();
			m_deactComp7->setActivar(false);
			m_deactComp7->setNombreComponente("CEnemyController");
			_entity->emitMessage(m_deactComp7, this);

			MSetAnimation *m_anim = new MSetAnimation();
			m_anim->setAnimationName("Death");
			m_anim->setLoop(false);
			_entity->emitMessage(m_anim, this);

			_moving = true;
			_attacking = false;

			/*
			Aviso al reloj con el tiempo de temporizador.
			El reloj empezará a contar a partir del frame siguiente a esta instrucción.
			*/
			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(5000, this);
		}

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
		else if (_attacking)
		{
			MAttackEntity *m_at = new MAttackEntity();
			m_at->setAttack(true);
			unsigned int p = rand() % 3;
			CEntity* player;
			switch (p)
			{
				case 0:
					player = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack");
					break;
				case 1:
					player = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick");
					break;
				case 2:
					player = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Amor");
					break;
			}
			m_at->setEntity(player);
			_entity->emitMessage(m_at, this);
			_attacking = false;
			player->addDeathListener(this);
		}

	} // tick

	//---------------------------------------------------------

	void CEnemyController::timeElapsed()
	{
		/* 
		Implementación del método de la interfaz que va a ser llamado cuando se acabe el tiempo.
		Se elimina al enemigo.
		*/

		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);

	} // timeElapsed

	//---------------------------------------------------------

	void CEnemyController::entityDeath(CEntity* entity)
	{
		/* 
		Implementación del método que va a ser llamado cuando muera la entidad.
		*/
		_attacking = _moving = false;
		entity->removeDeathListener(this);

	} // entityDeath

} // namespace Logic

