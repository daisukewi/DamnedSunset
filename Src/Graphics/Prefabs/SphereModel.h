//---------------------------------------------------------------------------
// SphereModel.h
//---------------------------------------------------------------------------

/**
@file SphereModel.h

Contiene la declaraci�n de la clase que representa una esfera

@see Graphics::ModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_SphereModel_H
#define __Graphics_SphereModel_H

#include "Graphics\Entity.h"
#include "Graphics\Server.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
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
	Clase que representa una entidada gr�fica (ESFERA). Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene.
	<p>
	Oculta los detalles escabrosos del motor gr�fico.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CSphereModel : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param shape Tipo de forma que se va a crear.
		@param dimensions Vector3 que contiene las dimensiones del
		objeto que se quiere crear.
		*/
		CSphereModel(const std::string &name, std::string materialName,float radio,Vector3 position);

		/**
		Destructor de la clase.
		*/
		virtual ~CSphereModel();

		/**
		Asigna un material al objeto.

		@param material Material que se quiere asignar al objeto.
		*/
		void SetMaterial(CMaterial material);

		

		
	protected:

		/**
		Clase amiga. Solo la escena puede mandar a la entidad que pase a formar
		parte de la geometr�a est�tica.
		*/
		friend class CScene;

		
		/**
		Sobreescribir el m�todo load de CEntity
		*/
		bool load();
		/**
		Sobreescribir el m�todo attachToScene de CEntity
		*/
		bool attachToScene(CScene *scene);
		


		float _radio;
		Vector3 _position;
		std::string _material;

	}; // class CSphereModel

} // namespace Graphics

#endif // __Graphics_SphereModel_H
