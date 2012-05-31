/**
@file LUA_EntitySelected.cpp

Contiene la implementación del mensaje de entidad seleccionada que sirve como intermediario entre lua y C++.

@author Luis Mendoza
@date Mayo, 2012
*/

#include "LUA_UbicarCamara.h"

#include "Logic/Entity/Messages/UbicarCamara.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include <cassert>

namespace ScriptManager
{

	LUA_MUbicarCamara::LUA_MUbicarCamara()
	{
		LUA_IMessage();

		_type = "LUA_MUbicarCamara";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void LUA_MUbicarCamara::send()
	{
		Logic::CEntity *selectedEntity;
		Logic::MUbicarCamara *m = new Logic::MUbicarCamara();

		selectedEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(this->getEntityTo());
		m->setEntity(selectedEntity);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(m);

	} // send

	//---------------------------------------------------------

} // namespace Logic