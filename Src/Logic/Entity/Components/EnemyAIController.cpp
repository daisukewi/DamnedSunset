/**
@file EnemyAIController.cpp

Contiene la implementación del componente que controla la IA de los enemigos.

@author Alberto Plaza
@date Mayo, 2012
*/

#include "EnemyAIController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CEnemyAIController);
	
	//---------------------------------------------------------

	bool CEnemyAIController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("initState"))
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].state = " << entityInfo->getIntAttribute("initState");
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
		if (_exeFrames >= _currentExeFrames)
		{
			// Reinicio el contador de frames.
			_currentExeFrames = 0;

			std::stringstream script;
			script	<< "AIAction(" << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

