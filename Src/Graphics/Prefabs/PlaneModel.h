//---------------------------------------------------------------------------
// PlaneModel.h
//---------------------------------------------------------------------------

/**
@file PlaneModel.h

Contiene la declaración de la clase que representa un plano

@see Graphics::ModelFactory
@see Graphics::CSimpleModel

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_PlaneModel_H
#define __Graphics_PlaneModel_H

#include "Graphics\Entity.h"
#include "Graphics\Server.h"
#include "Graphics\Prefabs\SimpleModel.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class MeshPtr;
}

namespace Graphics
{
	class CMaterial;
	class CEntity;
	class CSimpleModel;
}

namespace Graphics 
{


	/**
	Clase que representa una entidada gráfica (PLANO). Especializa la clase
	Graphics::CSimpleModel
	<p>
	Oculta los detalles escabrosos del motor gráfico.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CPlaneModel : public CSimpleModel
	{
	public:

		/**
		Constructor de la clase.

		@param shape Tipo de forma que se va a crear.
		@param dimensions Vector3 que contiene las dimensiones del
		objeto que se quiere crear.
		*/
		CPlaneModel(const std::string &name, std::string materialName,Vector2 dimensions,Vector3 position);

		/**
		Destructor de la clase.
		*/
		virtual ~CPlaneModel();

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

		Vector2 _dimensions;

	}; // class CPlaneModel

} // namespace Graphics

#endif // __Graphics_PlaneModel_H
