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
#include <string>

// Estructura con el contexto (estado) del int�rprete de Lua.
struct lua_State;

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
		Crea un nuevo estado de lua.
		Este m�todo tiene que ser llamado despu�s de inicializar el servidor
		y antes de poder utilizar cualquier funcionalidad de LUA.

		@return Devuelve false si no ha podido crear un nuevo estado de lua.
		*/
		bool CreateNewState();

		/**
		Descarga el estado actual de LUA liberando toda la memoria que haya
		reservado anteriormente.
		Este m�todo debe ser llamado antes de volver a crear un nuevo estado.
		*/
		void UnloadCurrentState();

		/**
		Carga un fichero de script en lua y lo ejecuta. Lo guarda
		en la lista de scripts cargados para no cargarlo una segunda vez
		y para poder recargarlo "en caliente".

		@param script nombre del fichero a cargar y ejecutar.
		@return true si todo fue bien y false en caso contrario.

		@note Hay que tener en cuenta que aunque la ejecuci�n no haya ido
		bien, si la carga se ha realizado con �xito, el script queda guardado,
		por lo que para volver a probarlo no har�a falta volver a cargarlo, sino
		llamar a la funci�n de recarga.
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

		/**
		Recarga y ejecuta todos los ficheros de script almacenados. Por
		cada uno muestra un mensaje indicando que se ha cargado y ejecutado
		correctamente o un mensaje de error en caso de que algo haya ido mal.
		*/
		void reloadScripts();

		/**
		Obtiene el valor de una variable global en Lua
		de tipo num�rico entero a partir de su nombre.
		 
		@param name Nombre de la variable global que
		se quiere obtener.
		@param defaultValue Valor que se devolver� 
		si no existe esa variable global en Lua.
		 
		@return Valor de la variable global de Lua, 
		o <tt>defaultValue</tt> si no exist�a.
		 
		@note En Lua el tipo num�rico es en principio
		<tt>double</tt>. Aqu� sin embargo devolvemos
		un entero.
		*/
		int getGlobal(const char *name, int defaultValue);

		/**
		Obtiene el valor de una variable global en Lua
		de tipo bool a partir de su nombre.
		 
		@param name Nombre de la variable global que
		se quiere obtener.
		@param error Variable booleana que indica si
		ha habido un error accediendo a la variable. Es true
		si ha habido alg�n error y false en caso contrario.
		 
		@return Valor de la variable global de Lua, 
		o false si no exist�a.
		*/
		bool getGlobal(const char *name, bool &error);

		/**
		Obtiene el valor de una variable global en Lua
		de tipo cadena a partir de su nombre.
	 
		@param name Nombre de la variable global que
		se quiere obtener.
		@param defaultValue Valor que se devolver� 
		si no existe esa variable global en Lua.
	 
		@return Valor de la variable global de Lua, 
		o <tt>defaultValue</tt> si no exist�a.
	 
		@note El invocante asume la posesi�n del puntero
		devuelto, que tendr� que ser liberado con
		<tt>free</tt>. Esta liberaci�n es necesaria
		<em>incluso aunque se haya devuelto
		<tt>defaultValue</tt></em> (se habr� hecho una
		copia).
	 
		@note Esta funci�n tiene un peligro potencial;
		Lua soporta cadenas con <tt>'\\0'</tt> en su
		interior. Aqu� <em>asumiremos que no lo tienen</em>
		porque usamos el <tt>'\\0'</tt> como marca de
		fin de cadena por simplicidad.
		*/
		const char *getGlobal(const char *name, const char *defaultValue);

		/**
		Establece el valor de una variable global en lua. Si ya 
		existe esa variable se sobreescribe.

		@param name Nombre de la variable.
		@param value Valor de la variable.
		*/
		template <class T>
		void setGlobal(const char *name, const T& value);

		/**
		Obtiene el valor de un campo de tipo num�rico de
		una tabla global.
	 
		@param table Nombre de la tabla (global) a la que
		se quiere acceder.
		@param field Nombre del campo (�ndice) cuyo valor se
		desea obtener.
		@param defaultValue Valor que se devolver� 
		si no existe la tabla o ese campo (�ndice) no
		es de tipo num�rico (o no hay una conversi�n posible).
	 
		@return Valor del campo solicitado, 
		o <tt>defaultValue</tt> si no exist�a.
	 
		@note En Lua el tipo num�rico es en principio
		<tt>double</tt>. Aqu� sin embargo devolvemos
		un entero.
		*/
		int getField(const char *table, const char *field, int defaultValue);

		/**
		Obtiene el valor de un campo de tipo booleano de
		una tabla global.
	 
		@param table Nombre de la tabla (global) a la que
		se quiere acceder.
		@param field Nombre del campo (�ndice) cuyo valor se
		desea obtener.
		@param error Variable booleana que indica si
		ha habido un error accediendo a la variable de la tabla. Es true
		si ha habido alg�n error y false en caso contrario.
	 
		@return Valor del campo solicitado, 
		o false si no exist�a.
		*/
		bool getField(const char *table, const char *field, bool &error);

		/**
		Obtiene el valor de un campo de tipo cadena de
		una tabla global.
	 
		@param table Nombre de la tabla (global) a la que
		se quiere acceder.
		@param field Nombre del campo (�ndice) cuyo valor se
		desea obtener.
		@param defaultValue Valor que se devolver� 
		si no existe la tabla o ese campo (�ndice) no
		es de tipo cadena (o no hay una conversi�n posible).
	 
		@return Valor del campo solicitado, 
		o <tt>defaultValue</tt> si no exist�a.
	 
		@note El invocante asume la posesi�n del puntero
		devuelto, que tendr� que ser liberado con
		<tt>free</tt>. Esta liberaci�n es necesaria
		<em>incluso aunque se haya devuelto
		<tt>defaultValue</tt></em> (se habr� hecho una
		copia).
	 
		@note Esta funci�n tiene un peligro potencial;
		Lua soporta cadenas con <tt>'\\0'</tt> en su
		interior. Aqu� <em>asumiremos que no lo tienen</em>
		porque usamos el <tt>'\\0'</tt> como marca de
		fin de cadena por simplicidad.
		*/
		const char *getField(const char *table, const char *field, const char *defaultValue);

		/**
		Ejecuta un procedimiento de lua sin par�metros y sin
		valores de vuelta.

		@param subroutineName Nombre del procedimiento.

		@return true si la ejecuci�n del procedimiento fue bien
		y false en caso contrario.
		*/
		bool executeProcedure(const char *subroutineName);

		/**
		M�todo templatizado que ejecuta un procedimiento de 
		lua con un par�metro de entrada y sin valor de vuelta

		@param subroutineName Nombre del procedimiento.
		@param param1 par�metro del procedimiento.

		@return true si la ejecuci�n del procedimiento fue bien
		y false en caso contrario.

		@note Esta es una plantilla definida en el fichero .cpp
		de la clase, por tanto la definici�n de la misma no puede
		quedarse como gen�rica ya que el compilador no lo acepta.
		Para instanciar la plantilla y que pueda compilar pero que
		al mismo tiempo la definici�n del m�todo quede lo suficientemente
		gen�rica, se han definido instancias concretas al final del
		fichero .cpp. Para cualquier instancia nueva que se necesite
		de la plantilla basta con definir una nueva l�nea con el
		tipo deseado en la secci�n concreta del fichero .cpp.
		*/
		template <class T>
		bool executeProcedure(const char *subroutineName, const T& param1);

		/**
		M�todo templatizado que ejecuta una funci�n de lua 
		con un par�metro de entrada y con un valor de vuelta 
		de tipo entero.

		@param subroutineName Nombre de la funci�n.
		@param param1 par�metro de la funci�n.
		@param result valor devuelto por la funci�n de lua.

		@return true si la ejecuci�n de la funci�n fue bien
		y false en caso contrario.

		@note Esta es una plantilla definida en el fichero .cpp
		de la clase, por tanto la definici�n de la misma no puede
		quedarse como gen�rica ya que el compilador no lo acepta.
		Para instanciar la plantilla y que pueda compilar pero que
		al mismo tiempo la definici�n del m�todo quede lo suficientemente
		gen�rica, se han definido instancias concretas al final del
		fichero .cpp. Para cualquier instancia nueva que se necesite
		de la plantilla basta con definir una nueva l�nea con el
		tipo deseado en la secci�n concreta del fichero .cpp.
		*/
		template <class T>
		bool executeFunction(const char *subroutineName, const T& param1, int &result);

		/**
		M�todo templatizado que registra una funci�n de C++ en el 
		contexto de lua. La funci�n a registrar no debe ser miembro 
		de ninguna clase ni estar incluida en ning�n espacio de nombres.

		@param name Nombre que tendr� la funci�n en el contexto de lua.
		@param f Puntero a la funci�n de C++.

		@note Esta es una plantilla definida en el fichero .cpp
		de la clase, por tanto la definici�n de la misma no puede
		quedarse como gen�rica ya que el compilador no lo acepta.
		Para instanciar la plantilla y que pueda compilar pero que
		al mismo tiempo la definici�n del m�todo quede lo suficientemente
		gen�rica, se han definido instancias concretas al final del
		fichero .cpp. Para cualquier instancia nueva que se necesite
		de la plantilla basta con definir una nueva l�nea con el
		tipo deseado en la secci�n concreta del fichero .cpp.
		*/
		template <class F>
		void registerFunction(const char *name, F f);

		/**
		M�todo que crea e inicia una corrutina de lua con el nombre y la funci�n
		pasadas como par�metro.

		@param corutineName Nombre con el que se va a crear la corrutina.
		@param corutineFunction Nombre de la funci�n a partir de la cual se va a
		crear la corrutina.
		@param resultName Nombre de la variable global de lua donde se va a guardar 
		el resultado devuelto por el primer yield del script.

		@return true si la corrutina se ha ejecutado y pausado con �xito o no.
		*/
		bool initCorutine(const char *corutineName, const char *corutineFunction, const char *resultName);

		/**
		M�todo que continua una corrutina pausada pas�ndole un par�metro en formato de cadena de caracteres.

		@param corutineName Nombre de la corutina que hay que despertar.
		@param resultName Nombre de la variable global de lua donde se va a guardar
		el resultado devuelto por el siguiente yield del script.
		@param param Par�metro a pasarle al yield del script actual. Independientemente del formato
		de la variable hay que pasarlo en formato texto de forma que lo entienda lua.

		@return true si la corrutina se ha ejecutado y pausado con �xito hasta el siguiente
		yield o no.
		*/
		bool resumeCorutine(const char *corutineName, const char *resultName, const char *param);

		/**
		Devuelve el estado de lua, que es la variable representativa
		de lua en C++.

		@return El estado de lua.
		*/
		lua_State *getLuaState() {return _lua;}

	protected:

		/**
		Constructor.
		*/
		CServer();

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
		Muestra un mensaje por consola.

		@param message Mensaje a mostrar.
		*/
		void showMessage(std::string &message);

		/**
		Muestra un mensaje de error por consola y salta un assert.

		@param message Mensaje de error a mostrar.
		*/
		void showErrorMessage(std::string &message);
		
		/**
		Registra los objetos C++ que vas a ser necesarios en LUA
		*/
		void registerClasses();

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