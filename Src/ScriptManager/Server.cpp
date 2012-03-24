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
extern "C" 
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>  // Para inicializar la librería base de Lua
}

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

#include "Map\MapParser.h"

#include <cassert>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace ScriptManager
{

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
			showErrorMessage("ERROR DE LUA! - Error al cargar el fichero de script \"" + std::string(script) + "\". Este fichero ya se ha cargado anteriormente.");

			return false;
		}

		// Cargo el script.
		if (!loadScript(script, false))
			return false;

		// Ejecuto el script.
		if (!executeLastLoadScript(script))
			return false;

		// Si he llegado aquí es que todo ha ido bien, por lo tanto me guardo el script y muestro un mensaje de confirmación.
		_scriptList.push_back(script);
		showMessage("Fichero \"" + std::string(script) + "\" cargado y ejecutado correctamente");

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

	void CServer::reloadScripts()
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		for (TScriptList::iterator it = _scriptList.begin(); it != _scriptList.end(); it++)
		{
			if (loadScript(it._Ptr->_Myval, false) && executeLastLoadScript(it._Ptr->_Myval))
				showMessage("Fichero \"" + std::string(it._Ptr->_Myval) + "\" cargado y ejecutado correctamente");
		}
	
	} // reloadScripts

	//---------------------------------------------------------

	template <class T>
	void CServer::setGlobal(const char *name, const T& value)
	{
		luabind::globals(_lua)[name] = boost::ref(value);
		
	} // setGlobal

	//---------------------------------------------------------

	int CServer::getGlobal(const char *name, int defaultValue)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gestión de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TNUMBER))
		{
			showErrorMessage("ERROR DE LUA! - La variable numérica \"" + std::string(name) + "\" a la que se está intentando acceder no existe en ningún script de lua o no es de tipo numérico.");

			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<int>(obj);

	} // getGlobal(int)

	//---------------------------------------------------------

	bool CServer::getGlobal(const char *name, bool &error)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gestión de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TBOOLEAN))
		{
			showErrorMessage("ERROR DE LUA! - La variable booleana \"" + std::string(name) + "\" a la que se está intentando acceder no existe en ningún script de lua o no es de tipo booleana.");

			error = true;
			return false;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++. Y actualizo la variable de error.
		error = false;
		return luabind::object_cast<bool>(obj);
		
	} // getGlobal(bool)

	//---------------------------------------------------------

	const char *CServer::getGlobal(const char *name, const char *defaultValue)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gestión de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TSTRING))
		{
			showErrorMessage("ERROR DE LUA! - La variable de tipo cadena \"" + std::string(name) + "\" a la que se está intentando acceder no existe en ningún script de lua o no es de tipo cadena.");

			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<const char*>(obj);
		
	} // getGlobal(char*)

	//---------------------------------------------------------

	int CServer::getField(const char *table, const char *field, int defaultValue)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			showErrorMessage("ERROR DE LUA! - La tabla \"" + std::string(table) + "\" a la que se está intentando acceder no existe o no es de tipo tabla.");
			
			return defaultValue;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TNUMBER))
		{
			showErrorMessage("ERROR DE LUA! - No existe ningún campo \"" + std::string(field) + "\" en la tabla \"" + std::string(table) + "\" o no es de tipo entero.");
			
			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<int>(valor);
		
	} // getField(int)

	//---------------------------------------------------------

	bool CServer::getField(const char *table, const char *field, bool &error)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			showErrorMessage("ERROR DE LUA! - La tabla \"" + std::string(table) + "\" a la que se está intentando acceder no existe o no es de tipo tabla.");
			
			error = true;
			return false;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TBOOLEAN))
		{
			showErrorMessage("ERROR DE LUA! - No existe ningún campo \"" + std::string(field) + "\" en la tabla \"" + std::string(table) + "\" o no es de tipo booleano.");
			
			error = true;
			return false;;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		error = false;
		return luabind::object_cast<bool>(valor);
		
	} // getField(bool)

	//---------------------------------------------------------

	const char *CServer::getField(const char *table, const char *field, const char *defaultValue)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			showErrorMessage("ERROR DE LUA! - La tabla \"" + std::string(table) + "\" a la que se está intentando acceder no existe o no es de tipo tabla.");
			
			return defaultValue;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TSTRING))
		{
			showErrorMessage("ERROR DE LUA! - No existe ningún campo \"" + std::string(field) + "\" en la tabla \"" + std::string(table) + "\" o no es de tipo cadena.");
			
			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<const char*>(valor);
		
	} //getField(char*)

	//---------------------------------------------------------

	bool CServer::executeProcedure(const char *subroutineName)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo el procedimiento definido en lua
		luabind::object proc = luabind::globals(_lua)[subroutineName];

		// Compruebo que el procedimiento existe y es un procedimiento.
		if (!proc.is_valid() || (luabind::type(proc) != LUA_TFUNCTION))
		{
			showErrorMessage("ERROR DE LUA! - El procedimiento \"" + std::string(subroutineName) + "\" que se está intentando ejecutar no existe o es un procedimiento.");

			return false;
		}

		// Lo ejecuto y hago comprobación de errores.
		try {
			proc();
		} catch (luabind::error &ex) {
			showErrorMessage("ERROR DE LUA! - Error al ejecutar el procedimiento \"" + std::string(subroutineName) + "\". Tipo de error: " + std::string(ex.what()));

			return false;
		}

		return true;
		
	} // executeProcedure

	//---------------------------------------------------------

	template <class T>
	bool CServer::executeProcedure(const char *subroutineName, const T& param1)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo el procedimiento definido en lua
		luabind::object proc = luabind::globals(_lua)[subroutineName];

		// Compruebo que el procedimiento existe y es un procedimiento.
		if (!proc.is_valid() || (luabind::type(proc) != LUA_TFUNCTION))
		{
			showErrorMessage("ERROR DE LUA! - El procedimiento \"" + std::string(subroutineName) + "\" que se está intentando ejecutar no existe o es un procedimiento.");

			return false;
		}

		// Lo ejecuto y hago comprobación de errores.
		try {
			proc(param1);
		} catch (luabind::error &ex) {
			showErrorMessage("ERROR DE LUA! - Error al ejecutar el procedimiento \"" + std::string(subroutineName) + "\". Tipo de error: " + std::string(ex.what()));

			return false;
		}

		return true;
		
	} // executeProcedure(1 param)

	//---------------------------------------------------------

	template <class T>
	bool CServer::executeFunction(const char *subroutineName, const T& param1, int &result)
	{
		assert(_lua && "No se ha hecho la inicialización de lua");

		// Obtengo la función definida en lua
		luabind::object func = luabind::globals(_lua)[subroutineName];

		// Compruebo que la función existe y es una función.
		if (!func.is_valid() || (luabind::type(func) != LUA_TFUNCTION))
		{
			showErrorMessage("ERROR DE LUA! - La función \"" + std::string(subroutineName) + "\" que se está intentando ejecutar no existe o es una función.");

			return false;
		}

		try {
			// Intento ejecutar la función
			luabind::object res = func(param1);

			// Hago comprobación de errores para asegurarme de que lo que me ha devuelto la función es correcto.
			if (!res.is_valid() || (luabind::type(res) != LUA_TNUMBER))
			{
				showErrorMessage("ERROR DE LUA! - La función \"" + std::string(subroutineName) + "\" no ha devuelto ningún valor o el valor devuelto no es de tipo entero.");

				return false;
			}

			result = luabind::object_cast<int>(res);
			return true;

		} catch (luabind::error &ex) {
			showErrorMessage("ERROR DE LUA! - Error al ejecutar la función \"" + std::string(subroutineName) + "\". Tipo de error: " + std::string(ex.what()));

			return false;
		}

		return true;
		
	} // executeFunction(1 param, 1 result)

	//---------------------------------------------------------

	template <class F>
	void CServer::registerFunction(const char *name, F f)
	{
		luabind::module(_lua)
		[
			luabind::def(name, f)
		];
		
	} // registerFunction

	//---------------------------------------------------------

	void CServer::registerClasses()
	{
		//------------------------------------------------------//
		//				REGISTRO DEL MAPPARSER					//
		//------------------------------------------------------//
		luabind::module(_lua)
			[
				luabind::class_<Map::CMapParser>("CMapParser")
				.def("beginEntity", (void (Map::CMapParser::*) (const char*)) &Map::CMapParser::beginEntity)
				.def("newAttrib", (void (Map::CMapParser::*) (const char*, const char*)) &Map::CMapParser::newAttrib)
				.def("endEntity", &Map::CMapParser::endEntity)
			];
		luabind::globals(_lua)["Parser"] = boost::ref(*Map::CMapParser::getSingletonPtr());
		
	} // registerClasses

	//---------------------------------------------------------

	void CServer::deRegisterClasses()
	{
		//------------------------------------------------------//
		//				DESREGISTRO DEL MAPPARSER				//
		//------------------------------------------------------//
		luabind::globals(_lua)["Parser"] = 0;
		
	} // deRegisterClasses

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
			showErrorMessage("ERROR DE LUA! - Error al cargar el fichero de script \"" + std::string(script) + "\". Comprueba que está bien escrito el nombre y que el fichero existe.");

			return false;
		}
		// Error de sintaxis de lua
		else if (errorType == LUA_ERRSYNTAX)
		{
			showErrorMessage("ERROR DE LUA! - Error de sintaxis de lua al cargar el script \"" + std::string(script) + "\". Comprueba que no hay errores en el fichero de script.");

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al cargar el script \"" + std::string(script) + "\" : Memory allocation error.");

			return false;
		}
		// Error chungo de no se qué de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al cargar el script \"" + std::string(script) + "\" : Error chungo de no se qué de metamethod.");

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
				showErrorMessage("ERROR DE LUA! - Error de runtime de lua al ejecutar el script \"" + std::string(script) + "\": " + std::string(error));
			}
			else
				// En teoría esta situación no debería darse nunca, pero no está de más hacer la comprobación.
				showErrorMessage("ERROR DE LUA! - Error desconocido de runtime de lua al ejecutar el script \"" + std::string(script) + "\"");

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" + std::string(script) + "\" : Memory allocation error.");

			return false;
		}
		// Error ejecutando el message handler
		else if (errorType == LUA_ERRERR)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" + std::string(script) + "\" : Error ejecutando el message handler.");

			return false;
		}
		// Error chungo de no se qué de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" + std::string(script) + "\" : Error chungo de no se qué de metamethod.");

			return false;
		}

		return true;

	} // executeLastLoadScript

	//---------------------------------------------------------

	void CServer::showMessage(std::string &message)
	{
		std::cout << std::endl;
		std::cout << message;
		std::cout << std::endl;
		
	} // showMessage

	//---------------------------------------------------------

	void CServer::showErrorMessage(std::string &message)
	{
		std::cout << std::endl;
		std::cout << message;
		std::cout << std::endl;

		assert(!"Ha ocurrido un error con lua. Mira la consola para saber porqué.");
	
	} // showErrorMessage

	//---------------------------------------------------------

	//------------------------------------------------------//
	//				DEFINICIONES DE PLANTILLAS				//
	//------------------------------------------------------//

	template void CServer::setGlobal<int>(const char *name, const int& value);

	template bool CServer::executeProcedure<int>(const char *subroutineName, const int& param1);
	template bool CServer::executeFunction<int>(const char *subroutineName, const int& param1, int &result);

	template void CServer::registerFunction<void(*)()>(const char *name, void (*f)());

} // namespace ScriptManager