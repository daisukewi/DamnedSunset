/**
@file TeletransportTo.h

Contiene la declaración del mensaje de teletransporte.

@see Logic::IMessage

@author Luis Mendoza
@date Abril, 2012
*/

#ifndef __Logic_TeletransportTo_H
#define __Logic_TeletransportTo_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que se teletransporte a un punto.

	@author Luis Mendoza
	@date Abril, 2012
	*/
	class MTeletransportTo : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MTeletransportTo();

		/**
		Método que establece en el mensaje la posición a la que se teletransportará.

		@param position vector que indica la posición.
		*/
		void setPosition(Vector3 position);

		/**
		Método que devuelve la posición.

		@return Posición.
		*/
		Vector3 getPosition();

	protected:

		/**
		Atributo que indica la curación causada.
		*/
		Vector3 _position;

	}; // class MTeletransportTo

} // namespace Logic

#endif // __Logic_TeletransportTo_H