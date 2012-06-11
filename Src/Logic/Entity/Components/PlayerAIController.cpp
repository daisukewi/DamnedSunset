/**
@file PlayerAIController.cpp

Contiene la implementación del componente que controla la IA de los personajes.

@author Alberto Ortega
@date Mayo, 2012
*/

#include "PlayerAIController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/SetPlayerState.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CPlayerAIController);
	
	//---------------------------------------------------------

	bool CPlayerAIController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if (!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("initState"))
		{
			std::stringstream script;
			script	<< "players[" << _entity->getEntityID() << "].state = " << entityInfo->getIntAttribute("initState");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		
			std::stringstream script2;
			script2	<< "players[" << _entity->getEntityID() << "].secondaryState = "  << entityInfo->getIntAttribute("initState");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script2.str().c_str());
		}
		else
		{
			std::stringstream script;
			script	<< "players[" << _entity->getEntityID() << "].state = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		
			std::stringstream script2;
			script2	<< "players[" << _entity->getEntityID() << "].secondaryState = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script2.str().c_str());
		}

		if (entityInfo->hasAttribute("runLifeThreshold"))
		{
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].runLifeThreshold = " << entityInfo->getIntAttribute("runLifeThreshold");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].runLifeThreshold = 0";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CPlayerAIController::activate()
	{
		return true;
		
	} // activate
	
	//---------------------------------------------------------

	void CPlayerAIController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPlayerAIController::accept(IMessage *message)
	{
		return !message->getType().compare("MSetPlayerState")
			|| !message->getType().compare("MEntitySelected")
			|| !message->getType().compare("MEntityCreated");

	} // accept
	
	//---------------------------------------------------------

	void CPlayerAIController::process(IMessage *message)
	{
		if (!message->getType().compare("MSetPlayerState")){
			MSetPlayerState *m_state = static_cast <MSetPlayerState*> (message);
			
			if (m_state->getPlayerState() == Logic::SetPlayerStateMessage::PlayerState::HOLD){

				_state = "hold";
				std::cout << "PlayerAIController: " + _state + "\n";
			
				std::stringstream script;
				script << "playerEventParam = { state = \"" << _state << "\" } ";
				script << "playerEvent(\"StateChange\", " << _entity->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			}else if (m_state->getPlayerState() == Logic::SetPlayerStateMessage::PlayerState::FOLLOW){

				_state = "follow";
				std::cout << "PlayerAIController: " + _state + "\n";

				std::stringstream script;
				script << "playerEventParam = { state = \"" << _state << "\" } ";
				script << "playerEvent(\"StateChange\", " << _entity->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			}else if (m_state->getPlayerState() == Logic::SetPlayerStateMessage::PlayerState::IDLE){
				
				_state = "idle";
				std::cout << "PlayerAIController: " + _state + "\n";

				std::stringstream script;
				script << "playerEventParam = { state = \"" << _state << "\" } ";
				script << "playerEvent(\"StateChange\", " << _entity->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
			}else if (m_state->getPlayerState() == Logic::SetPlayerStateMessage::PlayerState::FOLLOW_PLAYER_MANUAL){
				
				_secondaryState = "follow_player_manual";
				std::cout << "PlayerAIController: " + _state + "\n";

				std::stringstream script;
				script << "playerSecondaryEventParam = { state = \"" << _state << "\" } ";
				script << "playerSecondaryEvent(\"StateChange\", " << _entity->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
			}else if (m_state->getPlayerState() == Logic::SetPlayerStateMessage::PlayerState::FOLLOW_PLAYER_AUTOMATIC){
				
				_secondaryState = "follow_player_automatic";
				std::cout << "PlayerAIController: " + _state + "\n";

				std::stringstream script;
				script << "playerSecondaryEventParam = { state = \"" << _state << "\" } ";
				script << "playerSecondaryEvent(\"StateChange\", " << _entity->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
			}

		}else if (!message->getType().compare("MEntityCreated")){
		
			std::cout << "ENTIDAD CREADA";
			std::cout << "ENTIDAD CREADA";
			std::cout << "ENTIDAD CREADA";
			std::cout << "ENTIDAD CREADA";
			std::cout << "ENTIDAD CREADA";
			std::cout << "ENTIDAD CREADA";
		}
	} // process

	//---------------------------------------------------------

	void CPlayerAIController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		//if (true){
		if (!_entity->getSelected() || _entity->getSecondarySelected()){
			
			_currentExeFrames += msecs;

			//Ejecuto la perfección si toca
			if (_currentExeFrames >= _exeFrames){
				// Reinicio el contador de frames.
				_currentExeFrames = 0;

				if (_entity->getSecondarySelected()){

					// Actualizo la posición de la entidad y llamo a la función de la IA.
					std::stringstream script;
					script	<< "players[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
							<< "players[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
							<< "players[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z << " "
							<< "playerSecondaryAIAction(" << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
					
				}else if (!_entity->getSelected()){
					
					// Actualizo la posición de la entidad y llamo a la función de la IA.
					std::stringstream script;
					script	<< "players[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
							<< "players[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
							<< "players[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z << " "
							<< "playerAIAction(" << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
					
				}
			}
		}else{
				_currentExeFrames += msecs;

				//Ejecuto la perfección si toca
				if (_currentExeFrames >= _exeFrames){
					// Reinicio el contador de frames.
					_currentExeFrames = 0;

					// Actualizo la posición de la entidad
					std::stringstream script;
					script	<< "players[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
							<< "players[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
							<< "players[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z;
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}
			}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

