/**
@file Server.h

Contiene la declaración de la clase CServer, Singleton que se encarga de
la gestión de Sonidos

@see Sonido::CServer

@author Luis Rojas
@date Feb, 2012
*/
#ifndef __Sound_Server_H
#define __Sound_Server_H

#include "../../dependencies/include/fmod/fmod.hpp"
#include "../../dependencies/include/fmod/fmod_errors.h"

#include "BaseSubsystems/Math.h"

#include <map>
#include <string>

using namespace std;
using namespace FMOD;
//namespace FMOD{
//class System;
//};

// Declaración de la clase
namespace Sounds
{
	enum soundType
	{
		UNASSIGNED = 0xFFFFFFFF,
		Sound3D,
		Sound2D
	};
	/**
	Servidor del módulo de sonido implementado con Fmod. Está 
	implementado como un singlenton de inicialización explícita. Sirve 
	para reproducir sonidos ambientales, efectos de sonido, y sonidos 3D.

	@ingroup Sound

	@author Luis Rojas
	@date Feb, 2012
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
		Función invocada en cada vuelta para actualización.

		@param secs Segundos desde que se reenderizó el último frame.
		*/
		void tick(float secs);


		/**
		Not implemented
		*/
		int createChannel(const char* name, bool paused, bool loop, soundType tipo );

		/**
		Creates a NORMAL channel with a Sound (NOT streamed, NOT 3D).
		*/
		bool createSound(const char* name, bool paused, bool loop);
		
		/**
		Pause or unpause the channel.
		*/
		bool pauseSound(const int n, bool paused);

		/**
		Creates a new channel with a 3D sound.
		*/
		bool create3DSound(const char* name, bool paused, bool loop);

		/**
		Creates a new channel with a sound of steam type.
		*/
		bool createSoundStream(const char* name, bool paused, bool loop);

		/**
		Set the position in the world for the sound.
		*/
		bool set3DSoundPosition(const int n, Vector3 pos);

		/**
		Sets the Velocity for the position of the sound.

		(doesnt work) <--
		*/
		bool set3DSoundVelocity(const int n, Vector3 vel);

		/**
		Sets the minimun distance for Attenuation, and the maximun distance for Attenuation of the sound.
		*/
		bool set3DSoundConstrains(const int n, float min, float max);

		/**
		Sets the volumen of the channel.
		*/
		bool setChannelVolumen(const int n, float volume);

		/**
		Sets the position of the listener.
		*/
		bool setListenerPos(Vector3 pos);

		/**
		*/
		Channel* getChannel(int n);


		bool playSound(int id,  const char* name);

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

		// función para dar salida de error y terminar aplicación
		bool SERRCHECK(FMOD_RESULT result);

		/**
		Única instancia de la clase.
		*/
		static CServer* _instance;

		/**
		// reminiscencias de C
		*/
		System *_audioSystem;

		/**
		Tipo de datos tabla de sonidos. Es una tabla hash
		de las STL.
		*/
		typedef std::map<std::string, Sound*> TSoundTable;

		/**
		Tipo de datos tabla de canales. Es una tabla hash
		de las STL.
		*/
		typedef std::map<int, Channel*> TChannelTable;

		/**
		Tabla hash con todos los sonidos
		*/
		TSoundTable _sounds;

		/**
		Tabla hash con todos los canales
		*/
		TChannelTable _channels;

		int _numCanales;


		/**
		Path de los archivos de sonido
		*/
		char* _path;

	}; // class CServer

} // namespace Sound

#endif // __Sound_Server_H
