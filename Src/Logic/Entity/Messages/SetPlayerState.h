/**
@file SetPlayerState.h

Contiene la declaración del mensaje de cambio de estado(IA) de los personajes

@author Albert Ortega
@date Junio, 2012
*/

#ifndef __Logic_SetPlayerState_H
#define __Logic_SetPlayerState_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Estados de la IA de los personajes
	*/
	namespace SetPlayerStateMessage
	{
		enum PlayerState
		{
			IDLE,
			HOLD,
			FOLLOW
		};
	}

	typedef SetPlayerStateMessage::PlayerState PlayerState;


	/**
	Clase mensaje que se encargará de indicar que estado de la IA usar.

	@author Albert Ortega
	@date Junio, 2012
	*/
	class MSetPlayerState : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MSetPlayerState();

		/**
		Establece el estado de la IA
		@param state
		*/
		void setPlayerState(PlayerState state);

		/**
		Obtener el estado de la IA

		@return _playerState
		*/
		PlayerState getPlayerState();


	protected:

		/**
		Atributo que indica el estado que se quiere poner.
		*/
		PlayerState _playerState;
		

	}; // class MSetPlayerState

} // namespace Logic

#endif // __Logic_SetPlayerState_H