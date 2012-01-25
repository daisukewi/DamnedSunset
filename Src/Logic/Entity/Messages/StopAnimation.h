/**
@file StopAnimation.h

Contiene la declaración del mensaje de parar una animación.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_StopAnimation_H
#define __Logic_StopAnimation_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad que hay que parar una animación concreta.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class CStopAnimation : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		CStopAnimation();

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

	protected:

		/**
		Atributo que indica el nombre de la animación que hay que parar.
		*/
		std::string _animationName;

	}; // class CStopAnimation

} // namespace Logic

#endif // __Logic_StopAnimation_H