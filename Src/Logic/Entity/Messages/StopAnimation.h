/**
@file StopAnimation.h

Contiene la declaraci�n del mensaje de parar una animaci�n.

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
	Clase mensaje que se encargar� de avisar a una entidad que hay que parar una animaci�n concreta.

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
		M�todo que establece el nombre de la animaci�n en el mensaje.

		@param animationName Nombre de la animaci�n.
		*/
		void setAnimationName(std::string animationName);

		/**
		M�todo que devuelve el nombre de la animaci�n almacenada en el mensaje.

		@return Nombre de la animaci�n.
		*/
		std::string getAnimationName();

	protected:

		/**
		Atributo que indica el nombre de la animaci�n que hay que parar.
		*/
		std::string _animationName;

	}; // class CStopAnimation

} // namespace Logic

#endif // __Logic_StopAnimation_H