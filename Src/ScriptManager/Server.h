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

#include <list>

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

		/**
		Carga un fichero de script en lua y lo ejecuta. Lo guarda
		en la lista de scripts cargados para no cargarlo una segunda vez
		y para poder recargarlo "en caliente".

		@param script nombre del fichero a cargar y ejecutar.
		@return true si todo fue bien y false en caso contrario.
		*/
		bool loadExeScript(const char *script);

		/**
		Ejecuta una línea de texto como script de lua. La línea de
		texto puede ser una sentencia de lua o una función de un
		fichero anteriormente cargado.

		@param script línea de texto a ejecutar.
		@return true si todo fue bien y false en caso contrario.
		*/
		bool executeScript(const char *script);

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
		Carga un fichero de script haciendo todo el manejo de errores y
		mostrando por consola los mensajes pertinentes.

		@param script nombre del script a cargar.
		@param inmediate true si queremos cargar y ejecutar el script en modo inmediato y false en caso contrario.
		@return true si la carga fue bien y false en caso contrario.

		@note Esta función no ejecuta el script, solo lo carga y lo deja preparado
		para su ejecución. Tampoco hace la gestión de qué scripts se han cargado ya
		o guardar los nuevos.
		*/
		bool loadScript(const char *script, bool inmediate);

		/**
		Ejecuta el último script cargado y hace el manejo de errores,
		mostrando por consola los mensajes pertinentes.

		@param script nombre del último script cargado (se utiliza para mostrar los mensajes de error).
		@return true si la ejecución fue bien y false en caso contrario.
		*/
		bool executeLastLoadScript(const char *script);

		/**
		Única instancia de la clase.
		*/
		static CServer* _instance;

		/**
		Atributo que representa la comunicación con lua desde el código C++.
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
