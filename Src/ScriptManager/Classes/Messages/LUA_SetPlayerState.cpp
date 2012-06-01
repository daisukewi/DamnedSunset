/**
@file LUA_SetPlayerState.cpp

Contiene la implementación del mensaje de entidad seleccionada que sirve como intermediario entre lua y C++.

@author Albert Ortega
@date Junio, 2012
*/

#include "LUA_SetPlayerState.h"

#include "Logic/Entity/Messages/SetPlayerState.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include <cassert>

namespace ScriptManager
{

	LUA_MSetPlayerState::LUA_MSetPlayerState()
	{
		LUA_IMessage();

		_playerState = "";

		_type = "LUA_MSetPlayerState";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void LUA_MSetPlayerState::setPlayerState(std::string state)
	{
		_playerState = state;

	} // setPlayerState

	//---------------------------------------------------------

	void LUA_MSetPlayerState::send()
	{
		Logic::CEntity *selectedEntity = NULL;
		Logic::MSetPlayerState *m = new Logic::MSetPlayerState();
	
		Logic::SetPlayerStateMessage::PlayerState state;
		if (!_playerState.compare("idle"))
			state = Logic::SetPlayerStateMessage::PlayerState::IDLE;
		else if (!_playerState.compare("hold"))
			state = Logic::SetPlayerStateMessage::PlayerState::HOLD;
		else if (!_playerState.compare("follow"))
			state = Logic::SetPlayerStateMessage::PlayerState::FOLLOW;

		m->setPlayerState(state);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(this->getEntityTo())->emitMessage(m);

	} // send

	//---------------------------------------------------------

} // namespace Logic