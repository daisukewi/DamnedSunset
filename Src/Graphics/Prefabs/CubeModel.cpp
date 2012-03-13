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
		: CEntity("", "")
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
		//_entity->setMaterialName(_material);

/*		//Reescalar el prefab 
		Ogre::Node *node = _entity->getParentNode();

		Vector3 vector = auxBBox.getSize();



		node->scale(_dimensions.x / vector.x * 2,
			1.0,
			_dimensions.y / vector.z * 2);

		//Modificar la posición*/

		//this->setPosition(_position);

		_loaded = true;

		return _loaded;
	}
	
	bool CCubeModel::attachToScene(CScene *scene)
	{
		assert(scene && "¡¡La entidad debe asociarse a una escena!!");
		// Si la entidad está cargada por otro gestor de escena.
		if(_loaded && (_scene != scene))
			return false;

		// Si no está cargada forzamos su carga.
		if (!_loaded)
		{
			_scene = scene;
			return load();
		}

		// Si ya estaba cargada en la escena se devuelve cierto.
		return true;
	} // attachToScene

	CCubeModel::~CCubeModel()
	{
		//MeshManager::getSingleton().unload(_mesh);

	} // ~CCubeModel

	// ------------------------------------------------

	void CCubeModel::SetMaterial(CMaterial material)
	{
		_entity->setMaterial(material.GetMaterial());

	} // SetMaterial

} // namespace Graphics

