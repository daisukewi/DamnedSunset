/**
@file MoveTo.h

Contiene la declaración del mensaje que indica a una entidad donde tiene que moverse

@see Logic::IMessage

@author Alberto Ortega
@date Febrero, 2012
*/

#ifndef __Logic_MoveTo_H
#define __Logic_MoveTo_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que tiene que ir a un punto

	@author Alberto Ortega
	@date Febrero, 2012
	*/
	class MMoveTo : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MMoveTo();

		/**
		Método que establece el punto destino

		@param position punto destino del personajes
		*/
		void setPosition(Vector3 position);

		/**
		Método que devuelve el punto destino 

		@return El punto destino
		*/
		Vector3 getPosition();

	protected:

		/**
		Atributo que indica el punto destino
		*/
		Vector3 _point;

	}; // class MMoveTo

} // namespace Logic

#endif // __Logic_MoveTo_H

