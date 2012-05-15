/**
@file EnemyMindAIController.cpp

Contiene la implementación del componente que controla la IA de la supermente.

@author Alberto Plaza
@date Mayo, 2012
*/

#include "EnemyMindAIController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CEnemyMindAIController);
	
	//---------------------------------------------------------

	bool CEnemyMindAIController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if (!IComponent::spawn(entity,map,entityInfo))
			return false;

		// Creo la tabla que me va a servir para almacenar la información de la supermente y publico su ID.
		std::stringstream script;
		script	<< "enemyMind = {} ";
		script	<< "enemyMind.ID = " << _entity->getEntityID();
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

		// Cojo el estado inicial.
		if (entityInfo->hasAttribute("initState"))
		{
			std::stringstream script;
			script	<< "enemyMind.state = " << entityInfo->getIntAttribute("initState");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script	<< "enemyMind.state = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		// Cojo la etapa inicial de la misión.
		if (entityInfo->hasAttribute("initStage"))
		{
			std::stringstream script;
			script	<< "enemyMind.stage = " << entityInfo->getIntAttribute("initStage");
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			std::stringstream script;
			script	<< "enemyMind.stage = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CEnemyMindAIController::activate()
	{
		return true;

	} // activate
	
	//---------------------------------------------------------

	void CEnemyMindAIController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CEnemyMindAIController::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CEnemyMindAIController::process(IMessage *message)
	{
		
	} // process

	//---------------------------------------------------------

	void CEnemyMindAIController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		_currentExeTime += msecs;

		// Ejecuto la IA si toca.
		if (_currentExeTime >= _exeTime)
		{
			std::stringstream script;
			script	<< "enemyMind.deltaTime = " << _currentExeTime << " ";
			script	<< "enemyMindAIAction()";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			_currentExeTime = 0;
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

