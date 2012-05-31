/**
@file LUA_EntitySelected.h

Contiene la declaración del mensaje reposiciona la camara
que sirve como intermediario entre lua y C++.

@author Daniel Flamenco
@date Mayo, 2012
*/

#ifndef __Logic_LUA_MUbicarCamara_H
#define __Logic_LUA_MUbicarCamara_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargará de seleccionar una entidad.

	@author Luis Mendoza
	@date Mayo, 2012
	*/
	class LUA_MUbicarCamara : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MUbicarCamara();

		/**
		Implementación del método send heredado de la clase LUA_IMessage
		*/
		virtual void send();

	}; // class LUA_MUbicarCamara

} // namespace Logic

#endif // __Logic_LUA_MUbicarCamara_H