/**
@file Perception.cpp

Contiene la implementación del componente que controla la percepción de los enemigos.

@author Alberto Plaza
@date Mayo, 2012
*/

#include "Perception.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CPerception);
	
	//---------------------------------------------------------

	bool CPerception::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("distanceOfView"))
			_distanceOfView = entityInfo->getIntAttribute("distanceOfView");

		// Obtengo todas las entidades de tipo jugador del mapa.
		Logic::CEntity *ent = _entity->getMap()->getEntityByType("Player");
		while (ent != NULL)
		{
			_playerEntities.push_back(ent);
			ent = _entity->getMap()->getEntityByType("Player", ent);
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CPerception::activate()
	{
		return true;

	} // activate
	
	//---------------------------------------------------------

	void CPerception::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPerception::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CPerception::process(IMessage *message)
	{

	} // process

	//---------------------------------------------------------

	void CPerception::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Compruebo si veo a algún jugador.
		std::list<Logic::CEntity*>::const_iterator it = _playerEntities.begin();
		for (; it != _playerEntities.end(); it++)
		{
			int xDistance = std::abs(it._Ptr->_Myval->getPosition().x - _entity->getPosition().x);
			int yDistance = std::abs(it._Ptr->_Myval->getPosition().z - _entity->getPosition().z);

			int distance = xDistance + yDistance;

			if (distance <= _distanceOfView)
			{
				std::stringstream script;
				script << "onPlayerSeen(" << _entity->getEntityID() << ", " << it._Ptr->_Myval->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				break;
			}
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

