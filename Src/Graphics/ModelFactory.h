//---------------------------------------------------------------------------
// ModelFactory.h
//---------------------------------------------------------------------------

/**
@file ModelFactory.h

Contiene la declaración de la clase que permite crear modelos básicos de Ogre (planos, cubos, esferas y rectas)

@see Graphics::CModelFactory

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_ModelFactory_H
#define __Graphics_ModelFactory_H

#include <map>

#include "BaseSubsystems/Math.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class Root;
	class RenderWindow;
	class Timer;
}
namespace Graphics 
{
	class CScene;
	class CEntity;
	class CMaterial;
}

/**
Namespace con todo lo que se refiere a la parte gráfica. Las diferentes clases
se apoyan en Ogre.
(para más información ver @ref graphicsGroup).

@author Alberto Ortega
@date Marzo, 2012
*/
namespace Graphics 
{
		
	/**
	Se encarga de devolver instancias de modelos básicos de Ogre.
	<p>
	Está implementado como un Singleton de inicialización explícita; se debe 
	llamar a su método Init(), para que la instancia esté creada.
	<p>
	Los detalles de dibujado están implementados haciendo uso de las funciones de creación de modelos básicos de  Ogre.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CModelFactory 
	{
	protected:


	public:

		/**
		Devuelve la única instancia de la clase.

		@return Puntero al servidor gráfico.
		*/
		static Graphics::CModelFactory *getSingletonPtr() { return _instance; }

		/**
		Constructor de la clase.
		*/
		CModelFactory();

		/**
		Destructor de la aplicación.
		*/
		virtual ~CModelFactory();
		
		/*
		Función que devuelve una entidada gráfica (CEntity) que representa un CUBO
		*/
		CEntity * CreateCube();
		
		/*
		Función que devuelve una entidada gráfica (CEntity) que representa un PLANO
		*/
		CEntity * CreatePlane(const std::string &name, CMaterial material, Vector2 dimensions, Vector3 position);
		
		/*
		Función que devuelve una entidada gráfica (CEntity) que representa una LÍNEA
		*/
		CEntity * CreateLine();
		
		
		/*
		Función que devuelve una entidada gráfica (CEntity) que representa un ESFERA
		*/
		CEntity * CreateSphere();
		
	private:
	
		/**
		Instancia única de la clase
		*/
		static CModelFactory* _instance;
		
		
		
		


	}; // class CServer

} // namespace Graphics

#endif // __Graphics_Server_H
