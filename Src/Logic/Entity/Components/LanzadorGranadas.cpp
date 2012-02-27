#include "LanzadorGranadas.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Logic/Entity/Messages/LanzarGranada.h"

#include "Logic/Maps/EntityFactory.h"

namespace Logic 
{
	IMP_FACTORY(CLanzadorGranadas);
	
	//---------------------------------------------------------

	CLanzadorGranadas::CLanzadorGranadas() : IComponent() {

	}

	CLanzadorGranadas::~CLanzadorGranadas() {
		if (_billboard)
			delete _billboard;
	}

	bool CLanzadorGranadas::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_billboard = new Graphics::CBillboard(entity);
		if(entityInfo->hasAttribute("billboardLanzamientoMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardLanzamientoMaterial"));
		if(entityInfo->hasAttribute("billboardLanzamientoWith") && entityInfo->hasAttribute("billboardLanzamientoHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardLanzamientoWith"),entityInfo->getFloatAttribute("billboardLanzamientoHeight"));
		if(entityInfo->hasAttribute("billboardLanzamientoPosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardLanzamientoPosition");
			_billboard->setPosition(v.x,v.y,v.z);
		}
		_billboard->setPerpendicular();
		_billboard->setVisible(false);

		_estadoGranada = inactivo;

		return true;
	} // spawn


	bool CLanzadorGranadas::activate()
	{
		return true;
	} // activate
	//---------------------------------------------------------

	bool CLanzadorGranadas::accept(IMessage *message)
	{
		return !message->getType().compare("MLanzarGranada");
	} // accept
	
	//---------------------------------------------------------

	void CLanzadorGranadas::process(IMessage *message)
	{
		if (!message->getType().compare("MLanzarGranada"))
		{
			MLanzarGranada *m = static_cast <MLanzarGranada*> (message);

			if (m->getOrden() == mostrar)
			{
				_billboard->setVisible(true);
			} else if (m->getOrden() == ocultar)
			{
				_billboard->setVisible(false);
			}
			else if (m->getOrden() == lanzar)
			{
				//Lanzamos la granada a dicha posicion
				Map::CEntity * mapEntity = Map::CMapParser::getSingletonPtr()->getEntityInfo("Granada");
				mapEntity->setName("granada" + rand() );

				std::stringstream pos;
				pos << _entity->getPosition().x << ' ' << _entity->getPosition().y << ' ' << _entity->getPosition().z;
				mapEntity->setAttribute("position", pos.str());


				Logic::CEntity *entity = CEntityFactory::getSingletonPtr()->createEntity(mapEntity,Logic::CServer::getSingletonPtr()->getMap());
			}
		}
	} // process


} // namespace Logic

