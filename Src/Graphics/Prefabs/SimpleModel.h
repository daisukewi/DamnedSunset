//---------------------------------------------------------------------------
// SimpleModel.h
//---------------------------------------------------------------------------

/**
@file SimpleModel.h

Contiene la declaración de la clase padre de los prefabs

@see Graphics::ModelFactory
@see Graphics::CEntity

@author Alberto Ortega
@date Marzo, 2012
*/

#ifndef __Graphics_SimpleModel_H
#define __Graphics_SimpleModel_H

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
	Clase que puede representar un prefab de los definidos. Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene.
	<p>
	Oculta los detalles escabrosos del motor gráfico.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Marzo, 2012
	*/
	class CSimpleModel : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param shape Tipo de forma que se va a crear.
		@param dimensions Vector3 que contiene las dimensiones del
		objeto que se quiere crear.
		*/
		CSimpleModel(): CEntity("", ""), _defX(0), _defY(0), _defZ(0){};

		/**
		Destructor de la clase.
		*/
		virtual ~CSimpleModel();

		/**
		Asigna un material al objeto.

		@param material Material que se quiere asignar al objeto.
		*/
		void SetMaterial(CMaterial material);
		
		
		/**
		Asigna un valor a sumar en el eje x cada vez que el objeto sea movido.
		Se usa por ejemplo, cuando se dibuja la físca. Para ajustar las coordenadas de la entidad que se dibuja como representación de la física,
		a las coordenadas reales de la física.
		
		@param defX valor de x que se desea añadir cada vez que se mueva la entidad
		*/
		void SetDefPosX(float defX){_defX = defX;};

		/**
		Asigna un valor a sumar en el eje y cada vez que el objeto sea movido.
		Se usa por ejemplo, cuando se dibuja la físca. Para ajustar las coordenadas de la entidad que se dibuja como representación de la física,
		a las coordenadas reales de la física. 
		
		@param defY valor de y que se desea añadir cada vez que se mueva la entidad
		*/
		void SetDefPosY(float defY){_defY = defY;};

		/**
		Asigna un valor a sumar en el eje z cada vez que el objeto sea movido.
		Se usa por ejemplo, cuando se dibuja la físca. Para ajustar las coordenadas de la entidad que se dibuja como representación de la física,
		a las coordenadas reales de la física.
		
		@param defZ valor de z que se desea añadir cada vez que se mueva la entidad
		*/
		void SetDefPosZ(float defZ){_defZ = defZ;};


		/**
		Cambia la posición de la entidad.

		@param position Nueva posición para el nodo que contiene la entidad 
		de Ogre.
		*/
		virtual void setPosition(const Vector3& position);
		
		
	protected:

		/**
		Clase amiga. Solo la escena puede mandar a la entidad que pase a formar
		parte de la geometría estática.
		*/
		friend class CScene;
		
		/**
		Sobreescribir el método load de CEntity
		*/
		virtual bool load()=0;
		
		float _defX;
		float _defY;
		float _defZ;

		Vector3 _position;
		std::string _material;


	}; // class CSimpleModel

} // namespace Graphics

#endif // __Graphics_SimpleModel_H
