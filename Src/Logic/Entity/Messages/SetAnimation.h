/**
@file SetAnimation.h

Contiene la declaración del mensaje de poner una animación.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_SetAnimation_H
#define __Logic_SetAnimation_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad que hay que poner una animación concreta.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class CSetAnimation : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		CSetAnimation();

		/**
		Método que establece el nombre de la animación en el mensaje.

		@param animationName Nombre de la animación.
		*/
		void setAnimationName(std::string animationName);

		/**
		Método que devuelve el nombre de la animación almacenada en el mensaje.

		@return Nombre de la animación.
		*/
		std::string getAnimationName();

		/**
		Método que establece en el mensaje la información de si se tiene que reproducir la animación en bucle o no.

		@param loop Si la animación es en bucle o no.
		*/
		void setLoop(bool loop);

		/**
		Método que devuelve la información almacenada en el mensaje de si hay que reproducir la animación en bucle o no.

		@return true si la animación hay que reproducirla en bucle.
		*/
		bool getLoop();

	protected:

		/**
		Atributo que indica el nombre de la animación que hay que reproducir.
		*/
		std::string _animationName;

		/**
		Atributo que indica si la animación se tiene que repetir o no.
		*/
		bool _loop;

	}; // class CSetAnimation

} // namespace Logic

#endif // __Logic_SetAnimation_H