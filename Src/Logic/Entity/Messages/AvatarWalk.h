/**
@file AvatarWalk.h

Contiene la declaración del mensaje de mandar andar a una entidad.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_AvatarWalk_H
#define __Logic_AvatarWalk_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que ande.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class MAvatarWalk : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MAvatarWalk();

		/**
		Método que establece el vector de movimiento en el mensaje.

		@param movement Vector de movimiento para almacenar en el mensaje.
		*/
		void setMovement(Vector3 movement);

		/**
		Método que devuelve el vector de movimiento almacenado en el mensaje.

		@return El vector de movimiento almacenado en el mensaje
		*/
		Vector3 getMovement();

	protected:

		/**
		Atributo que indica el movimiento que debe hacer la entidad.
		*/
		Vector3 _movement;

	}; // class MAvatarWalk

} // namespace Logic

#endif // __Logic_AvatarWalk_H