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

	bool CServer::loadExeScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Busco si el script ya lo he cargado anteriormente.
		bool exists = false;

		for (TScriptList::iterator it = _scriptList.begin(); it != _scriptList.end(); it++)
			exists = exists || (script == it._Ptr->_Myval);

		// Si ya lo he cargado muestro un mensaje de error, salgo y devuelvo false.
		if (exists)
		{
			std::cout << "ERROR DE LUA! - Error al cargar el fichero de script \"" << script << "\". Este fichero ya se ha cargado anteriormente." << std::endl;

			return false;
		}

		// Cargo el script. Si la carga ha ido bien, me lo guardo.
		if (loadScript(script, false))
			_scriptList.push_back(script);
		else
			return false;

		// Ejecuto el script
		if (!executeLastLoadScript(script))
			return false;

		return true;

	} // loadExeScript

	//---------------------------------------------------------

	bool CServer::executeScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Cargo el script en modo inmediato.
		if (!loadScript(script, true))
			return false;

		// Ejecuto el script
		if (!executeLastLoadScript(script))
			return false;

		return true;
	
	} // executeScript

	//---------------------------------------------------------

	bool CServer::loadScript(const char *script, bool inmediate)
	{
		// Completo la ruta del script.
		std::stringstream filename;
		filename << "media\\scripts\\" << script << ".lua";

		// Cargo el fichero de script dependiendo del parámetro booleano.
		int errorType = 0;

		if (inmediate)
			errorType = luaL_loadstring(_lua, script);
		else
			errorType = luaL_loadfile(_lua, filename.str().c_str());

		// Error al cargar el fichero de script
		if (errorType == LUA_ERRFILE)
		{
			std::cout << "ERROR DE LUA! - Error al cargar el fichero de script \"" << script << "\". Comprueba que está bien escrito el nombre y que el fichero existe." << std::endl;

			return false;
		}
		// Error de sintaxis de lua
		else if (errorType == LUA_ERRSYNTAX)
		{
			std::cout << "ERROR DE LUA! - Error de sintaxis de lua al cargar el script \"" << script << "\". Comprueba que no hay errores en el fichero de script." << std::endl;

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al cargar el script \"" << script << "\" : Memory allocation error." << std::endl;

			return false;
		}
		// Error chungo de no se qué de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al cargar el script \"" << script << "\" : Error chungo de no se qué de metamethod." << std::endl;

			return false;
		}

		return true;
		
	} // loadScript

	//---------------------------------------------------------

	bool CServer::executeLastLoadScript(const char *script)
	{
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
				std::cout << "ERROR DE LUA! - Error de runtime de lua al ejecutar el script \"" << script << "\": " << error << std::endl;
			}
			else
				// En teoría esta situación no debería darse nunca, pero no está de más hacer la comprobación.
				std::cout << "ERROR DE LUA! - Error desconocido de runtime de lua al ejecutar el script \"" << script << "\"" << std::endl;

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" << script << "\" : Memory allocation error." << std::endl;

			return false;
		}
		// Error ejecutando el message handler
		else if (errorType == LUA_ERRERR)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" << script << "\" : Error ejecutando el message handler." << std::endl;

			return false;
		}
		// Error chungo de no se qué de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" << script << "\" : Error chungo de no se qué de metamethod." << std::endl;

			return false;
		}

		return true;

	} // executeLastLoadScript

	//---------------------------------------------------------

} // namespace ScriptManager
