/**
@file PanelSolarController.cpp

Contiene la implementación del componente que controla el comportamiento de los paneles solares.
 
@see Logic::CPanelSolarController
@see Logic::IComponent

@author Luis Mendoza
@date Julio, 2012
*/

#include "PanelSolarController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/DayNight.h"

namespace Logic 
{
	IMP_FACTORY(CPanelSolarController);
	
	//---------------------------------------------------------

	bool CPanelSolarController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("radioEnergy"))
		{
			_radioEnergy = entityInfo->getFloatAttribute("radioEnergy");
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CPanelSolarController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CPanelSolarController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPanelSolarController::accept(IMessage *message)
	{
		return (!message->getType().compare("MDayNight"));

	} // accept
	
	//---------------------------------------------------------

	void CPanelSolarController::process(IMessage *message)
	{
		if (!message->getType().compare("MDayNight"))
		{
			MDayNight *m_anochecer = static_cast <MDayNight*> (message);
			if (m_anochecer->getTime() == TIME_TYPE::NIGHT)
			{
				std::stringstream script;
				script	<< "activarEdificiosCercanos(" << _entity->getEntityID() << ", " << "true" << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
			}
			else if (m_anochecer->getTime() == TIME_TYPE::DAY)
			{
				std::stringstream script;
				script	<< "activarEdificiosCercanos(" << _entity->getEntityID() << ", " << "false" << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
			}
		}

	} // process
	
	//---------------------------------------------------------

	void CPanelSolarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

} // namespace Logic