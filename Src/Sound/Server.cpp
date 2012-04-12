//---------------------------------------------------------------------------
// Server.cpp
//---------------------------------------------------------------------------


/**
@file Server.h

Contiene la implementacion de la clase CServer, Singleton que se encarga de
la gestión de Sonidos

@see Sound::CServer

@author Luis Rojas
@date Feb, 2012
*/

#include "Server.h"
#include "SoundManager.h"

#include <assert.h>

#include "../../dependencies/include/fmod/fmod.hpp"
#include "../../dependencies/include/fmod/fmod_errors.h"

//using namespace std;
using namespace FMOD;

namespace Sounds {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer() : _audioSystem(NULL), _numCanales(0)
	{
		_instance = this;
		_path = "/Exes/media/sounds/";
	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicialización de Server::CServer no permitida!");

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
		assert(_instance && "Sound::CServer no está inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		if(!CSoundManager::Init())
		{
			cout << "unable to initialize CSoundManager " << endl;
			return false;
		}

		// Creamos un sistema
		FMOD_RESULT result;
		result = System_Create(&_audioSystem);
		if(SERRCHECK(result))
			return false;

		//Inicializamos el sistema
		result = _audioSystem->init(100, FMOD_INIT_NORMAL, 0);
		if(SERRCHECK(result))
			return false;

		float doppler = 1.0f; // ambos entre 0 y 1
		float rolloff = 1.0f;
		_audioSystem->set3DSettings(doppler,1.0,rolloff); //system->set3DSettings(doppler,1.0,rolloff);

		setListenerPos(Vector3(0,0,0));

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		if(_audioSystem)
			_audioSystem->release();

	} // close
	//--------------------------------------------------------

	void CServer::tick(float secs)
	{
		_audioSystem->update();
		//_audioSystem->getCPUUsage();

	}

	//--------------------------------------------------------
	bool CServer::createSound(const char* name, bool paused, bool loop)
	{
		FMOD_RESULT result;
		//Creando Sonido

		FMOD_MODE mode = FMOD_DEFAULT;
		if(loop)
			mode |= FMOD_LOOP_NORMAL;
		Sound *sound;

		//Si el sonido no existe lo guardamos en la tabla, si ya existía usamos el anterior
		TSoundTable::const_iterator soundIt;
		//Verificamos si no existe un sonido con el mismo nombre
		soundIt = _sounds.find(name);
		if(soundIt == _sounds.end()){
			result = _audioSystem->createSound(
			name, // path del arhivo de sonido
			mode, // flags FMOD_3D | FMOD_LOOP_NORMAL
			0, // información adicional (nada en este caso)
			& sound); // devolución del handle al buffer

			if(SERRCHECK(result))
				return false;

			_sounds[name] = sound;
		}else{
			cout << "Sonido::CServer: Usando recurso guardado" << endl;
			sound = _sounds[name];
		}

		//Creamos un Canal de audio
		Channel *canal;
		result = _audioSystem->playSound(
		FMOD_CHANNEL_FREE, // dejamos que FMOD seleccione cualquiera
		sound, // sonido que se “engancha” a ese canal
		paused, // arranca sin “pause” (se reproduce directamente)
		& canal); // devuelve el canal que asigna

		if(SERRCHECK(result))
			return false;

		//TChannelTable::const_iterator it;
		//// Comprobamos que no existe un caanal con ese nombre.
		//it = _channels.find(name);
		//assert(it == _channels.end() && "Sonido::CServer ya existe un canal con ese nombre");
		_channels[_numCanales++] = canal;

		return true;
	}

	//--------------------------------------------------------

	bool CServer::create3DSound(const char* name, bool paused, bool loop)
	{
		FMOD_RESULT result;
		//Creando Sonido
		FMOD_MODE mode = FMOD_DEFAULT | FMOD_3D;
		if(loop)
			mode |= FMOD_LOOP_NORMAL;

		Sound *sound;

		//Si el sonido no existe lo guardamos en la tabla, si ya existía usamos el anterior
		TSoundTable::const_iterator soundIt;
		//Verificamos si no existe un sonido con el mismo nombre
		soundIt = _sounds.find(name);
		if(soundIt == _sounds.end()){

			result = _audioSystem->createSound(
			name , // path del arhivo de sonido
			mode, // flags FMOD_3D | FMOD_LOOP_NORMAL
			0, // información adicional (nada en este caso)
			& sound); // devolución del handle al buffer

			if(SERRCHECK(result))
				return false;

			_sounds[name] = sound;
		}else{
			cout << "Sonido::CServer: Usando recurso guardado" << endl;
			sound = _sounds[name];
		}

		//Creamos un Canal de audio
		Channel *canal;
		result = _audioSystem->playSound(
		FMOD_CHANNEL_FREE, // dejamos que FMOD seleccione cualquiera
		sound, // sonido que se “engancha” a ese canal
		paused, // arranca sin “pause” (se reproduce directamente)
		& canal); // devuelve el canal que asigna

		if(SERRCHECK(result))
			return false;


		float minDist=5.0;
		float maxDist=20.0;
		result = canal->set3DMinMaxDistance(minDist,maxDist);
		if(SERRCHECK(result))
			return false;

		//TChannelTable::const_iterator it;
		//// Comprobamos que no existe un caanal con ese nombre.
		//it = _channels.find(name);
		//assert(it == _channels.end() && "Sonido::CServer ya existe un canal con ese nombre");
		//_channels[name] = canal;
		_channels[_numCanales++] = canal;

		return true;
	}

	//--------------------------------------------------------
	int CServer::createChannel(const char* name, bool paused, bool loop, soundType tipo )
	{
		FMOD_RESULT result;
		FMOD_MODE mode;
		switch(tipo)
		{
		case Sound3D:
			mode = FMOD_DEFAULT | FMOD_3D;
			break;
		case Sound2D:
			mode = FMOD_DEFAULT;
			break;
		default:
			break;
		}

		if(loop)
			mode |= FMOD_LOOP_NORMAL;

		Sound *sound;

		//Si el sonido no existe lo guardamos en la tabla, si ya existía usamos el anterior
		TSoundTable::const_iterator soundIt;
		//Verificamos si no existe un sonido con el mismo nombre
		soundIt = _sounds.find(name);
		if(soundIt == _sounds.end()){

			result = _audioSystem->createSound(
			name, // path del arhivo de sonido
			mode, // flags FMOD_3D | FMOD_LOOP_NORMAL
			0, // información adicional (nada en este caso)
			& sound); // devolución del handle al buffer

			if(SERRCHECK(result))
				return 0;

			_sounds[name] = sound;
		}else{
			cout << "Sonido::CServer: Usando recurso guardado" << endl;
			sound = _sounds[name];
		}

		//Creamos un Canal de audio
		Channel *canal;
		result = _audioSystem->playSound(
		FMOD_CHANNEL_FREE, // dejamos que FMOD seleccione cualquiera
		sound, // sonido que se “engancha” a ese canal
		paused, // arranca sin “pause” (se reproduce directamente)
		& canal); // devuelve el canal que asigna

		if(SERRCHECK(result))
			return 0;
		//float minDist=5.0;
		//float maxDist=20.0;
		//result = canal->set3DMinMaxDistance(minDist,maxDist);
		//if(SERRCHECK(result))
		//	return 0;
		_channels[++_numCanales] = canal;

		return _numCanales;
	}

	//--------------------------------------------------------
	
	bool CServer::setChannelVolumen(const int n, float volume)
	{
		TChannelTable::const_iterator it;
		// Comprobamos existe un caanal con ese nombre.
		it = _channels.find(n);
		if(it != _channels.end())
		{
			FMOD_RESULT result;
			result = (*it).second->setVolume(volume);
			if(SERRCHECK(result))
				return false;

			return true;
		}
		return false;
	}

	//--------------------------------------------------------

	bool CServer::setListenerPos(Vector3 pos)
	{
		FMOD_VECTOR
		listenerPos = {pos.x,pos.y,pos.z}, // posición del listener
		listenerVel = {0,0,0}, // velocidad
		up = {0,1,0}, // vector up: hacia la “coronilla”
		at = {1,0,0}; // vector at: hacia donde se mira

		// se coloca el listener
		_audioSystem->set3DListenerAttributes(0,&listenerPos, &listenerVel,&up, &at);

		return true;
	}

	//--------------------------------------------------------
	// función para dar salida de error y terminar aplicación
	bool CServer::SERRCHECK(FMOD_RESULT result){
			if (result != FMOD_OK){
				cout << "FMOD error! " << result << endl <<
				FMOD_ErrorString(result);
				return true;
			}
			return false;
	}

	//--------------------------------------------------------
	bool CServer::pauseSound(const int n, bool paused)
	{
		TChannelTable::const_iterator it;
		// Comprobamos existe un caanal con ese nombre.
		it = _channels.find(n);
		if(it != _channels.end())
		{
			//FMOD_RESULT result;

			(*it).second->setPaused(paused);
			//if(SERRCHECK(result))
			//	return false;

			return true;
		}

		return false;
	}
	//--------------------------------------------------------

	bool CServer::createSoundStream(const char* name, bool paused, bool loop)
	{
		FMOD_RESULT result;
		//Creando Sonido

		FMOD_MODE mode = FMOD_DEFAULT;
		if(loop)
			mode |= FMOD_LOOP_NORMAL;

		Sound *sound;
		//Si el sonido no existe lo guardamos en la tabla, si ya existía usamos el anterior
		//Verificamos si no existe un sonido con el mismo nombre
		TSoundTable::const_iterator soundIt;
		soundIt = _sounds.find(name);
		if(soundIt == _sounds.end()){

			result = _audioSystem->createStream(
			name, // path del arhivo de sonido
			mode, // flags FMOD_3D | FMOD_LOOP_NORMAL
			0, // información adicional (nada en este caso)
			& sound); // devolución del handle al buffer

			if(SERRCHECK(result))
				return false;

			_sounds[name] = sound;
		}else{
			cout << "Sonido::CServer: Usando recurso guardado" << endl;
			sound = _sounds[name];
		}

		//Creamos un Canal de audio
		Channel *canal;
		result = _audioSystem->playSound(
		FMOD_CHANNEL_FREE, // dejamos que FMOD seleccione cualquiera
		sound, // sonido que se “engancha” a ese canal
		paused, // arranca sin “pause” (se reproduce directamente)
		& canal); // devuelve el canal que asigna

		if(SERRCHECK(result))
			return false;

		//TChannelTable::const_iterator it;
		//// Comprobamos que no existe un caanal con ese nombre.
		//it = _channels.find(name);
		//assert(it == _channels.end() && "Sonido::CServer ya existe un canal con ese nombre");
		//_channels[name] = canal;
		_channels[_numCanales++] = canal;

		return true;
	}

	//--------------------------------------------------------
	
	Channel* CServer::getChannel(int n)
	{

		TChannelTable::const_iterator it;
		//// Comprobamos existe un canal con ese nombre.
		it = _channels.find(n);
		if(it != _channels.end()){
			return (*it).second;
		}

		return NULL;
	}

	//--------------------------------------------------------

	bool CServer::set3DSoundPosition(const int n, Vector3 pos)
	{
		FMOD_VECTOR pos2={pos.x,pos.y,pos.z}, vel={0,0,0};
		TChannelTable::const_iterator it;

		// Comprobamos existe un caanal con ese nombre.
		it = _channels.find(n);
		if(it != _channels.end()){

			FMOD_RESULT result;
			result = (*it).second->set3DAttributes(&pos2,&vel);
			if(SERRCHECK(result))
			 return false;
			return true;
		}

		return false;
	}

	//--------------------------------------------------------

	bool CServer::set3DSoundVelocity(const int n, Vector3 vel)
	{
		FMOD_VECTOR pos2={0,0,0}, vel2={vel.x,vel.y,vel.z};
		TChannelTable::const_iterator it;

		// Comprobamos existe un caanal con ese nombre.
		it = _channels.find(n);
		if(it != _channels.end()){

			FMOD_RESULT result;
			result = (*it).second->set3DAttributes(&pos2,&vel2);
			if(SERRCHECK(result))
			 return false;

			FMOD_VECTOR posicionFinal={0,0,0}, velFinal={vel.x,vel.y,vel.z};

			(*it).second->get3DAttributes(&posicionFinal,&velFinal);

			cout<< "Posicion final:" << posicionFinal.x << "," << posicionFinal.y << "," << posicionFinal.z << endl;

			return true;
		}

		return false;
	}

	//--------------------------------------------------------

	bool CServer::set3DSoundConstrains(const int n, float min, float max)
	{
		TChannelTable::const_iterator it;

		// Comprobamos existe un caanal con ese nombre.
		it = _channels.find(n);
		if(it != _channels.end()){

			FMOD_RESULT result;
			result = (*it).second->set3DMinMaxDistance(min,max);
			if(SERRCHECK(result))
				return false;

			return true;
		}

		return false;
	}

	//--------------------------------------------------------

	bool CServer::playSound(int id,  const char* name)
	{
		// Comprobamos existe un canal con ese id.
		TChannelTable::iterator it;
		it = _channels.find(id);
		if(it != _channels.end()){
			bool isplaying = false;
			FMOD_RESULT result;
			FMOD::Sound *sonido = 0;

			// Comprobamos existe un sonido con ese nombre.
			TSoundTable::iterator itSound;
			itSound = _sounds.find(name);
			if(itSound != _sounds.end()){
				sonido = itSound->second;
			}
			else
			{
				cout << "CServer: No se encuentra el sonido" << endl;
				return false;
			}

			result = it->second->isPlaying(&isplaying);

			if (isplaying == true)
			{
				cout << "CServer: Already playing this sound try to unpause" << endl;
				return false;  // Already playing this sound
			}

			// Start the sound
			Channel *canal;
			result = _audioSystem->playSound(FMOD_CHANNEL_FREE, sonido , false, &canal);
			if(SERRCHECK(result))
			{
				cout << "CServer: No se pudo reproducir el sonido" << endl;
				return false;
			}

			it->second = canal;
			return true;
		}
		else
		{
			cout << "CServer: No existe tal canal" <<endl;
			return false;
		}//if iterator

	}//playSound

	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------


} // namespace Sonido
