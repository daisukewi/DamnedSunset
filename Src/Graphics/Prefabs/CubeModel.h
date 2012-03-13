//---------------------------------------------------------------------------
// CubeModel.h
//---------------------------------------------------------------------------

/**
@file CubeModel.h

Contiene la declaración de la clase que representa un cubo

@see Graphics::ModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_CubeModel_H
#define __Graphics_CubeModel_H

#include "Graphics\Entity.h"
#include "Graphics\Server.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class MeshPtr;
}

namespace Graphics
{
	class CMaterial;
	class CEntity;
}

namespace Graphics 
{


	/**
	Clase que representa una entidada gráfica (CUBO). Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene.
	<p>
	Oculta los detalles escabrosos del motor gráfico.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CCubeModel : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param shape Tipo de forma que se va a crear.
		@param dimensions Vector3 que contiene las dimensiones del
		objeto que se quiere crear.
		*/
		CCubeModel(const std::string &name, std::string materialName,Vector3 dimensions,Vector3 position);

		/**
		Destructor de la clase.
		*/
		virtual ~CCubeModel();

		/**
		Asigna un material al objeto.

		@param material Material que se quiere asignar al objeto.
		*/
		void SetMaterial(CMaterial material);

		

		
	protected:

		/**
		Clase amiga. Solo la escena puede mandar a la entidad que pase a formar
		parte de la geometría estática.
		*/
		friend class CScene;

		
		/**
		Sobreescribir el método load de CEntity
		*/
		bool load();
		/**
		Sobreescribir el método attachToScene de CEntity
		*/
		bool attachToScene(CScene *scene);
		


		Vector3 _dimensions;
		Vector3 _position;
		std::string _material;

	}; // class CCubeModel

} // namespace Graphics

#endif // __Graphics_CubeModel_H
