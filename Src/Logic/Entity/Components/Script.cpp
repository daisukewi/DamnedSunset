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
		{
			std::string s = entityInfo->getStringAttribute("script");
			ScriptManager::CServer::getSingletonPtr()->loadExeScript(s.c_str());
		}

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

	} // tick

	//---------------------------------------------------------

} // namespace Logic