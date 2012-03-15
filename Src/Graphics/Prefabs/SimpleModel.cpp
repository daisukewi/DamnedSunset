//---------------------------------------------------------------------------
// SimpleModel.cpp
//---------------------------------------------------------------------------

/**
@file SimpleModel.cpp

Contiene la implemtación de la clase que representa un cubo

@see Graphics::CModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#include "Graphics\Prefabs\SimpleModel.h"
#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\Entity.h"
#include "Graphics\Scene.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace Graphics
{

	

	CSimpleModel::~CSimpleModel()
	{
		

	} // ~CSimpleModel

	// ------------------------------------------------

	void CSimpleModel::SetMaterial(CMaterial material)
	{
		_entity->setMaterial(material.GetMaterial());

	} // SetMaterial


	void CSimpleModel::setPosition(const Vector3 &position)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)

			_entityNode->setPosition(Vector3(position.x + _defX, position.y + _defY,position.z + _defZ));

	} // setPosition



} // namespace Graphics

