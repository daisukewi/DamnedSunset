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
#include "Logic/Entity/Messages/IsTouched.h"

#include "BaseSubsystems/Server.h"

#include "Logic/Entity/Messages/IASleep.h"

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

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CPerception::activate()
	{
		// Busco todas las entidades de tipo Player del mapa.
		Logic::CEntity *ent = _entity->getMap()->getEntityByTag("Player");
		while (ent != NULL)
		{
			_playerEntities.push_back(std::pair<Logic::CEntity*, bool>(ent, false));
			ent = _entity->getMap()->getEntityByTag("Player", ent);
		}

		// Construyo la estructura de datos que me va a servir para saber a que jugadores veo.
		std::stringstream script;
		script << "enemies[" << _entity->getEntityID() << "].playersSeen = { ";

		TPlayerList::const_iterator it = _playerEntities.begin();
		script << "[" << (*it).first->getEntityID() << "] = false";
		it++;
		for (; it != _playerEntities.end(); it++)
		{
			script << ", " << "[" << (*it).first->getEntityID() << "] = false";
		}
		script << " }";

		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

		// Construyo la estructura de datos que me va a servir para saber a que edificios veo.
		std::stringstream script2;
		script2 << "enemies[" << _entity->getEntityID() << "].buildingsSeen = {}";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script2.str().c_str());


		// Variable que va a contener el estado anterior en el que se encontraba la IA antes de dormirla
		std::stringstream script3;
		script3 << "enemies[" << _entity->getEntityID() << "].previousState = 0";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script3.str().c_str());


		return true;

	} // activate
	
	//---------------------------------------------------------

	void CPerception::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CPerception::accept(IMessage *message)
	{
		return !message->getType().compare("MIsTouched")
		|| !message->getType().compare("MIASleep");

	} // accept
	
	//---------------------------------------------------------

	void CPerception::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);
			if (m->getTouched())
			{
				if (!m->getEntity()->getTag().compare("Player"))
				{
					std::stringstream script;
					script << "enemyEventParam = { target = " << m->getEntity()->getEntityID() << " } ";
					script << "enemyEvent(\"OnPlayerSeen\", " << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}

				if (!m->getEntity()->getTag().compare("playerBuilding"))
				{
					std::stringstream script;
					script << "enemyEventParam = { target = " << m->getEntity()->getEntityID() << " } ";
					script << "enemyEvent(\"OnBuildingSeen\", " << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}
			}
			else
			{
				if (!m->getEntity()->getTag().compare("Player"))
				{
					std::stringstream script;
					script << "enemyEventParam = { target = " << m->getEntity()->getEntityID() << " } ";
					script << "enemyEvent(\"OnPlayerLost\", " << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}

				if (!m->getEntity()->getTag().compare("playerBuilding"))
				{
					std::stringstream script;
					script << "enemyEventParam = { target = " << m->getEntity()->getEntityID() << " } ";
					script << "enemyEvent(\"OnBuildingLost\", " << _entity->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
				}
			}
		}else if(!message->getType().compare("MIASleep")){

			MIASleep *m = static_cast <MIASleep*> (message);

			std::stringstream script;
			script << "enemyEvent(\"IASleep\", " << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(m->getTime(), this);
				
		}

			/*if (m->getTouched())
			{
				if (!m->getEntity()->getTag().compare("Player"))
				{
					// Busco al jugador que he visto.
					TPlayerList::iterator it = _playerEntities.begin();
					for (; it != _playerEntities.end(); it++)
					{
						if ((*it).first->getEntityID() == m->getEntity()->getEntityID())
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

							break;
						}
					}
				}
			}
			else
			{
				if (!m->getEntity()->getTag().compare("Player"))
				{
					// Busco al jugador que he dejado de ver.
					TPlayerList::iterator it = _playerEntities.begin();
					for (; it != _playerEntities.end(); it++)
					{
						if ((*it).first->getEntityID() == m->getEntity()->getEntityID())
						{
							// Compruebo si ya lo había dejado de ver para no mandar el aviso mas de una vez.
							if ((*it).second)
							{
								std::stringstream script;
								script << "enemyEventParam = { target = " << (*it).first->getEntityID() << " } ";
								script << "enemyEvent(\"OnPlayerLost\", " << _entity->getEntityID() << ")";
								ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

								(*it).second = false;
							}
						}
					}
				}
			}*/
	} // process

	//---------------------------------------------------------

	void CPerception::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		/*_currentExeFrames++;

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
						script << "enemyEventParam = { target = " << (*it).first->getEntityID() << ", distance = " << distance << " } ";
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
						script << "enemyEventParam = { target = " << (*it).first->getEntityID() << ", distance = " << distance << " } ";
						script << "enemyEvent(\"OnPlayerLost\", " << _entity->getEntityID() << ")";
						ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

						(*it).second = false;
					}
				}
			}
		}*/

	} // tick

	//---------------------------------------------------------


	void CPerception::timeElapsed()
	{
		std::stringstream script;
		script << "enemyEvent(\"IAAwake\", " << _entity->getEntityID() << ")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	} // timeElapsed


} // namespace Logic

