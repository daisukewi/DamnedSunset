/**
@file Sonido.cpp

Contiene la implementación del componente que controla la reproducción de un sonido 
 
@see Logic::CSonido
@see Logic::IComponent

@author Alberto ORtega
@date Marzo, 2011
*/

#include "Sonido.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Application/BaseApplication.h"

#include "Sound/Server.h"
#include "Sound/SoundManager.h"

#include "Logic/Entity/Messages/SetTransform.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Sound/Sound.h"



namespace Logic 
{
	IMP_FACTORY(CSonido);
	

	//---------------------------------------------------------

	bool CSonido::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		/*
		_id = new char [_Sonido.size()+1];
		strcpy (_id, _Sonido.c_str());

		_idChannel =
			Sounds::CSoundManager::getSingleton()->createChannel(_id,true,_loop,_type);
			//Sounds::CServer::getSingletonPtr()->createChannel(_id,true,_loop,_type);
		if(_idChannel == 0)
		{
			std::cout << "CSonido: no se pudo crear el sonido: " << _idChannel << std::endl;
		}
		*/
		/**

		*/
		for (int i = 0; i < numSounds; i++){
			_sound[i] = new Sounds::CSound();
		}
		
		countSounds = 0;
		
		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSonido::accept(IMessage *message)
	{
		return (!message->getType().compare("MSetTransform") ||
			!message->getType().compare("MSoundEffect"));

	} // accept
	
	//---------------------------------------------------------

	void CSonido::process(IMessage *message)
	{
		if (!message->getType().compare("MSetTransform")){
			MSetTransform *m = static_cast <MSetTransform*> (message);

			for (int i=0; (i < numSounds);i++){
				if (_sound[i]){
					//Sounds::CSoundManager::getSingleton()->setSoundPosition(_sound[i]->getIdChannel(),m->getTransform().getTrans());
				Sounds::CServer::getSingletonPtr()->set3DSoundPosition(_sound[i]->getIdChannel(),m->getTransform().getTrans());
				_sound[i]->setPosition(m->getTransform().getTrans());
				}
			}
			
		}else if (!message->getType().compare("MSoundEffect")){

			MSoundEffect *m = static_cast <MSoundEffect*> (message);

			
			countSounds++;
			if (countSounds >= numSounds)
				countSounds = 0;

			_sound[countSounds]->setSound(m->getSoundEffect());
			char* id = new char [_sound[countSounds]->getSound().size()+1];
			_sound[countSounds]->setId(id);
			strcpy (id, _sound[countSounds]->getSound().c_str());
			
			_sound[countSounds]->setIdChannel(Sounds::CSoundManager::getSingleton()->createChannel(_sound[countSounds]->getSound().c_str(),false,_sound[countSounds]->getLoop(),_sound[countSounds]->getSoundType()));
			if (_sound[countSounds]->getIdChannel() == 0){
				std::cout << "CSonido: no se pudo crear el sonido: " << _sound[countSounds]->getIdChannel() << std::endl;
			}

		}

		
	} // process

	//---------------------------------------------------------

	void CSonido::tick(unsigned int msecs)
	{

	}

	//---------------------------------------------------------

	bool CSonido::activate()
	{	
		for (int i = 0; i < numSounds; i++){
			_sound[i] = new Sounds::CSound();
		}

		return true;
	}

	//---------------------------------------------------------

	void CSonido::deactivate()
	{
		for (int i = 0; i < numSounds; i++){
			delete(_sound[i]);

		}

	}

	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

} // namespace Logic

