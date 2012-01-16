/**
@file RayPerception.h

Contiene la declaración del componente que controla la percepción de la entidad usando rayos.

@see Logic::CRayPerception
@see Logic::IComponent

@author Antonio A. Sánchez Ruiz-Granados
@date Noviembre, 2011
*/
#ifndef __Logic_RayPerception_H
#define __Logic_RayPerception_H

#include "Logic/Entity/Component.h"

// namespace del componente
namespace Logic 
{
	/**
	Este componente lanza un rayo en la dirección en la que mira la entidad para 
	comprobar si alguna otra entidad está cerca.

	@todo Ahora mismo este componente sólo escribe por consola los objetos que
	percibe. En el futuro habría que mandar un mensaje a la entidad para que los
	componentes	encargados del comportamiento reaccionen.
	
    @ingroup logicGroup

	@author Antonio A. Sánchez Ruiz-Granados
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
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		En cada tick se lanza un rayo en la dirección a la que mira la entidad para comprobar
		si hay alguna otra entidad en su rango de percepción.
	
		@param msecs Milisegundos transcurridos desde el último tick.
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