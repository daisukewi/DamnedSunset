/**
@file LUA_EntityFunctions.cpp

LUA

@author Daniel Flamenco
@date Mayo, 2012
*/

#include <cassert>

#include "BaseSubsystems/Math.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"

#include "Logic/Server.h"

namespace ScriptManager
{

	bool isPlayer(unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return !entity->getType().compare("Player");
		}

		return false;
	}

	//---------------------------------------------------------

	bool isEnemy(unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return !entity->getType().compare("Enemy");
		}

		return false;
	}

	//---------------------------------------------------------

	unsigned int getEntityID (std::string entityName)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName(entityName);
		if (entity != NULL)
		{
			return entity->getEntityID();
		}

		return 0;
	}
	
	//---------------------------------------------------------

	std::string getName (unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return entity->getName();
		}

		return "";
	}

} // namespace ScriptManager