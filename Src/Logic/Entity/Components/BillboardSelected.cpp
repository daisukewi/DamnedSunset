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
		if (_billboard)
			delete _billboard;
	}

	bool CBillboardSelected::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_billboard = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardSeleccionMaterial")){
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardSeleccionMaterial"));
			_material = entityInfo->getStringAttribute("billboardSeleccionMaterial");
		}
		
		if (entityInfo->hasAttribute("billboardMultipleSeleccionMaterial")){
			_materialMultiple = entityInfo->getStringAttribute("billboardMultipleSeleccionMaterial");
		}
			
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
			
			if (m->getSelectedEntity() == _entity){
				if (m->getSelectedType() == Logic::EntitySelectedMessage::PRIMARY){
					//bool mostrar = m->getSelectedEntity() == _entity;
					_billboard->setMaterial(_material);
					billboardVisible = true;
					_billboard->setVisible(true);

				}else{
					//bool mostrar = m->getSelectedEntity() == _entity;
					_billboard->setMaterial(_materialMultiple);
					billboardVisible = true;
					_billboard->setVisible(true);
				}
			}else{
				_billboard->setVisible(false);
			}

				/*
				bool mostrar = m->getSelectedEntity() == _entity;
				_billboard->setMaterial(_materialMultiple);
				billboardVisible = mostrar;
				_billboard->setVisible(mostrar);
				*/
			
		} 
	} // process


} // namespace Logic

