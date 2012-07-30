/**
@file EnemyAIController.cpp

Contiene la implementación del componente que controla las habilidades de los personajes.

@author Alberto Plaza
@date Julio, 2012
*/

#include "SkillsController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CSkillsController);
	
	//---------------------------------------------------------

	bool CSkillsController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if (!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("activateSkillsFunction"))
		{
			_activateSkillsFunction = true;
			_luaActivateSkillsFunction = entityInfo->getStringAttribute("activateSkillsFunction").c_str();
		}
		else
			_activateSkillsFunction = false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSkillsController::activate()
	{
		if (_activateSkillsFunction)
		{
			std::stringstream script;
			script << _luaActivateSkillsFunction << "(" << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CSkillsController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSkillsController::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CSkillsController::process(IMessage *message)
	{
		
	} // process

	//---------------------------------------------------------

	void CSkillsController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

	//---------------------------------------------------------

} // namespace Logic

