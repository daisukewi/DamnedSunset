/**
@file Graphics.cpp

Contiene la implementación del componente que controla la representación
gráfica de la entidad.
 
@see Logic::CGraphics
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "Graphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/StaticEntity.h"

#include "Logic/Entity/Messages/SetTransform.h"
#include "Logic/Entity/Messages/AttachBillboard.h"

namespace Logic 
{
	IMP_FACTORY(CGraphics);
	
	//---------------------------------------------------------

	CGraphics::~CGraphics() 
	{
		if(_graphicsEntity)
		{
			_scene->removeEntity(_graphicsEntity);
			delete _graphicsEntity;
			_graphicsEntity = 0;
		}


	} // ~CGraphics
	
	//---------------------------------------------------------

	bool CGraphics::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		_scene = _entity->getMap()->getScene();

		if(entityInfo->hasAttribute("model"))
			_model = entityInfo->getStringAttribute("model");

		_graphicsEntity = createGraphicsEntity(entityInfo);
		if(!_graphicsEntity)
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	Graphics::CEntity* CGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		bool isStatic = false;
		if(entityInfo->hasAttribute("static"))
			isStatic = entityInfo->getBoolAttribute("static");

		float scale = 1.0;
		if (entityInfo->hasAttribute("scale"))
			scale = entityInfo->getFloatAttribute("scale");

		if(isStatic)
		{
			_graphicsEntity = new Graphics::CStaticEntity(_entity->getName(),_model);
			if(!_scene->addStaticEntity((Graphics::CStaticEntity*)_graphicsEntity))
				return 0;
		}
		else
		{
			_graphicsEntity = new Graphics::CEntity(_entity->getName(),_model);
			if(!_scene->addEntity(_graphicsEntity))
				return 0;
		}

		_graphicsEntity->setScale(scale);
		_graphicsEntity->setTransform(_entity->getTransform());
		
		return _graphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CGraphics::accept(IMessage *message)
	{
		bool accepted = (message->getType().compare("MSetTransform") == 0
			|| !message->getType().compare("MAttachBillboard"));

		if (accepted) message->addPtr();
		return accepted;

	} // accept

	//---------------------------------------------------------

	void CGraphics::process(IMessage *message)
	{
		if (!message->getType().compare("MSetTransform"))
		{
			MSetTransform *m = static_cast <MSetTransform*> (message);

			_graphicsEntity->setTransform(m->getTransform());
		} else 	if (!message->getType().compare("MAttachBillboard"))
		{
			MAttachBillboard *m = static_cast <MAttachBillboard*> (message);
			_graphicsEntity->attachBillboardSet(m->getBillboardSet());
		}

		message->removePtr();
	} // process

} // namespace Logic

