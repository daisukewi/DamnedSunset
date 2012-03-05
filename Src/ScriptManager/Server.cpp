/**
@file Server.cpp

Contiene la implementaci�n de la clase CServer, Singleton que se encarga de
la gesti�n de los scripts del juego.

@see ScriptManager::CServer

@author Alberto Plaza
@date Marzo, 2012
*/

#include "Server.h"

// Inclu�mos las cabedceras de Lua.
// Como es c�digo C (no C++), hay que indicarselo al
// compilador para que asuma el convenio de nombres
// de C en el c�digo objeto.
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>  // Para inicializar la librer�a base de Lua
}

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

#include <cassert>

namespace ScriptManager {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer()
	{
		_instance = this;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicializaci�n de Logic::CServer no permitida!");

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
		assert(_instance && "Logic::CServer no est� inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		/*_lua = lua_open();

		if (!_lua)
			return false;

		// Abrimos la librer�a base para hacer disponible
		// print() en Lua.
		luaopen_base(_lua);

		// Activamos luabind en el int�rprete
		luabind::open(_lua);

		return true;*/

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{

	} // close

	//---------------------------------------------------------

} // namespace ScriptManager
