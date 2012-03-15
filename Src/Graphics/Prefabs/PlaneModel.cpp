//---------------------------------------------------------------------------
// PlaneModel.h
//---------------------------------------------------------------------------

/**
@file PlaneModel.cpp

Contiene la implemtación de la clase que representa una línea

@see Graphics::CModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#include "Graphics\Prefabs\PlaneModel.h"
#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\Entity.h"
#include "Graphics\Scene.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace Graphics
{
	
	CPlaneModel::CPlaneModel(const std::string &name, std::string materialName,Vector2 dimensions,Vector3 position)
		: CSimpleModel()
	{
		_name = name;
		_dimensions = dimensions;
		_position = position;
		_material = materialName;
		
		
	} // CPlaneModel

	bool CPlaneModel::load(){
		
		try{
		
		_entity = _scene->getSceneMgr()->createEntity(_name,Ogre::SceneManager::PrefabType::PT_PLANE);

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
		Vector3 vector = auxBBox.getSize();


		_entityNode->scale(_dimensions.x/vector.x,_dimensions.y / vector.y,1.0);
		//Girarlo 90 grados porque aparece prependicular al mapa
		_entityNode->setOrientation(-90.0,90.0,0.0,0.0);

		//Modificar la posición
		this->setPosition(_position);
		
		_loaded = true;

		return _loaded;
	}

	CPlaneModel::~CPlaneModel()
	{
		//MeshManager::getSingleton().unload(_mesh);

	} // ~CPlaneModel


} // namespace Graphics

