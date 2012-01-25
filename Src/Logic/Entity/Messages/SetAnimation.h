/**
@file SetAnimation.h

Contiene la declaraci�n del mensaje de poner una animaci�n.

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
	Clase mensaje que se encargar� de avisar a una entidad que hay que poner una animaci�n concreta.

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
		M�todo que establece el nombre de la animaci�n en el mensaje.

		@param animationName Nombre de la animaci�n.
		*/
		void setAnimationName(std::string animationName);

		/**
		M�todo que devuelve el nombre de la animaci�n almacenada en el mensaje.

		@return Nombre de la animaci�n.
		*/
		std::string getAnimationName();

		/**
		M�todo que establece en el mensaje la informaci�n de si se tiene que reproducir la animaci�n en bucle o no.

		@param loop Si la animaci�n es en bucle o no.
		*/
		void setLoop(bool loop);

		/**
		M�todo que devuelve la informaci�n almacenada en el mensaje de si hay que reproducir la animaci�n en bucle o no.

		@return true si la animaci�n hay que reproducirla en bucle.
		*/
		bool getLoop();

	protected:

		/**
		Atributo que indica el nombre de la animaci�n que hay que reproducir.
		*/
		std::string _animationName;

		/**
		Atributo que indica si la animaci�n se tiene que repetir o no.
		*/
		bool _loop;

	}; // class CSetAnimation

} // namespace Logic

#endif // __Logic_SetAnimation_H