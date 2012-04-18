/**
@file LUA_Message.cpp

LUA

Contiene el tipo de datos de un mensaje.

@author Alberto Ortega
@date Abril, 2012
*/

#include "LUA_Message.h"
#include <cassert>

namespace ScriptManager
{
	void LUA_IMessage::setEntityTo(unsigned int entityTo)
	{
		_entityTo = entityTo;
	}

	void LUA_IMessage::send()
	{
		assert(true && "No se ha redefinido el metodo en la clase hija"); 
	}


} // namespace ScriptManager