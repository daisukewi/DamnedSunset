/**
@file LUA_SetPlayerState.h

Contiene la declaración del mensaje de cambio de estado(IA) de los personajes que sirve como intermediario entre lua y C++.

@author Albert Ortega
@date Junio, 2012
*/

#ifndef __Logic_LUA_SetPlayerState_H
#define __Logic_LUA_SetPlayerState_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargará de indicar que estado de la IA usar.

	@author Albert Ortega
	@date Junio, 2012
	*/
	class LUA_MSetPlayerState : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MSetPlayerState();

		/**
		Implementación del método send heredado de la clase LUA_IMessage
		*/
		virtual void send();

		/**
		Establece en el mensaje el estado de la IA
		*/
		void setPlayerState(std::string state);


	protected:

		/**
		Atributo que indica el estado que se quiere poner.
		*/
		std::string _playerState;
		

	}; // class LUA_MSetPlayerState

} // namespace Logic

#endif // __Logic_LUA_SetPlayerState_H