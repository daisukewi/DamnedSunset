/**
@file CameraControl.h

Contiene la declaración del mensaje del control de cámara.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_CameraControl_H
#define __Logic_CameraControl_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a la cámara que el usuario quiere hacer un movimiento.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class MCameraControl : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MCameraControl();

		/**
		Método que devuelve si el ratón ha sido el culpable del movimiento o no.

		@return true si el ratón ha sido el que ha movido la cámara.
		*/
		bool getMouse();

		/**
		Método que establece el valor de la variable del ratón.

		@param mouse Valor de ratón a guardar.
		*/
		void setMouse(bool mouse);

		/**
		Método que devuelve el tipo de movimiento y la dirección.

		@return Una cadena de texto con el movimiento que hay que hacer.
		*/
		std::string getMovement();

		/**
		Método que establece el tipo de movimiento.

		@param movement Tipo de movimiento que se va a hacer
		*/
		void setMovement(std::string movement);

		/**
		Método que devuelve el giro de la rueda del ratón.

		@return int con el giro de la rueda.
		*/
		int getScroll();

		/**
		Método que establece el el giro de la rueda del ratón.

		@param scroll Giro
		*/
		void setScroll(int scroll);

	protected:

		/**
		Atributo que indica si el movimiento del que hay que notificar se ha hecho con el ratón o no.
		*/
		bool _mouse;

		/**
		Atributo que indica el tipo de movimiento que hay que notificar y la dirección.
		*/
		std::string _movement;

		/**
		Atributo que indica el giro de la rueda del ratón.
		*/
		int _scroll;

	}; // class MCameraControl

} // namespace Logic

#endif // __Logic_CameraControl_H