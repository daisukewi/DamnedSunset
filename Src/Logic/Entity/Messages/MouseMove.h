/**
@file MouseMove.h

Contiene la declaración del mensaje que avisa del movimiento del ratón.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_MouseMove_H
#define __Logic_MouseMove_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar que se ha movido el ratón.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class MMouseMove : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MMouseMove();

		/**
		Método que establece el valor de la posición del ratón en el mensaje.

		@param point Coordenadas 2D del punto.
		*/
		void setPoint(Vector2 point);

		/**
		Método que devuelve la posición del ratón almacenada en el mensaje.

		@return La posición del ratón.
		*/
		Vector2 getPoint();

	protected:

		/**
		Atributo que guarda la posición 2D del ratón
		*/
		Vector2 _point;

	}; // class MMouseMove

} // namespace Logic

#endif // __Logic_MouseMove_H