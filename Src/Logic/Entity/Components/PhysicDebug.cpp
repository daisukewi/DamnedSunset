/**
@file PhysicDebug.cpp

Contiene la implementación del componente que controla la representación
gráfica de la entida física
 
@see Logic::CGraphics
@see Logic::IComponent

@author Alberto Ortega
@date Febrero, 2012
*/

#include "PhysicDebug.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Server.h"
#include "Graphics/EntityDebug.h"
#include "Graphics/StaticEntity.h"

#include "Logic/Entity/Messages/SetTransform.h"
#include "Logic/Entity/Messages/AttachBillboard.h"

namespace Logic 
{
	IMP_FACTORY(CPhysicDebug);
	
	//---------------------------------------------------------

	CPhysicDebug::~CPhysicDebug() 
	{

		if(_graphicsEntity)
		{
			
			_scene->removeEntity(_graphicsEntity);
			delete _graphicsEntity;
			
			_graphicsEntity = 0;
			
		}

		if(_triggerEntity){
			_scene->removeEntity(_triggerEntity);
			delete _triggerEntity;

			_triggerEntity = 0;
		}

		

	

	} // ~CGraphics
	
	//---------------------------------------------------------

	bool CPhysicDebug::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
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

	Graphics::CEntityDebug* CPhysicDebug::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		bool isStatic = false;

		float scale = 1.0;
		if (entityInfo->hasAttribute("scale"))
			scale = entityInfo->getFloatAttribute("scale");

		if (entityInfo->hasAttribute("physic_shape")){
			std::string auxStr = entityInfo->getStringAttribute("physic_shape"); 
			Vector3 auxDimensions;
			float auxHeight;
			float auxRadius;
			
			Graphics::TOgrePrefab prefab;
			if (!auxStr.compare("box")){
				prefab = Graphics::TOgrePrefab::PT_CUBE;

				if (entityInfo->hasAttribute("physic_dimensions")){
					auxDimensions = entityInfo->getVector3Attribute("physic_dimensions");
				}
				
				_graphicsEntity = new Graphics::CEntityDebug(_entity->getName() + "_Debug",prefab, auxDimensions, _redMaterial);
				

			}else if (!auxStr.compare("capsule")){
				prefab = Graphics::TOgrePrefab::PT_SPHERE;
				
				if (entityInfo->hasAttribute("physic_height")){
					auxHeight = entityInfo->getFloatAttribute("physic_height");
				}
				
				if (entityInfo->hasAttribute("physic_radius")){
					auxRadius = entityInfo->getFloatAttribute("physic_radius");
				}

				_graphicsEntity = new Graphics::CEntityDebug(_entity->getName() + "_Debug",prefab,auxHeight,auxRadius, _greenMaterial);
			}
		}
		
		if (entityInfo->hasAttribute("trigger_shape")){
			std::string auxStr = entityInfo->getStringAttribute("trigger_shape"); 
			Vector3 auxDimensions;
			float auxHeight;
			float auxRadius;
			
			Graphics::TOgrePrefab prefab;
			if (!auxStr.compare("trigger_box")){
				prefab = Graphics::TOgrePrefab::PT_CUBE;

				if (entityInfo->hasAttribute("trigger_dimensions")){
					auxDimensions = entityInfo->getVector3Attribute("trigger_dimensions");
				}
				
				_triggerEntity = new Graphics::CEntityDebug(_entity->getName() + "_TDebug",prefab, auxDimensions, _blueMaterial);
				

			}else if (!auxStr.compare("trigger_sphere")){
				prefab = Graphics::TOgrePrefab::PT_SPHERE;
				
				if (entityInfo->hasAttribute("physic_height")){
					auxHeight = entityInfo->getFloatAttribute("physic_height");
				}
				
				if (entityInfo->hasAttribute("physic_radius")){
					auxRadius = entityInfo->getFloatAttribute("physic_radius");
				}

				_triggerEntity = new Graphics::CEntityDebug(_entity->getName() + "_TDebug",prefab,auxHeight,auxRadius, _blueMaterial);
			}
		}

			
		if (!_scene->addEntity(_graphicsEntity))
			return 0;

		_graphicsEntity->setScale(scale);
	
		_graphicsEntity->setTransform(_entity->getTransform());


		if(_triggerEntity){

			if (!_scene->addEntity(_triggerEntity))
			return 0;

			_triggerEntity->setScale(scale);
	
			_triggerEntity->setTransform(_entity->getTransform());
		}
		
		
		return _graphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CPhysicDebug::accept(IMessage *message)
	{
		bool accepted = (message->getType().compare("MSetTransform") == 0);

		if (accepted) message->addPtr();
		return accepted;

	} // accept

	//---------------------------------------------------------

	void CPhysicDebug::process(IMessage *message)
	{
		if (!message->getType().compare("MSetTransform"))
		{
			MSetTransform *m = static_cast <MSetTransform*> (message);

			_graphicsEntity->setTransform(m->getTransform());

			if(_triggerEntity)
				_triggerEntity->setTransform(m->getTransform());
		} 

		message->removePtr();
	} // process

} // namespace Logic


