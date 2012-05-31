/**
@file EnemyAIController.cpp

Contiene la implementación del componente que controla la IA de los enemigos.

@author Alberto Plaza
@date Mayo, 2012
*/

#include "EnemyAIController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CEnemyAIController);
	
	//---------------------------------------------------------

	bool CEnemyAIController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if (!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("initState"))
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].state = " << entityInfo->getIntAttribute("initState");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].state = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		if ((entityInfo->hasAttribute("memInitPoint")) && (entityInfo->getBoolAttribute("memInitPoint")))
		{
			std::stringstream script;
			script << "enemies[" << _entity->getEntityID() << "].backToInitPoint = true";
			script << " enemies[" << _entity->getEntityID() << "].initPoint = { x = " << _entity->getPosition().x << ", y = " << _entity->getPosition().y << ", z = " << _entity->getPosition().z << " }";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script << "enemies[" << _entity->getEntityID() << "].backToInitPoint = false";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		if (entityInfo->hasAttribute("runLifeThreshold"))
		{
			std::stringstream script;
			script << "enemies[" << _entity->getEntityID() << "].runLifeThreshold = " << entityInfo->getIntAttribute("runLifeThreshold");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script << "enemies[" << _entity->getEntityID() << "].runLifeThreshold = 0";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CEnemyAIController::activate()
	{
		return true;

	} // activate
	
	//---------------------------------------------------------

	void CEnemyAIController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CEnemyAIController::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CEnemyAIController::process(IMessage *message)
	{
		
	} // process

	//---------------------------------------------------------

	void CEnemyAIController::tick(unsigned int msecs)
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
			script	<< "enemies[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
					<< "enemies[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
					<< "enemies[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z << " "
					<< "AIAction(" << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

