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

namespace Logic 
{
	IMP_FACTORY(CLanzadorGranadas);
	
	//---------------------------------------------------------

	CLanzadorGranadas::CLanzadorGranadas() : IComponent() {

	}

	CLanzadorGranadas::~CLanzadorGranadas() {

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
			_billboard->setVisible(true);
		}
	} // process


} // namespace Logic

