/**
@file CameraControl.h

Contiene la declaraci�n del mensaje del control de c�mara.

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
	Clase mensaje que se encargar� de avisar a la c�mara que el usuario quiere hacer un movimiento.

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
		M�todo que devuelve si el rat�n ha sido el culpable del movimiento o no.

		@return true si el rat�n ha sido el que ha movido la c�mara.
		*/
		bool getMouse();

		/**
		M�todo que establece el valor de la variable del rat�n.

		@param mouse Valor de rat�n a guardar.
		*/
		void setMouse(bool mouse);

		/**
		M�todo que devuelve el tipo de movimiento y la direcci�n.

		@return Una cadena de texto con el movimiento que hay que hacer.
		*/
		std::string getMovement();

		/**
		M�todo que establece el tipo de movimiento.

		@param movement Tipo de movimiento que se va a hacer
		*/
		void setMovement(std::string movement);

		/**
		M�todo que devuelve el giro de la rueda del rat�n.

		@return int con el giro de la rueda.
		*/
		int getScroll();

		/**
		M�todo que establece el el giro de la rueda del rat�n.

		@param scroll Giro
		*/
		void setScroll(int scroll);

	protected:

		/**
		Atributo que indica si el movimiento del que hay que notificar se ha hecho con el rat�n o no.
		*/
		bool _mouse;

		/**
		Atributo que indica el tipo de movimiento que hay que notificar y la direcci�n.
		*/
		std::string _movement;

		/**
		Atributo que indica el giro de la rueda del rat�n.
		*/
		int _scroll;

	}; // class MCameraControl

} // namespace Logic

#endif // __Logic_CameraControl_H