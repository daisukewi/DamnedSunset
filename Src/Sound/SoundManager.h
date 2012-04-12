/**
@file SoundManager.h

@author Luis Rojas
@date Marzo 2012
*/

#ifndef _Sound_MANAGER_H
#define _Sound_MANAGER_H

#include "BaseSubsystems/Math.h"
#include "Server.h"

#include <string>

using namespace std;

namespace Sounds{

	class CSoundManager{

	public:

		/**
		Inicialización de Sound Manager
		*/
		static bool Init();

		/**
		Liberación de recursos de Sound Manager
		*/
		static void Release();

		/** Instancia del Singleton */
		static CSoundManager *getSingleton(){return _instance;}

		/**
		Crea un canal, con un sonido, si el sonido ya esta cargado
		se reusa en un nuevo canal.
		Devuelve el id del canal
		*/
		int createChannel(const char* name, bool paused, bool loop, soundType tipo );

		/** 
		Reproduce un sonido.
		*/
		bool playSound(int id, const char* name);

		/** 
		Reproduce un sonido.
		*/
		bool pauseSound(int id,bool pause);

		/** 
		SetSoundPosition
		*/
		bool setSoundPosition(int id, Vector3 pos);

		/** 
		Set Listener Position
		*/
		bool setListenerPosition(Vector3 pos);

	protected:

		/**
		Constructor, por defecto vacío
		*/
		CSoundManager();

		/**
		Destructor, libera la instancia del Singleton
		*/
		~CSoundManager();

		/**
		Incia el Sound Manager
		*/
		bool open();

		/**
		Libera el SoundManager
		*/
		void close();

		/** Instancia única de la clase para el Singleton */
		static CSoundManager *_instance;

		Vector3 _listener;

		CServer *_SoundServer;
		
	}; // class CSoundManager

}

#endif // _Sound_MANAGER_H