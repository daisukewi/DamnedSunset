//---------------------------------------------------------------------------
// ModelFactory.h
//---------------------------------------------------------------------------

/**
@file ModelFactory.h

Contiene la implementación de la clase que permite crear modelos básicos de Ogre (planos, cubos, esferas y rectas)

@see Graphics::CModelFactory

@author Alberto Ortega
@date Marzo, 2012
*/


#include <map>

#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\ModelFactory.h"
#include "Graphics\Prefabs\PlaneModel.h"
#include "Graphics\Scene.h"
#include "OgreSceneManager.h"
#include "Graphics\Entity.h"
#include "Graphics\Server.h"
#include <assert.h>


namespace Graphics 
{
		
	CModelFactory *CModelFactory::_instance = 0;
	
	static int _nextID = 0;
	
	CModelFactory::CModelFactory(){
		assert(!_instance && "Segunda inicialización de Graphics::CModelFactory no permitida!");
		
		_instance = this;
	}


	CModelFactory::~CModelFactory(){
		assert(_instance);

		_instance = 0;
	}	

	CEntity * CModelFactory::CreateCube(){
		return 0;
	}

	CEntity * CModelFactory::CreatePlane(Graphics::CScene *scene, const std::string &name, std::string materialName, Vector2 dimensions, Vector3 position){
		
		std::stringstream auxName;
		if ((!name.compare("")) || (name.length() == 0)){
			auxName << "BasicShape_" << _nextID++;
		}else{
			auxName << name;
		}
		CPlaneModel *model = new CPlaneModel(auxName.str(),materialName, dimensions, position);
		
		if (!scene->addEntity(model))
				return 0;

		return model;
	
	}

	CEntity * CModelFactory::CreateLine(){
		return 0;
	}

	CEntity * CModelFactory::CreateSphere(){
		return 0;
	}
		
} // namespace Graphics

