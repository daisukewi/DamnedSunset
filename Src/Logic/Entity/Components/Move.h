/**
@file Move.h

Contiene la declaración del componente que se encarga de recibir los mensajes para indicar a la 
entidad a que punto se debe mover (Los envía el SelectionController)

@see Logic::CMove
@see Logic::IComponent

@author Alberto Ortega
@date Febrero, 2011
*/
#ifndef __Logic_Move_H
#define __Logic_Move_H

#include "Logic/Entity/Component.h"

namespace Graphics 
{
	class CEntity;
}

//declaración de la clase
namespace Logic 
{
/**
	Este componente controla el movimiento de una entidad, más concretamente el punto
	done se debe mover la entidad una vez hecho click con el ratón en el escenario.
	Procesa mensajes MMoveTo  (Los envía el SelectionController)
	<p>
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2011
*/
	class CMove : public IComponent
	{
		DEC_FACTORY(CMove);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CMove();

		~CMove();
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Este componente sólo acepta mensajes MDamaged.
		*/
		virtual bool accept(IMessage *message);

		/**
		Al recibir un mensaje MDamaged la vida de la entidad disminuye.
		*/
		virtual void process(IMessage *message);

	protected:

	}; // class CLife

	REG_FACTORY(CMove);

} // namespace Logic

#endif // __Logic_Move_H