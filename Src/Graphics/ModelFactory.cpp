//---------------------------------------------------------------------------
// ModelFactory.h
//---------------------------------------------------------------------------

/**
@file ModelFactory.h

Contiene la implementaci�n de la clase que permite crear modelos b�sicos de Ogre (planos, cubos, esferas y rectas)

@see Graphics::CModelFactory

@author Alberto Ortega
@date Marzo, 2012
*/


#include <map>

#include "BaseSubsystems/Math.h"
#include "Graphics\Material.h"
#include "Graphics\ModelFactory.h"
#include "Graphics\Prefabs\PlaneModel.h"
#include <assert.h>


namespace Graphics 
{
		
	CModelFactory *CModelFactory::_instance = 0;
	
	static int _nextID = 0;
	
	CModelFactory::CModelFactory(){
		assert(!_instance && "Segunda inicializaci�n de Graphics::CModelFactory no permitida!");
		
		_instance = this;
	}


	CModelFactory::~CModelFactory(){
		assert(_instance);

		_instance = 0;
	}	

	CEntity * CModelFactory::CreateCube(){
		return 0;
	}

	CEntity * CModelFactory::CreatePlane(const std::string &name, CMaterial material, Vector2 dimensions, Vector3 position){
		
		std::stringstream auxName;
		if ((!name.compare("")) || (name.length() == 0)){
			auxName << "BasicShape_" << _nextID++;
		}else{
			auxName << name;
		}
		return new CPlaneModel(auxName.str(), material, dimensions, position);
	
	}

	CEntity * CModelFactory::CreateLine(){
		return 0;
	}

	CEntity * CModelFactory::CreateSphere(){
		return 0;
	}
		
} // namespace Graphics
