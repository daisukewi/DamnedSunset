//---------------------------------------------------------------------------
// SphereModel.cpp
//---------------------------------------------------------------------------

/**
@file SphereModel.cpp

Contiene la implemtación de la clase que representa una esfera

@see Graphics::CModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#include "Graphics\Prefabs\SphereModel.h"
#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\Entity.h"
#include "Graphics\Scene.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace Graphics
{
	
	CSphereModel::CSphereModel(const std::string &name, std::string materialName,float radio,Vector3 position)
		: CEntity("", "")
	{
		_name = name;
		_radio = radio;
		_position = position;
		_material = materialName;
		
		
	} // CSphereModel

	bool CSphereModel::load(){
		
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
		//_entity->setMaterialName(_material);

		//Reescalar el prefab 
		Ogre::Node *node = _entity->getParentNode();

		Vector3 vector = auxBBox.getSize();



		_entityNode->scale(_radio / vector.x * 2,
			_radio / vector.y * 2,
			_radio / vector.z * 2);

		//Modificar la posición

		this->setPosition(_position);

		_loaded = true;

		return _loaded;
	}
	
	bool CSphereModel::attachToScene(CScene *scene)
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

	CSphereModel::~CSphereModel()
	{
		//MeshManager::getSingleton().unload(_mesh);

	} // ~CSphereModel

	// ------------------------------------------------

	void CSphereModel::SetMaterial(CMaterial material)
	{
		_entity->setMaterial(material.GetMaterial());

	} // SetMaterial

} // namespace Graphics

