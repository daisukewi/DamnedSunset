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

#include <OISMouse.h>
#include "Application/BaseApplication.h"

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
		//Logic::MCambiarDiaNoche *message = new Logic::MCambiarDiaNoche();
		//message->setCambiarADia(_cambiarADia);
		//Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entityTo)->emitMessage(message);


		Application::CBaseApplication::getSingletonPtr()->setState("game");
	} // sendKFF

	//---------------------------------------------------------

} // namespace Logic