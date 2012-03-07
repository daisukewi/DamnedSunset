/**
@file Server.h

Contiene la declaraci�n de la clase CServer, Singleton que se encarga de
la gesti�n de los scripts del juego.

@see ScriptManager::CServer

@author Alberto Plaza
@date Marzo, 2012
*/
#ifndef __ScriptManager_Server_H
#define __ScriptManager_Server_H

#include <list>

// Estructura con el contexto (estado) del int�rprete de Lua.
struct lua_State;

typedef int (*lua_CFunction) (lua_State *L);

/**
Namespace para la gesti�n de los scripts del juego. Se encarga
de la carga y lectura de los mismos.

@author Alberto Plaza
@date Marzo, 2012
*/
namespace ScriptManager
{
	/**
	Clase servidor del ScriptManager. Se encarga de la gesti�n de los scripts; la carga y lectura de los
	mismos. Ser� la clase encargada de inicializar luabind y de establecer la conexi�n entre lua
	y el c�digo C++.

	@author Alberto Plaza
	@date Marzo, 2012
	*/
	class CServer
	{
	public:

		/**
		Devuelve la �nica instancia de la clase CServer.
		
		@return �nica instancia de la clase CServer.
		*/
		static CServer* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la instancia de CServer. Debe llamarse al finalizar la 
		aplicaci�n.
		*/
		static void Release();

		/**
		Carga un fichero de script en lua y lo ejecuta.

		@param script nombre del fichero a cargar y ejecutar.
		@return true si todo fue bien y false en caso contrario.
		*/
		bool loadScript(const char *script);

	protected:
		/**
		Constructor.
		*/
		CServer ();

		/**
		Destructor.
		*/
		~CServer();

		/**
		Segunda fase de la construcci�n del objeto. Sirve para hacer
		inicializaciones de la propia instancia en vez de inicializaciones 
		est�ticas.

		@return true si todo fue correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucci�n del objeto. Sirve para hacer liberar 
		los recursos de la propia instancia, la liberaci�n de los recursos 
		est�ticos se hace en Release().
		*/
		void close();

	private:
		/**
		�nica instancia de la clase.
		*/
		static CServer* _instance;

		/**
		Atributo que representa la comunicaci�n con lua desde el c�digo C++.
		*/
		lua_State *_lua;

		/**
		Tipo lista de scripts cargados en el manager de scripts.
		*/
		typedef std::list<const char*> TScriptList;

		/**
		Lista de scripts cargados.
		*/
		TScriptList _scriptList;

	}; // class CServer

} // namespace ScriptManager

#endif // __ScriptManager_Server_H
