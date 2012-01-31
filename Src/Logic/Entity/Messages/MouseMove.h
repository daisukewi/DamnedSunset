/**
@file MouseMove.h

Contiene la declaraci�n del mensaje que avisa del movimiento del rat�n.

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
	Clase mensaje que se encargar� de avisar que se ha movido el rat�n.

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
		M�todo que establece el valor de la posici�n del rat�n en el mensaje.

		@param point Coordenadas 2D del punto.
		*/
		void setPoint(Vector2 point);

		/**
		M�todo que devuelve la posici�n del rat�n almacenada en el mensaje.

		@return La posici�n del rat�n.
		*/
		Vector2 getPoint();

	protected:

		/**
		Atributo que guarda la posici�n 2D del rat�n
		*/
		Vector2 _point;

	}; // class MMouseMove

} // namespace Logic

#endif // __Logic_MouseMove_H