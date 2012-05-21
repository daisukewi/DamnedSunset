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
		}
		else
		{
			std::stringstream script;
			script	<< "players[" << _entity->getEntityID() << "].state = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		if ((entityInfo->hasAttribute("memInitPoint")) && (entityInfo->getBoolAttribute("memInitPoint")))
		{
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].backToInitPoint = true";
			script << " players[" << _entity->getEntityID() << "].initPoint = { x = " << _entity->getPosition().x << ", y = " << _entity->getPosition().y << ", z = " << _entity->getPosition().z << " }";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].backToInitPoint = false";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
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
		/*
		// Busco todas las entidades de tipo Player del mapa.
		std::list<Logic::CEntity*> _playerEntities;
		Logic::CEntity *ent = _entity->getMap()->getEntityByType("Player");
		while (ent != NULL)
		{
			_playerEntities.push_back(ent);
			ent = _entity->getMap()->getEntityByType("Player", ent);
		}


		// Construyo la estructura de datos que me va a servir para saber a que jugadores veo.
		std::stringstream script;
		script << "enemies[" << _entity->getEntityID() << "].playersSeen = { ";

		std::list<Logic::CEntity*>::const_iterator it = _playerEntities.begin();
		script << "[" << (*it)->getEntityID() << "] = false";
		it++;
		for (; it != _playerEntities.end(); it++)
		{
			script << ", " << "[" << (*it)->getEntityID() << "] = false";
		}
		script << " }";

		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		*/
		return true;
		
	} // activate
	
	//---------------------------------------------------------

	void CPlayerAIController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPlayerAIController::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CPlayerAIController::process(IMessage *message)
	{
		
	} // process

	//---------------------------------------------------------

	void CPlayerAIController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		_currentExeFrames++;

		// Ejecuto la IA si toca.
		if (_currentExeFrames >= _exeFrames)
		{
			// Reinicio el contador de frames.
			_currentExeFrames = 0;

			// Actualizo la posición de la entidad y llamo a la función de la IA.
			std::stringstream script;
			script	<< "players[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
					<< "players[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
					<< "players[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z << " "
					<< "playerAIAction(" << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

