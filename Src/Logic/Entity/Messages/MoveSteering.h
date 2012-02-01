/**
@file MoveSteering.h

Contiene la declaración del mensaje de un steering movement.

@see Logic::IMessage

@author Luis Mendoza
@date Enero, 2012
*/

#ifndef __Logic_MoveSteering_H
#define __Logic_MoveSteering_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que hay que hacer un steering movement.

	@author Luis Mendoza
	@date Enero, 2012
	*/
	class MMoveSteering : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MMoveSteering();

		/**
		Método que establece el tipo de movimiento.

		@param movementType entero que indica el tipo de movimiento (ver los tipos en IMovement).
		*/
		void setMovementType(int movementType);

		/**
		Método que devuelve el tipo de movimiento almacenado en el mensaje.

		@return Tipo de movimiento.
		*/
		int getMovementType();

		/**
		Método que establece en el mensaje el destino del movimiento.

		@param target punto de destino.
		*/
		void setTarget(Vector3 target);

		/**
		Método que devuelve del mensaje el destino del movimiento.

		@return el punto de destino.
		*/
		Vector3 getTarget();

	protected:

		/**
		Atributo que indica el tipo de movimiento (ver los tipos en IMovement).
		*/
		int _movType;

		/**
		Atributo que indica el destino del movimiento.
		*/
		Vector3 _target;

	}; // class MMoveSteering

} // namespace Logic

#endif // __Logic_MoveSteering_H