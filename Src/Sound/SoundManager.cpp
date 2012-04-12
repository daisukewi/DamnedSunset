/**
@file SoundManager.cpp

@author Luis Rojas
@date Marzo 2012
*/

#include "BaseSubsystems/Math.h"
#include "SoundManager.h"

#include <string>

using namespace std;

namespace Sounds{
		CSoundManager* CSoundManager::_instance = 0;


		CSoundManager::CSoundManager() : _SoundServer(NULL)
		{
			_instance = this;
		} // CSoundManager

		CSoundManager::~CSoundManager()
		{
			_instance = 0;

		} // ~CSoundManager

		/**
		Inicialización de Sound Manager
		*/
		bool CSoundManager::Init()
		{
			assert(!_instance && "Segunda inicialización de Sounds::CSoundManager no permitida!");

			new CSoundManager();

			if (!_instance->open())
			{
				Release();
				return false;
			}

			return true;
		}

		/**
		Liberación de recursos de Sound Manager
		*/
		void CSoundManager::Release()
		{
			assert(_instance && "Sounds::CSoundManager no está inicializado!");
			if(_instance)
			{
				_instance->close();
				delete _instance;
			}

		}

		/**
		Crea un canal, con un sonido, si el sonido ya esta cargado
		se reusa en un nuevo canal.
		Devuelve el id del canal
		*/
		int CSoundManager::createChannel(const char* name, bool paused, bool loop, soundType tipo )
		{
			return _SoundServer->createChannel(name,paused,loop,tipo);
		}

		/** 
		Reproduce un sonido.
		*/
		bool CSoundManager::playSound(int id, const char* name)
		{
			if(_SoundServer->playSound(id,name))
			{
				return true;
			}else
			{
				return _SoundServer->pauseSound(id,false);
			}
		}

		/** 
		Reproduce un sonido.
		*/
		bool CSoundManager::pauseSound(int id,bool pause)
		{
			return _SoundServer->pauseSound(id,pause);
		}

		/** 
		SetSoundPosition
		*/
		bool CSoundManager::setSoundPosition(int id, Vector3 pos)
		{
			return _SoundServer->set3DSoundPosition(id,pos);
		}

		/** 
		Set Listener Position
		*/
		bool CSoundManager::setListenerPosition(Vector3 pos)
		{
			return _SoundServer->setListenerPos(pos);
		}

		/**
		Incia el Sound Manager
		*/
		bool CSoundManager::open()
		{
			_SoundServer = CServer::getSingletonPtr();

			if (_SoundServer)
				return true;

			return false;
		}

		/**
		Libera el SoundManager
		*/
		void CSoundManager::close()
		{
			_SoundServer = 0;
		}

}