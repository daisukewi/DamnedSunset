/**
@file RayPerception.h

Contiene la declaraci�n del componente que controla la percepci�n de la entidad usando rayos.

@see Logic::CRayPerception
@see Logic::IComponent

@author Antonio A. S�nchez Ruiz-Granados
@date Noviembre, 2011
*/
#ifndef __Logic_RayPerception_H
#define __Logic_RayPerception_H

#include "Logic/Entity/Component.h"

// namespace del componente
namespace Logic 
{
	/**
	Este componente lanza un rayo en la direcci�n en la que mira la entidad para 
	comprobar si alguna otra entidad est� cerca.

	@todo Ahora mismo este componente s�lo escribe por consola los objetos que
	percibe. En el futuro habr�a que mandar un mensaje a la entidad para que los
	componentes	encargados del comportamiento reaccionen.
	
    @ingroup logicGroup

	@author Antonio A. S�nchez Ruiz-Granados
	@date Noviembre, 2011
	*/
	class CRayPerception : public IComponent
	{
		DEC_FACTORY(CRayPerception);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CRayPerception() : IComponent(), _distance(10.0f) {}
		
		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		En cada tick se lanza un rayo en la direcci�n a la que mira la entidad para comprobar
		si hay alguna otra entidad en su rango de percepci�n.
	
		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);

	protected:

		/**
		Distancia a la que se perciben las entidades.
		*/
		float _distance;

	}; // class CRayPerception

	REG_FACTORY(CRayPerception);

} // namespace Logic

#endif // __Logic_RayPerception_H