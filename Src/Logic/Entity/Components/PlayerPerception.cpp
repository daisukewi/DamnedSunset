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

#include "Logic/Server.h"



#include <sstream>
#include <iostream>

namespace Logic
{
	IMP_FACTORY(CPlayerPerception);
	
	//---------------------------------------------------------

	bool CPlayerPerception::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{

		if (entityInfo->hasAttribute("perceptionTime")){
			_perceptionTime = entityInfo->getIntAttribute("perceptionTime");
		}else{
			_perceptionTime = 50;
		}


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
						_enemyEntities.push_back(ent->getEntityID());
						std::cout << "\n ENEMIGO HA ENTRADO \n";


					
					//Si ha salido, eliminar de la lista y avisar a LUA(si está deseleccionado la entidad) de que lo ha dejado de ver
					}else{
					
						std::cout << "\n ENEMIGO HA SALIDO \n";

						std::stringstream script;
						script << "playerEventParam = { target = " << ent->getEntityID() << ", distance = " << 0 << " } ";
							

						//if(true){
						if (!_entity->getSelected()){	
							script << "playerEvent(\"OnEnemyLost\", " << _entity->getEntityID() << ")";
							
						}else if (_entity->getSecondarySelected()){

							//script << "playerSecondaryEvent(\"OnEnemyLost\", " << _entity->getEntityID() << ")";
						}

						ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

						//En caso de que salga del trigger y muera, solo se mandaría a LUA el aviso
						//de que está fuera del trigger, no el de muerte, ya que cuando se analizan las entidades muertas dentro del 
						//trigger, está ya no existe por haberla sacado de la lista. Así que es necesario hacer una lista de entidades a 
						//borrar por haber salido fuera del trigger, y tenerla en cuenta después de eliminar las entidades muertas 
						//ya que una vez muerta no importa lo que ha pasado con ella.
						_enemyTriggerOut.push_back(ent->getEntityID());
					}
				}
			
		}
	} // process

	//---------------------------------------------------------

	void CPlayerPerception::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		//msecs = 0;
		//if (true){
		if (!_entity->getSelected() || _entity->getSecondarySelected()){
			
			_perceptionCountTime += msecs;

			//Ejecuto la perfección si toca
			if (_perceptionCountTime >= _perceptionTime){
				// Reinicio el contador de frames.
				_perceptionCountTime = 0;

				//Recorrer la lista para saber cual es el enemigo más cercano y enviar un OnEnemySeen a la IA de LUA para que sea su nuevo objetivo 
				TEnemyList::iterator it = _enemyEntities.begin();

				//Lista para apuntar los enemigos que hay que borrar

				TEnemyList deleteEnemies;

				//Obtener el enemigo más cercano
				for (; it != _enemyEntities.end(); it++)
				{
		
					CEntity *ent = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(*it);
					if (ent){
						// Calculo la distancia entre el jugador y la entidad actual. (Distancia Manhattan)

						int xDistance = std::abs(ent->getPosition().x - _entity->getPosition().x);
						int yDistance = std::abs(ent->getPosition().z - _entity->getPosition().z);
						

						int distance = xDistance + yDistance;


						if (distance < _minDistance){
							_minDistance = distance;
							_minDistanceEntity = (*it);
						}
					}else{
						deleteEnemies.push_back(*it);
					}
				}

				//Elimino los enemigos muertos
				TEnemyList::iterator id = deleteEnemies.begin();
				for (; id != deleteEnemies.end(); id++)
				{
					_enemyEntities.remove(*id);
					//Si coincide con el que estoy atacando
					if (_minDistanceEntity == (*id)){
						_minDistanceEntity = -1;
					}

					//Avisar a LUA de que ha muerto
					std::stringstream script;
					script << "playerEventParam = { target = " << (*id) << ", distance = " << 0 << " } ";
					
					if (!_entity->getSelected()){
					
						script << "playerEvent(\"OnEnemyDie\", " << _entity->getEntityID() << ")";
					
					}else if (_entity->getSecondarySelected()){
					
						//script << "playerSecondaryEvent(\"OnEnemyDie\", " << _entity->getEntityID() << ")";
					
					}
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}

				
				//Elimino los enemigos que han salido del trigger
				TEnemyList::iterator io = _enemyTriggerOut.begin();
				for (;io != _enemyTriggerOut.end();io++)
				{
					_enemyEntities.remove(*io);
				}
				_enemyTriggerOut.clear();



				CEntity *ent = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_minDistanceEntity);

				if (ent){
					//Avisar a LUA del enemigo más cercano
					//std::cout << "\n ENTIDA MAS CERCANA: " << _minDistanceEntity << " :: " << _minDistance<<"\n";
					std::stringstream script;
					script << "playerEventParam = { target = " << _minDistanceEntity << ", distance = " << _minDistance << " } ";
					
					if (!_entity->getSelected()){
					
						script << "playerEvent(\"OnEnemySeen\", " << _entity->getEntityID() << ")";
					
					}else if (_entity->getSecondarySelected()){
					
						//script << "playerSecondaryEvent(\"OnEnemySeen\", " << _entity->getEntityID() << ")";
					
					}
					
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}else{
					_minDistance = 10000;
				}
			}
			
		}else{
			_perceptionCountTime=0;
		}
		

	} // tick

	//---------------------------------------------------------

} // namespace Logic

