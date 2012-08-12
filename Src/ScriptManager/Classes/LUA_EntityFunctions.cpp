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
#include "Logic/Maps/EntityFactory.h"

#include "Logic/Server.h"

namespace ScriptManager
{

	void deleteEntity(unsigned int entityID)
	{
		Logic::CEntityFactory::getSingletonPtr()->deferredDeleteEntity(Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID));
	}

	//---------------------------------------------------------

	bool isPlayer(unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return !entity->getTag().compare("Player");
		}

		return false;
	}

	//---------------------------------------------------------

	bool isEnemy(unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return !entity->getTag().compare("enemy");
		}

		return false;
	}

	//---------------------------------------------------------

	bool isEnemyBuilding(unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return !entity->getTag().compare("enemyBuilding");
		}

		return false;
	}

	//---------------------------------------------------------

	bool isPlayerBuilding(unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return !entity->getTag().compare("playerBuilding");
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

	//---------------------------------------------------------

	std::string getTag (unsigned int entityID)
	{
		Logic::CEntity* entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity != NULL)
		{
			return entity->getTag();
		}

		return "";
	}

} // namespace ScriptManager