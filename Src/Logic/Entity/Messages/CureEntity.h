/**
@file CureEntity.h

Contiene la declaración del mensaje de curación a una entidad.

@see Logic::IMessage

@author Alberto Ortega
@date Febrero, 2012
*/

#ifndef __Logic_CureEntity_H
#define __Logic_CureEntity_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que hay que atacar a otra entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class MCureEntity : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MCureEntity();

		/**
		Método que establece en el mensaje la entidad a la que hay que curar.

		@param entity Entidad a la que curar que debe guardar el mensaje.
		*/
		void setEntity(CEntity* entity);

		/**
		Método que establece en el mensaje si hay que curar o hay que dejar de curar.

		@param attack Cierto si hay que atacar y Falso para dejar de atacar.
		*/
		void setCure(bool cure) { _cure = cure;};

		/**
		Método que devuelve la entidad a la que hay que curar guardada en el mensaje.

		@return Puntero a la entidad guardada en el mensaje.
		*/
		CEntity *getEntity();

		/**
		Método que nos dice si hay que atacar.

		@return Bool que es cierto si hay que curar y falso si hay que dejar de curar.
		*/
		bool getCure() { return _cure;};

	protected:

		/**
		Atributo que indica la entidad a la que hay que atacar.
		*/
		CEntity* _entity;

		/**
		Atributo que indica si hay que atacar.
		*/
		bool _cure;

	}; // class MCureEntity

} // namespace Logic

#endif // __Logic_AttackEntity_H