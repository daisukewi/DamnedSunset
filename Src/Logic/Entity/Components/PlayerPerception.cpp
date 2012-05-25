/**
@file PlayerPerception.cpp

Contiene la implementación del componente que controla la percepción de los players.

@author Alberto Ortega
@date Mayo, 2012
*/

#include "PlayerPerception.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/AttackEntity.h"

#include <sstream>

namespace Logic
{
	IMP_FACTORY(CPlayerPerception);
	
	//---------------------------------------------------------

	bool CPlayerPerception::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("distOfView"))
			_distanceOfView = entityInfo->getIntAttribute("distOfView");
		else
			_distanceOfView = 30;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CPlayerPerception::activate()
	{
		// Obtengo todas las entidades de tipo enemigo del mapa.
		Logic::CEntity *ent = _entity->getMap()->getEntityByType("Enemy");
		while (ent != NULL)
		{
			_enemyEntities.push_back(std::pair<Logic::CEntity*, bool>(ent, false));
			ent = _entity->getMap()->getEntityByType("Enemy", ent);
		}

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CPlayerPerception::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPlayerPerception::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CPlayerPerception::process(IMessage *message)
	{
		
	} // process

	//---------------------------------------------------------

	void CPlayerPerception::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		/*
		if (!_entity->getSelected()){
			
			_currentExeFrames++;

			// Ejecuto la percepción si toca.
			if (_exeFrames >= _currentExeFrames)
			{
				// Reinicio el contador de frames.
				_currentExeFrames = 0;

				// Compruebo si veo a algún jugador. Me recorro la lista de jugadores para ver uno por uno si está a la distancia de visión.
				TEnemyList::iterator it = _enemyEntities.begin();
				for (; it != _enemyEntities.end(); it++)
				{
					// Calculo la distancia entre el jugador y la entidad actual. (Distancia Manhattan)
					int xDistance = std::abs((*it).first->getPosition().x - _entity->getPosition().x);
					int yDistance = std::abs((*it).first->getPosition().z - _entity->getPosition().z);

					int distance = xDistance + yDistance;

					// Si está dentro de la distancia de visión, aviso a lua.
					if (distance <= _distanceOfView)
					{
					
						//Necesario comrobar todas las veces para saber cual es el enemigo más cercano
						//if (!(*it).second)
						//{
							std::stringstream script;
							script << "playerEventParam = { target = " << (*it).first->getEntityID() << ", distance = " << distance << " } ";
							script << "playerEvent(\"OnEnemySeen\", " << _entity->getEntityID() << ")";
							ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

							(*it).second = true;
						//}
					}
					// Si está fuera de la distancia de visión, aviso a lua de que lo he perdido de vista.
					else
					{
						// Compruebo si ya lo había dejado de ver para no mandar el aviso mas de una vez.
						if ((*it).second)
						{
							std::stringstream script;
							script << "playerEventParam = { target = " << (*it).first->getEntityID() << ", distance = " << distance << " } ";
							script << "playerEvent(\"OnEnemyLost\", " << _entity->getEntityID() << ")";
							ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

							(*it).second = false;
						}
					}
				}
			}
		}else{
			_currentExeFrames=0;
		}*/

	} // tick

	//---------------------------------------------------------

} // namespace Logic

