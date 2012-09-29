/**
@file IsTouched.h

Contiene la declaración del mensaje que indica si una entidad ha entrado en contacto con otra o si han dejado
de estar en contacto.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_IsTouched_H
#define __Logic_IsTouched_H

#include "Logic/Entity/Message.h"

#include "Logic/Entity/Entity.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar si una entidad ha entrado en contacto con otra o si han dejado
	de estar en contacto.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class MIsTouched : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MIsTouched();

		/**
		Método que establece el valor de tocado o no en el mensaje.

		@param touched Valor a almacenar en el mensaje.
		*/
		void setTouched(bool touched);

		/**
		Método que devuelve el valor de tocado almacenado en el mensaje.

		@return El valor alamacenado en el mensaje.
		*/
		bool getTouched();

		/**
		Método que establece el ID de la entidad en el mensaje.

		@param entityID int a almacenar en el mensaje.
		*/
		void setEntityID(unsigned int entityID);

		/**
		Método que devuelve el ID de la entidad almacenada en el mensaje.

		@return ID alamacenado en el mensaje.
		*/
		unsigned int getEntityID();

	protected:

		/**
		Atributo que indica si las entidades han entrado en contacto o han dejado de estar en contacto.
		*/
		bool _touched;

		/**
		ID de la entidad a la que hay que avisar del mensaje.
		*/
		unsigned int _entityID;

	}; // class MIsTouched

} // namespace Logic

#endif // __Logic_IsTouched_H