/**
@file Script.cpp

Contiene la implementaci�n del componente que contiene el control y la ejecuci�n de los
scripts asociados a una entidad.

@see Logic::IComponent

@author Alberto Plaza
@date Enero, 2012
*/

#include "Script.h"

#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/Healed.h"
#include "Logic/Entity/Messages/CureEntity.h"
#include "Logic/Entity/Messages/ActivateSkill.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CScript);

	//---------------------------------------------------------

	bool CScript::spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("script"))
		{
			//std::string s = entityInfo->getStringAttribute("script");
			ScriptManager::CServer::getSingletonPtr()->loadExeScript(entityInfo->getStringAttribute("script").c_str());
		}

		if (entityInfo->hasAttribute("tickFunction"))
		{
			_tickFunction = true;
			_luaTickFunction = entityInfo->getStringAttribute("tickFunction").c_str();
		}
		else
			_tickFunction = false;

		if (entityInfo->hasAttribute("activateFunction"))
		{
			_activateFunction = true;
			_luaActivateFunction = entityInfo->getStringAttribute("activateFunction").c_str();
		}
		else
			_activateFunction = false;

		return true;

	} // spawn

	//---------------------------------------------------------

	bool CScript::activate()
	{
		if (_activateFunction)
		{
			std::stringstream script;
			script << _luaActivateFunction << "()";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;

	} // activate

	//---------------------------------------------------------

	void CScript::deactivate()
	{


	} // deactivate

	//---------------------------------------------------------

	bool CScript::accept(IMessage *message)
	{
		return false;

	} // accept

	//---------------------------------------------------------

	void CScript::process(IMessage *message)
	{


	} // process

	//---------------------------------------------------------

	void CScript::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_tickFunction)
		{
			std::stringstream script;
			script << _luaTickFunction << "(" << msecs << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic