/**
@file LUA_EntityFunctions.h

LUA


@author Daniel Flamenco
@date Mayo, 2012
*/

#ifndef __Logic_LUA_EntityFunctions_H
#define __Logic_LUA_EntityFunctions_H


namespace ScriptManager
{

	void deleteEntity(unsigned int entityID);
	bool isPlayer (unsigned int entityID);
	bool isEnemy (unsigned int entityID);
	unsigned int getEntityID (std::string entityName);
	std::string getName (unsigned int entityID);
	std::string getTag (unsigned int entityID);
	

} // namespace Logic

#endif // __Logic_LUA_EntityFunctions_H