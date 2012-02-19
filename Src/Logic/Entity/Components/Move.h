/**
@file Move.h

Contiene la declaraci�n del componente que se encarga de recibir los mensajes para indicar a la 
entidad a que punto se debe mover (Los env�a el SelectionController)

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

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente controla el movimiento de una entidad, m�s concretamente el punto
	done se debe mover la entidad una vez hecho click con el rat�n en el escenario.
	Procesa mensajes MMoveTo  (Los env�a el SelectionController)
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
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Este componente s�lo acepta mensajes MDamaged.
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