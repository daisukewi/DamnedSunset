/**
@file SetPlayerState.cpp

Contiene la implementación del mensaje de entidad seleccionada que sirve como intermediario entre lua y C++.

@author Albert Ortega
@date Junio, 2012
*/

#include "SetPlayerState.h"

#include "Logic/Entity/Messages/SetPlayerState.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include <cassert>

namespace Logic
{

	MSetPlayerState::MSetPlayerState()
	{
		IMessage();

		_type = "MSetPlayerState";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void MSetPlayerState::setPlayerState(PlayerState state)
	{
		_playerState = state;

	} // setPlayerState


	//---------------------------------------------------------

	PlayerState MSetPlayerState::getPlayerState()
	{
		return _playerState;

	} // getPlayerState


	//---------------------------------------------------------

} // namespace Logic