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
		Carga un fichero de script en lua y lo ejecuta. Lo guarda
		en la lista de scripts cargados para no cargarlo una segunda vez
		y para poder recargarlo "en caliente".

		@param script nombre del fichero a cargar y ejecutar.
		@return true si todo fue bien y false en caso contrario.
		*/
		bool loadExeScript(const char *script);

		/**
		Ejecuta una l�nea de texto como script de lua. La l�nea de
		texto puede ser una sentencia de lua o una funci�n de un
		fichero anteriormente cargado.

		@param script l�nea de texto a ejecutar.
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
		Carga un fichero de script haciendo todo el manejo de errores y
		mostrando por consola los mensajes pertinentes.

		@param script nombre del script a cargar.
		@param inmediate true si queremos cargar y ejecutar el script en modo inmediato y false en caso contrario.
		@return true si la carga fue bien y false en caso contrario.

		@note Esta funci�n no ejecuta el script, solo lo carga y lo deja preparado
		para su ejecuci�n. Tampoco hace la gesti�n de qu� scripts se han cargado ya
		o guardar los nuevos.
		*/
		bool loadScript(const char *script, bool inmediate);

		/**
		Ejecuta el �ltimo script cargado y hace el manejo de errores,
		mostrando por consola los mensajes pertinentes.

		@param script nombre del �ltimo script cargado (se utiliza para mostrar los mensajes de error).
		@return true si la ejecuci�n fue bien y false en caso contrario.
		*/
		bool executeLastLoadScript(const char *script);

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
