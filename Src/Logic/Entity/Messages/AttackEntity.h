/**
@file AttackEntity.h

Contiene la declaración del mensaje de ataque a una entidad.

@see Logic::IMessage

@author Luis Mendoza
@date Febrero, 2012
*/

#ifndef __Logic_AttackEntity_H
#define __Logic_AttackEntity_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que hay que atacar a otra entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class MAttackEntity : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MAttackEntity();

		/**
		Método que establece en el mensaje la entidad a la que hay que atacar.

		@param entity Entidad a la que atacar que debe guardar el mensaje.
		*/
		void setEntity(CEntity* entity);

		/**
		Método que establece en el mensaje si hay que atacar o hay que dejar de atacar.

		@param attack Cierto si hay que atacar y Falso para dejar de atacar.
		*/
		void setAttack(bool attack) { _attack = attack;};

		/**
		Método que devuelve la entidad a la que hay que atacar guardada en el mensaje.

		@return Puntero a la entidad guardada en el mensaje.
		*/
		CEntity *getEntity();

		/**
		Método que nos dice si hay que atacar.

		@return Bool que es cierto si hay que atacar y falso si hay que dejar de atacar.
		*/
		bool getAttack() { return _attack;};

	protected:

		/**
		Atributo que indica la entidad a la que hay que atacar.
		*/
		CEntity* _entity;

		/**
		Atributo que indica si hay que atacar.
		*/
		bool _attack;

	}; // class MAttackEntity

} // namespace Logic

#endif // __Logic_AttackEntity_H