/**
@file Server.cpp

Contiene la implementaci�n de la clase CServer, Singleton que se encarga de
la gesti�n de los scripts del juego.

@see ScriptManager::CServer

@author Alberto Plaza
@date Marzo, 2012
*/

#include "Server.h"

#include "ScriptManager\Classes\Messages\LUA_AStarRoute.h"
#include "ScriptManager\Classes\Messages\LUA_AttackEntity.h"
#include "ScriptManager\Classes\Messages\LUA_SpawnEnemy.h"
#include "ScriptManager\Classes\Messages\LUA_AttackDistance.h"
#include "ScriptManager\Classes\Messages\LUA_EntitySelected.h"
#include "ScriptManager\Classes\Messages\LUA_CambiarDiaNoche.h"
#include "ScriptManager\Classes\Messages\LUA_UbicarCamara.h"
#include "ScriptManager\Classes\Messages\LUA_SetPlayerState.h"

#include "ScriptManager/Classes/LUA_EntityFunctions.h"

// Inclu�mos las cabedceras de Lua.
// Como es c�digo C (no C++), hay que indicarselo al
// compilador para que asuma el convenio de nombres
// de C en el c�digo objeto.
extern "C" 
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>  // Para inicializar la librer�a base de Lua
}

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

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
		// Con esto evitamos que otros (Lua) no cree mas referencias de la clase.
		if (_instance == 0)
		{
			_instance = this;
			_lua = NULL;
		}
		
	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		// Con esto evitamos que otros (Lua) no destruyan nuestro singleton.
		if (_instance == this)
			_instance = 0;

	} // ~CServer

	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicializaci�n de ScriptManager::CServer no permitida!");

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
		assert(_instance && "ScriptManager::CServer no est� inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		return CreateNewState();

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		UnloadCurrentState();

	} // close

	//---------------------------------------------------------

	bool CServer::CreateNewState()
	{
		// Obtengo el estado de lua (inicializaci�n de lua)
		_lua = luaL_newstate();

		if (!_lua)
			return false;

		// Abro las librer�as de lua (segunda parte de la inicializaci�n)
		luaL_openlibs(_lua);

		// Abrimos la librer�a base para hacer disponible
		// print() en Lua.
		luaopen_base(_lua);

		// Activamos luabind en el int�rprete
		luabind::open(_lua);

		//Registrar las clases que se van a usar desde LUA
		registerClasses();

		return true;
	}

	//---------------------------------------------------------

	void CServer::UnloadCurrentState()
	{
		if (_lua)
		{
			//lua_close(_lua);
		}

		_scriptList.clear();
	}

	//---------------------------------------------------------

	bool CServer::loadExeScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

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

		// Si he llegado aqu� es que todo ha ido bien, por lo tanto me guardo el script y muestro un mensaje de confirmaci�n.
		_scriptList.push_back(script);
		showMessage("Fichero \"" + std::string(script) + "\" cargado y ejecutado correctamente");

		return true;

	} // loadExeScript

	//---------------------------------------------------------

	bool CServer::executeScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

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
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		for (TScriptList::iterator it = _scriptList.begin(); it != _scriptList.end(); it++)
		{
			if (loadScript(it._Ptr->_Myval, false) && executeLastLoadScript(it._Ptr->_Myval))
				showMessage("Fichero \"" + std::string(it._Ptr->_Myval) + "\" cargado y ejecutado correctamente");
		}
	
	} // reloadScripts

	//---------------------------------------------------------

	int CServer::getGlobal(const char *name, int defaultValue)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gesti�n de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TNUMBER))
		{
			showErrorMessage("ERROR DE LUA! - La variable num�rica \"" + std::string(name) + "\" a la que se est� intentando acceder no existe en ning�n script de lua o no es de tipo num�rico.");

			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<int>(obj);

	} // getGlobal(int)

	//---------------------------------------------------------

	bool CServer::getGlobal(const char *name, bool &error)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gesti�n de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TBOOLEAN))
		{
			showErrorMessage("ERROR DE LUA! - La variable booleana \"" + std::string(name) + "\" a la que se est� intentando acceder no existe en ning�n script de lua o no es de tipo booleana.");

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
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gesti�n de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TSTRING))
		{
			showErrorMessage("ERROR DE LUA! - La variable de tipo cadena \"" + std::string(name) + "\" a la que se est� intentando acceder no existe en ning�n script de lua o no es de tipo cadena.");

			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<const char*>(obj);
		
	} // getGlobal(char*)

	//---------------------------------------------------------

	template <class T>
	void CServer::setGlobal(const char *name, const T& value)
	{
		luabind::globals(_lua)[name] = value;

	} // setGlobal

	//---------------------------------------------------------

	int CServer::getField(const char *table, const char *field, int defaultValue)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			showErrorMessage("ERROR DE LUA! - La tabla \"" + std::string(table) + "\" a la que se est� intentando acceder no existe o no es de tipo tabla.");
			
			return defaultValue;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TNUMBER))
		{
			showErrorMessage("ERROR DE LUA! - No existe ning�n campo \"" + std::string(field) + "\" en la tabla \"" + std::string(table) + "\" o no es de tipo entero.");
			
			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<int>(valor);
		
	} // getField(int)

	//---------------------------------------------------------

	bool CServer::getField(const char *table, const char *field, bool &error)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			showErrorMessage("ERROR DE LUA! - La tabla \"" + std::string(table) + "\" a la que se est� intentando acceder no existe o no es de tipo tabla.");
			
			error = true;
			return false;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TBOOLEAN))
		{
			showErrorMessage("ERROR DE LUA! - No existe ning�n campo \"" + std::string(field) + "\" en la tabla \"" + std::string(table) + "\" o no es de tipo booleano.");
			
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
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			showErrorMessage("ERROR DE LUA! - La tabla \"" + std::string(table) + "\" a la que se est� intentando acceder no existe o no es de tipo tabla.");
			
			return defaultValue;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TSTRING))
		{
			showErrorMessage("ERROR DE LUA! - No existe ning�n campo \"" + std::string(field) + "\" en la tabla \"" + std::string(table) + "\" o no es de tipo cadena.");
			
			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<const char*>(valor);
		
	} //getField(char*)

	//---------------------------------------------------------

	bool CServer::executeProcedure(const char *subroutineName)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo el procedimiento definido en lua
		luabind::object proc = luabind::globals(_lua)[subroutineName];

		// Compruebo que el procedimiento existe y es un procedimiento.
		if (!proc.is_valid() || (luabind::type(proc) != LUA_TFUNCTION))
		{
			showErrorMessage("ERROR DE LUA! - El procedimiento \"" + std::string(subroutineName) + "\" que se est� intentando ejecutar no existe o es un procedimiento.");

			return false;
		}

		// Lo ejecuto y hago comprobaci�n de errores.
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
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo el procedimiento definido en lua
		luabind::object proc = luabind::globals(_lua)[subroutineName];

		// Compruebo que el procedimiento existe y es un procedimiento.
		if (!proc.is_valid() || (luabind::type(proc) != LUA_TFUNCTION))
		{
			showErrorMessage("ERROR DE LUA! - El procedimiento \"" + std::string(subroutineName) + "\" que se est� intentando ejecutar no existe o es un procedimiento.");

			return false;
		}

		// Lo ejecuto y hago comprobaci�n de errores.
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
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la funci�n definida en lua
		luabind::object func = luabind::globals(_lua)[subroutineName];

		// Compruebo que la funci�n existe y es una funci�n.
		if (!func.is_valid() || (luabind::type(func) != LUA_TFUNCTION))
		{
			showErrorMessage("ERROR DE LUA! - La funci�n \"" + std::string(subroutineName) + "\" que se est� intentando ejecutar no existe o es una funci�n.");

			return false;
		}

		try {
			// Intento ejecutar la funci�n
			luabind::object res = func(param1);

			// Hago comprobaci�n de errores para asegurarme de que lo que me ha devuelto la funci�n es correcto.
			if (!res.is_valid() || (luabind::type(res) != LUA_TNUMBER))
			{
				showErrorMessage("ERROR DE LUA! - La funci�n \"" + std::string(subroutineName) + "\" no ha devuelto ning�n valor o el valor devuelto no es de tipo entero.");

				return false;
			}

			result = luabind::object_cast<int>(res);
			return true;

		} catch (luabind::error &ex) {
			showErrorMessage("ERROR DE LUA! - Error al ejecutar la funci�n \"" + std::string(subroutineName) + "\". Tipo de error: " + std::string(ex.what()));

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

	bool CServer::initCorutine(const char *corutineName, const char *corutineFunction, const char *resultName)
	{
		// Creo la corrutina.
		std::stringstream corutineCreate;
		corutineCreate << corutineName << " = coroutine.create(" << corutineFunction << ")";
		executeScript(corutineCreate.str().c_str());

		// Ejecuto la corrutina.
		std::stringstream corutineInit;
		corutineInit << "correct, " << resultName << " = coroutine.resume(" << corutineName << ")";
		executeScript(corutineInit.str().c_str());

		// Variable temporal para llamar a "getGlobal"
		bool result;

		// Devuelvo si la corrutina se ha ejecutado correctamente o no.
		return ScriptManager::CServer::getSingletonPtr()->getGlobal("correct", result);

	} // initCorutine

	//---------------------------------------------------------

	bool CServer::resumeCorutine(const char *corutineName, const char *resultName, const char *param)
	{
		// Ejecuto la corrutina
		std::stringstream corutineResume;
		corutineResume << "correct, " << resultName << " = coroutine.resume(" << corutineName << ", " << param <<")";
		executeScript(corutineResume.str().c_str());

		// Variable temporal para llamar a "getGlobal"
		bool result;

		// Devuelvo si la corrutina se ha ejecutado correctamente o no.
		return ScriptManager::CServer::getSingletonPtr()->getGlobal("correct", result);

	} // resumeCorutine

	//---------------------------------------------------------

	bool CServer::loadScript(const char *script, bool inmediate)
	{
		// Completo la ruta del script.
		std::stringstream filename;
		filename << "media\\scripts\\" << script << ".lua";

		// Cargo el fichero de script dependiendo del par�metro booleano.
		int errorType = 0;

		if (inmediate)
			errorType = luaL_loadstring(_lua, script);
		else
			errorType = luaL_loadfile(_lua, filename.str().c_str());

		// Error al cargar el fichero de script
		if (errorType == LUA_ERRFILE)
		{
			showErrorMessage("ERROR DE LUA! - Error al cargar el fichero de script \"" + std::string(script) + "\". Comprueba que est� bien escrito el nombre y que el fichero existe.");

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
		// Error chungo de no se qu� de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al cargar el script \"" + std::string(script) + "\" : Error chungo de no se qu� de metamethod.");

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
				// En teor�a esta situaci�n no deber�a darse nunca, pero no est� de m�s hacer la comprobaci�n.
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
		// Error chungo de no se qu� de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			showErrorMessage("ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" + std::string(script) + "\" : Error chungo de no se qu� de metamethod.");

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

		//assert(!"Ha ocurrido un error con lua. Mira la consola para saber porqu�.");
	
	} // showErrorMessage

	//---------------------------------------------------------

	void CServer::registerClasses()
	{
		//------------------------------------------------------//
		//			REGISTRO DEL SERVIDOR DE SCRIPTS				//
		//------------------------------------------------------//
		
		luabind::module(_lua) 
			[ 
				/** Note: ScriptManager is a class with static member functions */ 
				luabind::class_<CServer>("ScriptManager")
				.scope
				[
					luabind::def("getSingleton", &CServer::getSingletonPtr)
				]
				.def("loadScript", &CServer::loadExeScript)
			];

		luabind::globals(_lua)["SManager"] = CServer::getSingletonPtr();


		//------------------------------------------------------//
		//				REGISTRO DE LOS MENSAJES					//
		//------------------------------------------------------//

		// LUA_MAStarRoute

		luabind::module(_lua)
		[
			luabind::class_<LUA_MAStarRoute>("LUA_MAStarRoute")
				.def(luabind::constructor<>())
				.def("setDestPointX", (void (LUA_MAStarRoute::*) (float)) &LUA_MAStarRoute::setDestPointX)
				.def("setDestPointY", (void (LUA_MAStarRoute::*) (float)) &LUA_MAStarRoute::setDestPointY)
				.def("setDestPointZ", (void (LUA_MAStarRoute::*) (float)) &LUA_MAStarRoute::setDestPointZ)
				.def("setEntityTo", (void (LUA_MAStarRoute::*) (unsigned int)) &LUA_MAStarRoute::setEntityTo)
				.def("setStart", (void (LUA_MAStarRoute::*) (bool)) &LUA_MAStarRoute::setStart)
				.def("send", &LUA_MAStarRoute::send)
		];

		// LUA_MAttackEntity

		luabind::module(_lua)
		[
			luabind::class_<LUA_MAttackEntity>("LUA_MAttackEntity")
				.def(luabind::constructor<>())
				.def("setAttack", (void (LUA_MAttackEntity::*) (bool)) &LUA_MAttackEntity::setAttack)
				.def("setEntity", (void (LUA_MAttackEntity::*) (unsigned int)) &LUA_MAttackEntity::setEntity)
				.def("setEntityTo", (void (LUA_MAttackEntity::*) (unsigned int)) &LUA_MAttackEntity::setEntityTo)
				.def("send", &LUA_MAttackEntity::send)
				
		];

		// LUA_MSpawnEnemy

		luabind::module(_lua)
		[
			luabind::class_<LUA_MSpawnEnemy>("LUA_MSpawnEnemy")
				.def(luabind::constructor<>())
				.def("setEntityTo", (void (LUA_MSpawnEnemy::*) (unsigned int)) &LUA_MSpawnEnemy::setEntityTo)
				.def("setNumEnemies", (void (LUA_MSpawnEnemy::*) (int)) &LUA_MSpawnEnemy::setNumEnemies)
				.def("send", &LUA_MSpawnEnemy::send)
		];

		// LUA_MAttackEntity

		luabind::module(_lua)
		[
			luabind::class_<LUA_MAttackDistance>("LUA_MAttackDistance")
				.def(luabind::constructor<>())
				.def("setEntityTo", (void (LUA_MAttackDistance::*) (unsigned int)) &LUA_MAttackDistance::setEntityTo)
				.def("setEntity", (void (LUA_MAttackDistance::*) (unsigned int)) &LUA_MAttackDistance::setEntity)
				.def("setAttack", (void (LUA_MAttackDistance::*) (bool)) &LUA_MAttackDistance::setAttack)
				.def("setContinue", (void (LUA_MAttackDistance::*) (bool)) &LUA_MAttackDistance::setContinue)
				.def("send", &LUA_MAttackDistance::send)
		];

		// LUA_MEntitySelected
		luabind::module(_lua)
		[
			luabind::class_<LUA_MEntitySelected>("LUA_MEntitySelected")
				.def(luabind::constructor<>())
				.def("setEntityTo", (void (LUA_MEntitySelected::*) (unsigned int)) &LUA_MEntitySelected::setEntityTo)
				.def("setSelectedEntity", (void (LUA_MEntitySelected::*) (std::string)) &LUA_MEntitySelected::setSelectedEntity)
				.def("setSelectedEntity", (void (LUA_MEntitySelected::*) (unsigned int)) &LUA_MEntitySelected::setSelectedEntity)
				.def("setSelectedType", (void (LUA_MEntitySelected::*) (std::string)) &LUA_MEntitySelected::setSelectedType)
				.def("send", &LUA_MEntitySelected::send)
		];

		// LUA_MCambiarDiaNoche
		luabind::module(_lua)
		[
			luabind::class_<LUA_MCambiarDiaNoche>("LUA_MCambiarDiaNoche")
				.def(luabind::constructor<>())
				.def("setCambiarADia", (void (LUA_MCambiarDiaNoche::*) (bool)) &LUA_MCambiarDiaNoche::setCambiarADia)
				.def("send", &LUA_MCambiarDiaNoche::send)
		];

		// LUA_MUbicarCamara
		luabind::module(_lua)
			[
				luabind::class_<LUA_MUbicarCamara>("LUA_MUbicarCamara")
					.def(luabind::constructor<>())
					.def("setTarget", (void (LUA_MUbicarCamara::*) (unsigned int)) &LUA_MUbicarCamara::setEntityTo)
					.def("send", &LUA_MUbicarCamara::send)
			];

		// LUA_MSetStatePlayer
		luabind::module(_lua)
			[
				luabind::class_<LUA_MSetPlayerState>("LUA_MSetPlayerState")
					.def(luabind::constructor<>())
					.def("setEntityTo", (void (LUA_MSetPlayerState::*) (unsigned int)) &LUA_MSetPlayerState::setEntityTo)
					.def("setPlayerState", (void (LUA_MSetPlayerState::*) (std::string)) &LUA_MSetPlayerState::setPlayerState)
					.def("send", &LUA_MSetPlayerState::send)
			];

		// Funciones especiales
		luabind::module(_lua)
			[
				luabind::def("isPlayer", &isPlayer)
			];
		luabind::module(_lua)
			[
				luabind::def("isEnemy", &isEnemy)
			];
		luabind::module(_lua)
			[
				luabind::def("getEntityID", &getEntityID)
			];
		luabind::module(_lua)
			[
				luabind::def("getName", &getName)
			];
		luabind::module(_lua)
			[
				luabind::def("deleteEntity", &deleteEntity)
			];

		//---------------------------------------------------------

	}

	//---------------------------------------------------------

	//------------------------------------------------------//
	//				DEFINICIONES DE PLANTILLAS				//
	//------------------------------------------------------//

	template bool CServer::executeProcedure<int>(const char *subroutineName, const int& param1);
	template bool CServer::executeFunction<int>(const char *subroutineName, const int& param1, int &result);

	template void CServer::registerFunction<void(*)()>(const char *name, void (*f)());

	template void CServer::setGlobal<int>(const char *name, const int& value);

} // namespace ScriptManager