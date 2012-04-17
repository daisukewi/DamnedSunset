/**
@file TeletransportTo.h

Contiene la declaraci�n del mensaje de teletransporte.

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
	Clase mensaje que se encargar� de avisar a una entidad de que se teletransporte a un punto.

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
		M�todo que establece en el mensaje la posici�n a la que se teletransportar�.

		@param position vector que indica la posici�n.
		*/
		void setPosition(Vector3 position);

		/**
		M�todo que devuelve la posici�n.

		@return Posici�n.
		*/
		Vector3 getPosition();

	protected:

		/**
		Atributo que indica la curaci�n causada.
		*/
		Vector3 _position;

	}; // class MTeletransportTo

} // namespace Logic

#endif // __Logic_TeletransportTo_H