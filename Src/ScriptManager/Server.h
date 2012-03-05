/**
@file Server.h

Contiene la declaración de la clase CServer, Singleton que se encarga de
la gestión de los scripts del juego.

@see ScriptManager::CServer

@author Alberto Plaza
@date Marzo, 2012
*/
#ifndef __ScriptManager_Server_H
#define __ScriptManager_Server_H

// Estructura con el contexto (estado) del intérprete de Lua.
struct lua_State;

typedef int (*lua_CFunction) (lua_State *L);

/**
Namespace para la gestión de los scripts del juego. Se encarga
de la carga y lectura de los mismos.

@author Alberto Plaza
@date Marzo, 2012
*/
namespace ScriptManager
{
	/**
	Clase servidor del ScriptManager. Se encarga de la gestión de los scripts; la carga y lectura de los
	mismos. Será la clase encargada de inicializar luabind y de establecer la conexión entre lua
	y el código C++.

	@author Alberto Plaza
	@date Marzo, 2012
	*/
	class CServer
	{
	public:

		/**
		Devuelve la única instancia de la clase CServer.
		
		@return Única instancia de la clase CServer.
		*/
		static CServer* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la instancia de CServer. Debe llamarse al finalizar la 
		aplicación.
		*/
		static void Release();

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
		Segunda fase de la construcción del objeto. Sirve para hacer
		inicializaciones de la propia instancia en vez de inicializaciones 
		estáticas.

		@return true si todo fue correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucción del objeto. Sirve para hacer liberar 
		los recursos de la propia instancia, la liberación de los recursos 
		estáticos se hace en Release().
		*/
		void close();

	private:
		/**
		Única instancia de la clase.
		*/
		static CServer* _instance;

		/**
		Atributo que representa la comunicación con lua desde el código C++.
		*/
		lua_State *_lua;

	}; // class CServer

} // namespace ScriptManager

#endif // __ScriptManager_Server_H
