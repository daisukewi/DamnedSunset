//---------------------------------------------------------------------------
// BasicShapeEntity.h
//---------------------------------------------------------------------------

/**
@file BasicShapeEntity.h

Contiene la declaraci�n de la clase que representa una entidad gr�fica 
b�sica, como planos, cubos, esferas, etc...

@see Graphics::CBasicShapeEntity
@see Graphics::CEntity

@author Daniel Flamenco
@date Marzo, 2012
*/

#ifndef __Graphics_BasicShapeEntity_H
#define __Graphics_BasicShapeEntity_H

#include "Entity.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class MeshPtr;
}

namespace Graphics
{
	class CMaterial;
}

namespace Graphics 
{

	enum ShapeType
	{
		ST_Plane,
		ST_Cube,
		ST_Sphere,
		ST_Line
	};

	typedef Graphics::ShapeType ShapeType;

	/**
	Clase que representa una entidad gr�fica de forma b�sica. Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene. A�ade la posibilidad de crear una forma
	b�sica como un plano, un cubo, una esfera, etc...
	<p>
	Oculta los detalles escabrosos del motor gr�fico.
	
	@ingroup graphicsGroup

	@author Daniel Flamenco
	@date Marzo, 2012
	*/
	class CBasicShapeEntity : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param shape Tipo de forma que se va a crear.
		@param dimensions Vector3 que contiene las dimensiones del
		objeto que se quiere crear.
		*/
		CBasicShapeEntity(const ShapeType shape, Ogre::Vector2 dimensions);

		/**
		Destructor de la clase.
		*/
		virtual ~CBasicShapeEntity();

		/**
		Asigna un material al objeto.

		@param material Material que se quiere asignar al objeto.
		*/
		void SetMaterial(CMaterial material);
	
	private:

		/**
		Crea un plano con las dimensiones dadas.

		@param name Nombre que se le dar� al objeto en Ogre como identificador.
		@param width Anchura del plano.
		@param height Altura del plano.
		@return Puntero al objeto creado en Ogre.
		*/
		Ogre::MeshPtr CreatePlane(const std::string &name, float width, float height);

	}; // class CBasicShapeEntity

} // namespace Graphics

#endif // __Graphics_BasicShapeEntity_H
