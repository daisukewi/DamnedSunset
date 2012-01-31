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

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que ande.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class CAvatarWalk : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		CAvatarWalk();

		/**
		Método que establece el vector de movimiento en el mensaje.
		*/
		void setMovement(Vector3 movement);

		/**
		Método que devuelve el vector de movimiento almacenado en el mensaje.
		*/
		Vector3 getMovement();

	protected:

		/**
		Atributo que indica el movimiento que debe hacer la entidad.
		*/
		Vector3 _movement;

	}; // class CAvatarWalk

} // namespace Logic

#endif // __Logic_AvatarWalk_H