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

	//void startGrenade(unsigned int entityID);
	void startGrenade(unsigned int entityID, float point_x, float point_y, float point_z);
	void cancelGrenade(unsigned int entityID, float point_x, float point_y, float point_z);
	void launchGrenade(unsigned int entityID, float point_x, float point_y, float point_z);
	void empujarCircle(unsigned int entityID);

	void startPowerShoot(unsigned int entityID, float point_x, float point_y, float point_z);
	void launchPowerShoot(unsigned int entityID, float point_x, float point_y, float point_z);
	void cancelPowerShoot(unsigned int entityID);

	void startFlameThrower(unsigned int entityID);
	void launchFlameThrower(unsigned int entityID, float point_x, float point_y, float point_z);
	void cancelFlameThrower(unsigned int entityID);

	void enemigosContraEnemigos(unsigned int entityID);
} // namespace Logic

#endif // __Logic_LUA_MessageFunctions_H