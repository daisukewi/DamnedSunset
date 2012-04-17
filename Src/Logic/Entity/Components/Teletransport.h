/**
@file Teletransport.h

Contiene la declaración del componente que se encarga de teletransportar a una entidad a un punto.

@see Logic::CTeletransport
@see Logic::IComponent

@author Luis Mendoza
@date Abril, 2012
*/
#ifndef __Logic_Teletransport_H
#define __Logic_Teletransport_H

#include "Logic/Entity/Component.h"

namespace Graphics 
{
	class CEntity;
}

//declaración de la clase
namespace Logic 
{
/**
	Este componente controla el teletransporte de una entidad.
	<p>
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Abril, 2012
*/
	class CTeletransport : public IComponent
	{
		DEC_FACTORY(CTeletransport);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CTeletransport();

		~CTeletransport();
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		
		*/
		virtual bool accept(IMessage *message);

		/**
		
		*/
		virtual void process(IMessage *message);

	protected:

	}; // class CTeletransport

	REG_FACTORY(CTeletransport);

} // namespace Logic

#endif // __Logic_Teletransport_H