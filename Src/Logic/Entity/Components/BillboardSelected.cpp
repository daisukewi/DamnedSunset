#include "BillboardSelected.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Entity/Messages/EntitySelected.h"

namespace Logic 
{
	IMP_FACTORY(CBillboardSelected);
	
	//---------------------------------------------------------

	CBillboardSelected::CBillboardSelected() : IComponent() {

	}

	CBillboardSelected::~CBillboardSelected() {

	}

	bool CBillboardSelected::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_billboard = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardSeleccionMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardSeleccionMaterial"));
		if(entityInfo->hasAttribute("billboardSeleccionWith") && entityInfo->hasAttribute("billboardSeleccionHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardSeleccionWith"),entityInfo->getFloatAttribute("billboardSeleccionHeight"));
		if(entityInfo->hasAttribute("billboardSeleccionPosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardSeleccionPosition");
			_billboard->setPosition(v.x,v.y,v.z);
		}
		_billboard->setPerpendicular();
		_billboard->setVisible(false);
		billboardVisible = false;
		return true;

	} // spawn

	//---------------------------------------------------------

	bool CBillboardSelected::accept(IMessage *message)
	{
		return !message->getType().compare("MEntitySelected");
	} // accept
	
	//---------------------------------------------------------

	void CBillboardSelected::process(IMessage *message)
	{
		if (!message->getType().compare("MEntitySelected"))
		{
			MEntitySelected * m = static_cast <MEntitySelected*> (message);
			bool mostrar = m->getSelectedEntity() == _entity;
			billboardVisible = mostrar;
			_billboard->setVisible(mostrar);
		} 
	} // process


} // namespace Logic

