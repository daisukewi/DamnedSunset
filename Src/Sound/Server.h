/**
@file Server.h

Contiene la declaraci�n de la clase CServer, Singleton que se encarga de
la gesti�n de la m�sica del juego.

@see Sound::CServer

@author David Llans�
@date Agosto, 2010
*/
#ifndef __Sound_Server_H
#define __Sound_Server_H


/**
Namespace que engloba la l�gica del juego. Engloba desde el mapa l�gico
contenedor de todas las entidades del juego hasta las propias entidades,
sus componentes, mensajes, factorias de entidades y componentes, etc.
(para m�s informaci�n ver @ref SoundGroup).

@author David Llans�
@date Agosto, 2010
*/
namespace Sound
{
	/**
	

	@ingroup soundGroup

	@author David Llans�
	@date Agosto, 2010
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
		Funci�n llamada en cada frame para que se realicen las funciones
		de actualizaci�n adecuadas.
		<p>
		Llamar� al m�todo tick() del mapa.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		void tick(unsigned int msecs);

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

	}; // class CServer

} // namespace Sound

#endif // __Sound_Server_H
