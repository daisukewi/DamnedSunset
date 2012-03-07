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
	
	CPlaneModel::CPlaneModel(const std::string &name, CMaterial material, Vector2 dimensions, Vector3 position)
		: CEntity("", "")
	{
		Ogre::AxisAlignedBox auxBBox;


		//Crear un nuevo nodo
		_entityNode = _scene->getSceneMgr()->getRootSceneNode()->
								createChildSceneNode(name + "_node");

								
		//Añadirle la entidad del plano
		_entityNode->attachObject(_entity);
		
		
		//Asignar el material
		
		_entity->setMaterial(material.GetMaterial());
		
		
		//Reescalar el prefab 
		Ogre::Node *node = _entity->getParentNode();
		auxBBox = _entity->getBoundingBox();
		Vector3 vector = auxBBox.getSize();
		
		node->scale(dimensions.x / vector.x * 2,
			1,
			dimensions.y / vector.y * 2);
			
		_entityNode->setPosition(position.x,
			position.y,
			position.z);
		
	} // CPlaneModel
	
	
	CPlaneModel::~CPlaneModel()
	{
		//MeshManager::getSingleton().unload(_mesh);

	} // ~CPlaneModel

	// ------------------------------------------------

	void CPlaneModel::SetMaterial(CMaterial material)
	{
		_entity->setMaterial(material.GetMaterial());

	} // SetMaterial

} // namespace Graphics

