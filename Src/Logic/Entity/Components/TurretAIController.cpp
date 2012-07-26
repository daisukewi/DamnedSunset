/**
@file TurretAIController.cpp

Contiene la implementación del componente que controla la IA de los personajes.

@author Alberto Ortega
@date Julio, 2012
*/

#include "TurretAIController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CTurretAIController);
	
	//---------------------------------------------------------

	bool CTurretAIController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if (!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("exeFrames"))
		{
			_exeFrames = entityInfo->getFloatAttribute("exeFrames");
		}else{
			_exeFrames = 1000.0;
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CTurretAIController::activate()
	{
		return true;
		
	} // activate
	
	//---------------------------------------------------------

	void CTurretAIController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CTurretAIController::accept(IMessage *message)
	{
		return true;

	} // accept
	
	//---------------------------------------------------------

	void CTurretAIController::process(IMessage *message)
	{
	
	} // process

	//---------------------------------------------------------

	void CTurretAIController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		_currentExeFrames += msecs;

		//Ejecuto la perfección si toca
		if (_currentExeFrames >= _exeFrames){
			// Reinicio el contador de frames.
			_currentExeFrames = 0;

			// Actualizo la posición de la entidad y llamo a la función de la IA.
			std::stringstream script;
			script	<< "buildings[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
					<< "buildings[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
					<< "buildings[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z << " "
					<< "turretAIAction(" << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	
		}


	} // tick

	//---------------------------------------------------------

} // namespace Logic

