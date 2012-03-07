/**
@file Server.cpp

Contiene la implementación de la clase CServer, Singleton que se encarga de
la gestión de los scripts del juego.

@see ScriptManager::CServer

@author Alberto Plaza
@date Marzo, 2012
*/

#include "Server.h"

// Incluímos las cabedceras de Lua.
// Como es código C (no C++), hay que indicarselo al
// compilador para que asuma el convenio de nombres
// de C en el código objeto.
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>  // Para inicializar la librería base de Lua
}

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

#include <cassert>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace ScriptManager {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer()
	{
		_instance = this;
		_lua = NULL;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicialización de ScriptManager::CServer no permitida!");

		new CServer();

		if (!_instance->open())
		{
			Release();
			return false;
		}

		return true;

	} // Init

	//--------------------------------------------------------

	void CServer::Release()
	{
		assert(_instance && "ScriptManager::CServer no está inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		// Obtengo el estado de lua (inicialización de lua)
		_lua = luaL_newstate();

		if (!_lua)
			return false;

		// Abro las librerías de lua (segunda parte de la inicialización)
		luaL_openlibs(_lua);

		// Abrimos la librería base para hacer disponible
		// print() en Lua.
		luaopen_base(_lua);

		// Activamos luabind en el intérprete
		luabind::open(_lua);

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		if (_lua)
			lua_close(_lua);

	} // close

	//---------------------------------------------------------

	bool CServer::loadScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Busco si el script ya lo he cargado anteriormente.
		bool exists = false;

		for (TScriptList::iterator it = _scriptList.begin(); it != _scriptList.end(); it++)
			exists = exists || (script == it._Ptr->_Myval);

		// Si ya lo he cargado salgo y devuelvo false.
		if (exists)
			return false;

		std::stringstream filename;
		filename << "media\\scripts\\" << script << ".lua";

		// Si he llegado aquí sin salir es que el script no lo he cargado aún. Lo cargo.
		if (luaL_loadfile(_lua, filename.str().c_str()) != 0)
			return false;

		// Ejecuto el script y hago el manejo de errores.
		int msgHandler = 0;
		int errorType = lua_pcall(_lua, 0, 0, msgHandler);

		// Si es un runtime error, accedo al tipo de error guardado en la pila y lo muestro por consola
		if (errorType == LUA_ERRRUN)
		{
			// Si el handler es distinto de cero, el mensaje de error se encuentra en la pila. Lo recupero y lo muestro.
			if (msgHandler != 0)
			{
				const char* error = lua_tostring(_lua, msgHandler);
				std::cout << "Error de runtime de lua al ejecutar el script " << script << ": " << error;
			}
			else
				// En teoría esta situación no debería darse nunca, pero no está de más hacer la comprobación.
				std::cout << "Error desconocido de runtime de lua al ejecutar el script " << script;

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			std::cout << "Error chungo de lua al ejecutar el script " << script << " : Memory allocation error.";

			return false;
		}
		// Error ejecutando el message handler
		else if (errorType == LUA_ERRERR)
		{
			std::cout << "Error chungo de lua al ejecutar el script " << script << " : Error ejecutando el message handler.";

			return false;
		}
		// Error chungo de no se qué de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			std::cout << "Error chungo de lua al ejecutar el script " << script << " : Error chungo de no se qué de metamethod.";

			return false;
		}

		// Si he llegado aquí es que el script no lo había cargado aún y tanto la carga como la ejecución han ido bien.
		_scriptList.push_back(script);

		return true;

	} // loadScript

	//---------------------------------------------------------

} // namespace ScriptManager
