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
#include "Logic/Entity/Messages/IsTouched.h"



#include <sstream>
#include <iostream>

namespace Logic
{
	IMP_FACTORY(CPlayerPerception);
	
	//---------------------------------------------------------

	bool CPlayerPerception::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CPlayerPerception::activate()
	{
		

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CPlayerPerception::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPlayerPerception::accept(IMessage *message)
	{
		return (!message->getType().compare("MIsTouched"));

	} // accept
	
	//---------------------------------------------------------

	void CPlayerPerception::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched")){
			MIsTouched *m = static_cast <MIsTouched*> (message);
			Logic::CEntity *ent = m->getEntity();

			//Si el trigger lo ha activado un enemigo
			if (!ent->getType().compare("Enemy")){
				//si ha entrado se añade a la lista de enemigos detntro del trigger
				if (m->getTouched()){
					_enemyEntities.push_back(ent);
					std::cout << "ENEMIGO HA ENTRADO";
				//Si ha salido, eliminar de la lista y avisar a LUA de que lo ha dejado de ver
				}else{
					
					std::cout << "ENEMIGO HA SALIDO";
					std::stringstream script;
					script << "playerEventParam = { target = " << ent->getEntityID() << ", distance = " << 0 << " } ";
					script << "playerEvent(\"OnEnemyLost\", " << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

					_enemyEntities.remove(ent);
		}
			}
			
		}
	} // process

	//---------------------------------------------------------

	void CPlayerPerception::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (!_entity->getSelected()){
			
			_currentExeFrames++;

			// Ejecuto la percepción si toca.
			if (_exeFrames >= _currentExeFrames)
			{
				// Reinicio el contador de frames.
				_currentExeFrames = 0;

				//Recorrer la lista para saber cual es el enemigo más cercano y enviar un OnEnemySeen a la IA de LUA para que sea su nuevo objetivo 
				TEnemyList::iterator it = _enemyEntities.begin();
				CEntity *minDistanceEntity;
				
				int minDistance = 10000000;

				//Obtener el enemigo más cercano
				for (; it != _enemyEntities.end(); it++)
				{
					// Calculo la distancia entre el jugador y la entidad actual. (Distancia Manhattan)
					int xDistance = std::abs((*it)->getPosition().x - _entity->getPosition().x);
					int yDistance = std::abs((*it)->getPosition().z - _entity->getPosition().z);



					int distance = xDistance + yDistance;


					if (distance < minDistance){
						minDistance = distance;
						minDistanceEntity = (*it);
					}
				
				}

				if (minDistanceEntity){
					//Avisar a LUA del enemigo más cercano
					std::stringstream script;
					script << "playerEventParam = { target = " << minDistanceEntity->getEntityID() << ", distance = " << minDistance << " } ";
					script << "playerEvent(\"OnEnemySeen\", " << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}

			}
		}else{
			_currentExeFrames=0;
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

