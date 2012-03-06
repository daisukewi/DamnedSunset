//---------------------------------------------------------------------------
// BasicShapeEntity.cpp
//---------------------------------------------------------------------------

/**
@file BasicShapeEntity.cpp

Contiene la implementación de la clase que representa una entidad gráfica 
básica, como planos, cubos, esferas, etc...

@see Graphics::CBasicShapeEntity
@see Graphics::CEntity

@author Daniel Flamenco
@date Marzo, 2012
*/

#include "BasicShapeEntity.h"
#include "Scene.h"
#include "Material.h"

#include <assert.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

namespace Graphics 
{
	using namespace Ogre;

	static int _nextID = 0;

	CBasicShapeEntity::CBasicShapeEntity(const ShapeType shape, Ogre::Vector2 dimensions)
		: CEntity("", "")
	{
		std::stringstream name;
		name << "BasicShape_" << _nextID++;
		_mesh = name.str();

		MeshPtr shapeMesh;

		switch (shape)
		{
		case ShapeType::ST_Plane:
			shapeMesh = CreatePlane(_mesh, dimensions.x, dimensions.y);
			break;

		case ShapeType::ST_Cube:
		case ShapeType::ST_Sphere:
		case ShapeType::ST_Line:
			break;
		}

		std::stringstream entityName;
		entityName << "Entity" << _mesh;
		_name = entityName.str();

	} // CBasicShapeEntity

	// ------------------------------------------------

	CBasicShapeEntity::~CBasicShapeEntity()
	{
		MeshManager::getSingleton().unload(_mesh);

	} // ~CBasicShapeEntity

	// ------------------------------------------------

	void CBasicShapeEntity::SetMaterial(CMaterial material)
	{
		_entity->setMaterial(material.GetMaterial());

	} // SetMaterial

	// ------------------------------------------------

	MeshPtr CBasicShapeEntity::CreatePlane(const std::string &name, float width, float height)
	{
		Plane plane(Ogre::Vector3::UNIT_Y, 0);

		return MeshManager::getSingleton().createPlane(
			name,				// Name
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,	//Resource group Name
			plane,				// Normal orientation and distance from the origin
			width, height,		// Width, Height
			1, 1,				// x-segments, y-segments
			true,				// normals
			1,					// numTexCordsets
			1, 1,				// uTile, vTile
			Ogre::Vector3::UNIT_Z);	// UpVector
		
	} // CreatePlane

} // namespace Graphics