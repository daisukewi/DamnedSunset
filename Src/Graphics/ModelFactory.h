//---------------------------------------------------------------------------
// ModelFactory.h
//---------------------------------------------------------------------------

/**
@file ModelFactory.h

Contiene la declaraci�n de la clase que permite crear modelos b�sicos de Ogre (planos, cubos, esferas y rectas)

@see Graphics::CModelFactory

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_ModelFactory_H
#define __Graphics_ModelFactory_H

#include <map>

#include "BaseSubsystems/Math.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
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
Namespace con todo lo que se refiere a la parte gr�fica. Las diferentes clases
se apoyan en Ogre.
(para m�s informaci�n ver @ref graphicsGroup).

@author Alberto Ortega
@date Marzo, 2012
*/
namespace Graphics 
{
		
	/**
	Se encarga de devolver instancias de modelos b�sicos de Ogre.
	<p>
	Est� implementado como un Singleton de inicializaci�n expl�cita; se debe 
	llamar a su m�todo Init(), para que la instancia est� creada.
	<p>
	Los detalles de dibujado est�n implementados haciendo uso de las funciones de creaci�n de modelos b�sicos de  Ogre.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CModelFactory 
	{
	protected:


	public:

		/**
		Devuelve la �nica instancia de la clase.

		@return Puntero al servidor gr�fico.
		*/
		static Graphics::CModelFactory *getSingletonPtr() { return _instance; }

		/**
		Constructor de la clase.
		*/
		CModelFactory();

		/**
		Destructor de la aplicaci�n.
		*/
		virtual ~CModelFactory();
		
		/*
		Funci�n que devuelve una entidada gr�fica (CEntity) que representa un CUBO
		*/
		CEntity * CreateCube();
		
		/*
		Funci�n que devuelve una entidada gr�fica (CEntity) que representa un PLANO
		*/
		CEntity * CreatePlane(const std::string &name, CMaterial material, Vector2 dimensions, Vector3 position);
		
		/*
		Funci�n que devuelve una entidada gr�fica (CEntity) que representa una L�NEA
		*/
		CEntity * CreateLine();
		
		
		/*
		Funci�n que devuelve una entidada gr�fica (CEntity) que representa un ESFERA
		*/
		CEntity * CreateSphere();
		
	private:
	
		/**
		Instancia �nica de la clase
		*/
		static CModelFactory* _instance;
		
		
		
		


	}; // class CServer

} // namespace Graphics

#endif // __Graphics_Server_H
