/**
@file LUA_CambiarDiaNoche.cpp

LUA

Contiene la implementación del mensaje de cambiar ciclo dia y noche

@author Isaac Gallarzagoitia
@date Mayo, 2012
*/

#include "LUA_CambiarDiaNoche.h"



//#include "Logic/Entity/Messages/CambiarDiaNoche.h"
#include <cassert>

#include "BaseSubsystems/Math.h"

#include "Logic/Maps/Map.h"

#include "Logic/Server.h"

#include "Logic\Entity\Messages\DayNight.h"

namespace ScriptManager
{

	LUA_MCambiarDiaNoche::LUA_MCambiarDiaNoche()
	{
		LUA_IMessage();

		_type = "LUA_MCambiarDiaNoche";

	} // MAttackEntity


	//---------------------------------------------------------

	void LUA_MCambiarDiaNoche::send()
	{
		Logic::MDayNight *m = new Logic::MDayNight();
		m->setTime(Logic::TIME_TYPE::NIGHT);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod")->emitMessage(m);
	} // sendKFF

	//---------------------------------------------------------

} // namespace Logic