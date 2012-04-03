/**
@file Script.cpp

Contiene la implementación del componente que contiene el control y la ejecución de los
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

namespace Logic
{
	IMP_FACTORY(CScript);

	//---------------------------------------------------------

	bool CScript::spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("script"))
			ScriptManager::CServer::getSingletonPtr()->loadExeScript(entityInfo->getStringAttribute("script").c_str());

		return true;

	} // spawn

	//---------------------------------------------------------

	bool CScript::activate()
	{
		return true;

	} // activate

	//---------------------------------------------------------

	void CScript::deactivate()
	{

	} // deactivate

	//---------------------------------------------------------

	bool CScript::accept(IMessage *message)
	{
		return (!message->getType().compare("MCureEntity"));

	} // accept

	//---------------------------------------------------------

	void CScript::process(IMessage *message)
	{
		if (!message->getType().compare("MCureEntity"))
		{
			ScriptManager::CServer::getSingletonPtr()->executeScript("hability = coroutine.create(healHability)");
			ScriptManager::CServer::getSingletonPtr()->executeScript("correct, result = coroutine.resume(hability)");
			int n = ScriptManager::CServer::getSingletonPtr()->getGlobal("result", 0);
			ScriptManager::CServer::getSingletonPtr()->executeScript("correct = coroutine.resume(hability, 28)");
			int n3 = 0;
		}

	} // process

	//---------------------------------------------------------

	void CScript::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

	//---------------------------------------------------------

} // namespace Logic