/**
@file LUA_MessageFunctions.cpp

LUA

@author Daniel Flamenco
@date Mayo, 2012
*/

#include <cassert>

#include "BaseSubsystems/Math.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"

#include "Logic/Entity/Messages/EmplaceBuilding.h"
#include "Logic/Entity/Messages/LanzarGranada.h"
#include "Logic/Entity/Messages/PushEntities.h"

#include "Logic/Server.h"

namespace ScriptManager
{

	void startBuild(std::string building)
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::START_BUILDING);
		build->setBuildingType(building);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	//---------------------------------------------------------

	void cancelBuild()
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::CANCEL_BUILDING);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	//---------------------------------------------------------

	void emplaceBuild()
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::EMPLACE_BUILDING);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	//---------------------------------------------------------

	void startGrenade(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarGranada *m = new Logic::MLanzarGranada();
		m->setPosition(Vector2(entity->getPosition().x, entity->getPosition().y));
		m->setOrdenGranada(Logic::OrdenGranada::mostrar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void cancelGrenade(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarGranada *m = new Logic::MLanzarGranada();
		m->setPosition(Vector2(entity->getPosition().x, entity->getPosition().y));
		m->setOrdenGranada(Logic::OrdenGranada::ocultar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void launchGrenade(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarGranada *m = new Logic::MLanzarGranada();
		m->setPosition(Vector2(entity->getPosition().x, entity->getPosition().y));
		m->setOrdenGranada(Logic::OrdenGranada::lanzar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void empujarCircle(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MPushEntities *m = new Logic::MPushEntities();

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

} // namespace ScriptManager