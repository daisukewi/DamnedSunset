/**
@file IsTouched.h

Contiene la declaraci�n del mensaje que indica si una entidad ha entrado en contacto con otra o si han dejado
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
	Clase mensaje que se encargar� de avisar si una entidad ha entrado en contacto con otra o si han dejado
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
		M�todo que establece el valor de tocado o no en el mensaje.

		@param touched Valor a almacenar en el mensaje.
		*/
		void setTouched(bool touched);

		/**
		M�todo que devuelve el valor de tocado almacenado en el mensaje.

		@return El valor alamacenado en el mensaje.
		*/
		bool getTouched();

		/**
		M�todo que establece la entidad a la que hay que avisar.

		@param entity Entidad a guardar en el mensaje.
		*/
		void setEntity(CEntity *entity);

		/**
		M�todo que devuelve la entidad almacenada en el mensaje.

		@return Entidad guardada en el mensaje.
		*/
		CEntity* getEntity();

	protected:

		/**
		Atributo que indica si las entidades han entrado en contacto o han dejado de estar en contacto.
		*/
		bool _touched;

		/**
		Entidad a la que hay que avisar del mensaje.
		*/
		CEntity *_entity;

	}; // class MIsTouched

} // namespace Logic

#endif // __Logic_IsTouched_H