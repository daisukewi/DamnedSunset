//---------------------------------------------------------------------------
// CapsuleModel.h
//---------------------------------------------------------------------------

/**
@file CapsuleModel.h

Contiene la declaración de la clase que representa una esfera

@see Graphics::ModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_CapsuleModel_H
#define __Graphics_CapsuleModel_H

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
	Clase que representa una entidada gráfica (ESFERA). Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene.
	<p>
	Oculta los detalles escabrosos del motor gráfico.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CCapsuleModel : public CSimpleModel
	{
	public:

		/**
		Constructor de la clase.

		@param shape Tipo de forma que se va a crear.
		@param dimensions Vector3 que contiene las dimensiones del
		objeto que se quiere crear.
		*/
		CCapsuleModel(const std::string &name, std::string materialName,float radio,Vector3 position, float height);

		/**
		Destructor de la clase.
		*/
		virtual ~CCapsuleModel();

		

		
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
	
		float _radio;
		float _height;

	}; // class CCapsuleModel

} // namespace Graphics

#endif // __Graphics_CapsuleModel_H
