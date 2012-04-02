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
#include "Graphics/StaticEntity.h"

#include "Logic/Entity/Messages/SetTransform.h"
#include "Logic/Entity/Messages/AttachBillboard.h"

#include "Graphics/ModelFactory.h"
#include "Graphics/Prefabs/SimpleModel.h"

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

	Graphics::CSimpleModel* CPhysicDebug::createGraphicsEntity(const Map::CEntity *entityInfo)
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
				
				_graphicsEntity = Graphics::CModelFactory::getSingletonPtr()->CreateCube(_scene,_entity->getName(), _redMaterial, auxDimensions,_entity->getPosition());
				_graphicsEntity->SetDefPosY(auxDimensions.y);

			}else if (!auxStr.compare("capsule")){
				prefab = Graphics::TOgrePrefab::PT_SPHERE;
				
				if (entityInfo->hasAttribute("physic_height")){
					auxHeight = entityInfo->getFloatAttribute("physic_height");
				}
				
				if (entityInfo->hasAttribute("physic_radius")){
					auxRadius = entityInfo->getFloatAttribute("physic_radius");
				}

				_graphicsEntity = Graphics::CModelFactory::getSingletonPtr()->CreateCapsule(_scene,_entity->getName(), _greenMaterial, auxRadius,_entity->getPosition(),auxHeight);
				_graphicsEntity->SetDefPosY(auxHeight);

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
				
				_triggerEntity = Graphics::CModelFactory::getSingletonPtr()->CreateCube(_scene,_entity->getName()+"_trigger", _blueMaterial, auxDimensions,_entity->getPosition());
				

			}else if (!auxStr.compare("trigger_sphere")){
				prefab = Graphics::TOgrePrefab::PT_SPHERE;
				
				if (entityInfo->hasAttribute("trigger_height")){
					auxHeight = entityInfo->getFloatAttribute("trigger_height");
				}
				
				if (entityInfo->hasAttribute("trigger_radius")){
					auxRadius = entityInfo->getFloatAttribute("trigger_radius");
				}

				_triggerEntity = Graphics::CModelFactory::getSingletonPtr()->CreateCapsule(_scene,_entity->getName()+"_trigger", _blueMaterial, auxRadius,_entity->getPosition(),auxHeight);
			}
		}
		
		return _graphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CPhysicDebug::accept(IMessage *message)
	{
		return (message->getType().compare("MSetTransform") == 0);
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
	} // process

} // namespace Logic


