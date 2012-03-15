//---------------------------------------------------------------------------
// CubeModel.cpp
//---------------------------------------------------------------------------

/**
@file CubeModel.cpp

Contiene la implemtación de la clase que representa un cubo

@see Graphics::CModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#include "Graphics\Prefabs\CubeModel.h"
#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\Entity.h"
#include "Graphics\Scene.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace Graphics
{
	
	CCubeModel::CCubeModel(const std::string &name, std::string materialName,Vector3 dimensions,Vector3 position)
		: CSimpleModel()
	{
		_name = name;
		_dimensions = dimensions;
		_position = position;
		_material = materialName;
		
		
	} // CCubeModel

	bool CCubeModel::load(){
		
		try{
		
			_entity = _scene->getSceneMgr()->createEntity(_name,Ogre::SceneManager::PrefabType::PT_CUBE);

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

		

		_entityNode->scale(_dimensions.x / vector.x * 2,
			_dimensions.y / vector.y * 2,
			_dimensions.z / vector.z * 2);

		//Modificar la posición

		this->setPosition(_position);

		_loaded = true;

		return _loaded;
	}

	CCubeModel::~CCubeModel()
	{
		//MeshManager::getSingleton().unload(_mesh);

	} // ~CCubeModel

} // namespace Graphics

