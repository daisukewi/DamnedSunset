/**
@file LUA_MessageFunctions.h

LUA


@author Daniel Flamenco
@date Mayo, 2012
*/

#ifndef __Logic_LUA_MessageFunctions_H
#define __Logic_LUA_MessageFunctions_H


namespace ScriptManager
{
	void startBuild(std::string building);
	void cancelBuild();
	void emplaceBuild();

	void startGrenade(unsigned int entityID);
	void cancelGrenade(unsigned int entityID);
	void launchGrenade(unsigned int entityID);
	void empujarCircle(unsigned int entityID);

} // namespace Logic

#endif // __Logic_LUA_MessageFunctions_H