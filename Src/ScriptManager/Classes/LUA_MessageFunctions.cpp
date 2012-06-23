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

	void cancelBuild()
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::CANCEL_BUILDING);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	void emplaceBuild()
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::EMPLACE_BUILDING);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

} // namespace ScriptManager