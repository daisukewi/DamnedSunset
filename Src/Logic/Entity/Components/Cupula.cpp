#include "Cupula.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include "Logic/Entity/Messages/DayNight.h"
#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/Damaged.h"


#include "Graphics/ModelFactory.h"

#include <sstream>


namespace Logic 
{
	IMP_FACTORY(CCupula);

	//---------------------------------------------------------

	bool CCupula::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if (entityInfo->hasAttribute("cupulaRadius")){
			_radius = entityInfo->getFloatAttribute("cupulaRadius");
		}

		if(entityInfo->hasAttribute("grid_position"))
		{
			Vector2 dimension = entityInfo->getVector2Attribute("dimension");
			Vector2 currentTilePos = entityInfo->getVector2Attribute("grid_position");
			Vector2 relativePosition = map->getGridMap()->getRelativeMapPos(currentTilePos.y - dimension.y *0.25 , currentTilePos.x - dimension.x * 0.25);

			_position.x = relativePosition.x;
			_position.z = relativePosition.y;
			_position.y = 0.0;

			std::stringstream script;
			script << "playerBase = { position = { x = " << _position.x << ", y = " << _position.y << ", z = " << _position.z << " } }";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}



		return true;
	} // spawn

	//---------------------------------------------------------

	bool CCupula::activate()
	{
		//Crear la estructura en LUA
		/*std::stringstream scriptCreate;
		scriptCreate << "cupula[" << _entity->getEntityID() << "] = {} ";
		scriptCreate << "cupula[" << _entity->getEntityID() << "].radius = " << _radius << " ";
		scriptCreate << "cupula[" << _entity->getEntityID() << "].posX = " << _position.x << " ";
		scriptCreate << "cupula[" << _entity->getEntityID() << "].posY = " << _position.y << " ";
		scriptCreate << "cupula[" << _entity->getEntityID() << "].posZ = " << _position.z;
		ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreate.str().c_str());
		*/

		//HACK, solo para ver que funciona bien
		//Graphics::CModelFactory::getSingletonPtr()->CreateCapsule(_entity->getMap()->getScene(),"","physic_debug_blue50",_radius,_position,0.5);
		
		return true;
	} // activate

	//---------------------------------------------------------

	bool CCupula::accept(IMessage *message)
	{
		return (!message->getType().compare("MDayNight"));
	} // accept
	
	//---------------------------------------------------------

	void CCupula::process(IMessage *message)
	{
		if (!message->getType().compare("MDayNight")){
			MDayNight *m = static_cast <MDayNight*> (message);
			if (m->getTime() == Logic::TIME_TYPE::DAY){

				//Hacer daño a las entidades (enemy y player) que se han quedado fuera de la cúpula
				MDamaged *damageMessage = new MDamaged();
				damageMessage->setHurt(4000);
				Logic::CMap::TEntityMap* entityMap = Logic::CServer::getSingletonPtr()->getMap()->getEntityMap();
				Logic::CMap::TEntityMap::const_iterator it, end;
				it = entityMap->begin();
				end = entityMap->end();
				damageMessage->addPtr();
				for(; it != end; it++)
				{
					std::string aux = (*it).second->getType();
					std::string aux2 = (*it).second->getTag();
					//Comprobar el tipo de entidad
					if (!aux.compare("Enemy") || !aux2.compare("Player")){
						
						//Comprobar la distancia del centro a la que se encuentra
						if (_position.distance((*it).second->getPosition()) > _radius)
							if (!aux2.compare("Player")){
								
							}else{
								(*it).second->emitMessage(damageMessage);
							}
						}

				}
				damageMessage->removePtr();
			}
		}
	} // process

	//---------------------------------------------------------

	void CCupula::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	
	}

	//---------------------------------------------------------

} // namespace Logic

