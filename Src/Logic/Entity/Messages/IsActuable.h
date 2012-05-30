/**
@file IsActuable.h

Contiene la declaración del mensaje enviado para preguntar a una entidad
si se puede interactuar con ella o no.

@see Logic::IMessage

@author Daniel Flamenco
@date Mayo, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_MIsActuable_H
#define __Logic_MIsActuable_H

#include "Logic/Entity/Message.h"

namespace Logic
{
	class CEntity;
}

namespace Logic 
{
	enum ActuablePetition
	{
		ACTION_REQUEST,
		ACTION_RESPONSE
	};

	class MIsActuable : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MIsActuable();

		/**
		Método que devuelve el tipo del mensaje,
		si es de peticion o respuesta de seleccion.

		@return enumerado que contiene el tipo del mensaje.
		*/
		ActuablePetition getMessageType();

		/**
		Método que establece el tipo del mensaje,
		si es de peticion o respuesta de seleccion.
		*/
		void setMessageType(ActuablePetition petitionType);

		/**
		Establece la entidad que emite este mensaje.
		Debe ser cambiado cuando se manda una respuesta.
		*/
		void setSenderEntity(CEntity* sender);

		/**
		Devuelve la entidad que envia el mensaje.
		*/
		CEntity* getSenderEntity();

	private:

		/**
		Atributo que contiene el tipo de mensaje que es
		*/
		ActuablePetition _petition;

		unsigned int _senderID;
	};

} // namespace Logic

#endif // __Logic_MIsActuable_H