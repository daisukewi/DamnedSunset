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

#include "Logic/Entity/Messages/AttackEntity.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CPerception);
	
	//---------------------------------------------------------

	bool CPerception::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("distOfView"))
			_distanceOfView = entityInfo->getIntAttribute("distOfView");

		// Obtengo todas las entidades de tipo jugador del mapa.
		Logic::CEntity *ent = _entity->getMap()->getEntityByType("Player");
		while (ent != NULL)
		{
			_playerEntities.push_back(std::pair<Logic::CEntity*, bool>(ent, false));
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

		_currentExeFrames++;

		// Ejecuto la percepción si toca.
		if (_exeFrames >= _currentExeFrames)
		{
			// Reinicio el contador de frames.
			_currentExeFrames = 0;

			// Compruebo si veo a algún jugador. Me recorro la lista de jugadores para ver uno por uno si está a la distancia de visión.
			TPlayerList::iterator it = _playerEntities.begin();
			for (; it != _playerEntities.end(); it++)
			{
				// Calculo la distancia entre el jugador y la entidad actual. (Distancia Manhattan)
				int xDistance = std::abs((*it).first->getPosition().x - _entity->getPosition().x);
				int yDistance = std::abs((*it).first->getPosition().z - _entity->getPosition().z);

				int distance = xDistance + yDistance;

				// Si está dentro de la distancia de visión, aviso a lua.
				if (distance <= _distanceOfView)
				{
					// Compruebo si ya lo había visto antes para no mandar el aviso mas de una vez.
					if (!(*it).second)
					{
						std::stringstream script;
						script << "enemyEventParam = { target = " << (*it).first->getEntityID() << " } ";
						script << "enemyEvent(\"OnPlayerSeen\", " << _entity->getEntityID() << ")";
						ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

						(*it).second = true;
					}
				}
				// Si está fuera de la distancia de visión, aviso a lua de que lo he perdido de vista.
				else
				{
					// Compruebo si ya lo había dejado de ver para no mandar el aviso mas de una vez.
					if ((*it).second)
					{
						std::stringstream script;
						script << "enemyEvent(\"OnPlayerLost\", " << _entity->getEntityID() << ")";
						ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

						(*it).second = false;
					}
				}
			}
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

