//---------------------------------------------------------------------------
// CapsuleModel.cpp
//---------------------------------------------------------------------------

/**
@file CapsuleModel.cpp

Contiene la implemtación de la clase que representa una esfera

@see Graphics::CModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#include "Graphics\Prefabs\CapsuleModel.h"
#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\Entity.h"
#include "Graphics\Scene.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace Graphics
{
	
	CCapsuleModel::CCapsuleModel(const std::string &name, std::string materialName,float radio,Vector3 position, float height)
		: CSimpleModel()
	{
		_name = name;
		_radio = radio;
		_position = position;
		_material = materialName;
		_height = height;
		
	} // CCapsuleModel

	bool CCapsuleModel::load(){
		
		try{
		
			_entity = _scene->getSceneMgr()->createEntity(_name,Ogre::SceneManager::PrefabType::PT_SPHERE);

		}catch(std::exception e)
		{
			return false;
		}
		
		
		Ogre::AxisAlignedBox auxBBox = _entity->getBoundingBox();

		_entityNode = _scene->getSceneMgr()->getRootSceneNode()->
								createChildSceneNode(_name + "_node");

		_entityNode->attachObject(_entity);
		

		//Añadir el material
		_entity->setMaterialName(_material);

		//Reescalar el prefab 
		Ogre::Node *node = _entity->getParentNode();

		Vector3 vector = auxBBox.getSize();



		_entityNode->scale(_radio / vector.x * 2,
			_height / vector.y * 2,
			_radio / vector.z * 2);

		//Modificar la posición

		this->setPosition(_position);

		_loaded = true;

		return _loaded;
	}

	CCapsuleModel::~CCapsuleModel()
	{
		//MeshManager::getSingleton().unload(_mesh);

	} // ~CCapsuleModel


} // namespace Graphics

