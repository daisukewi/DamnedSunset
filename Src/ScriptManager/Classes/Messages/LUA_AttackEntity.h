/**
@file LUA_AttackEntity.h

LUA

Contiene la declaración del mensaje de ataque a una entidad.

@see Logic::IMessage

@author Alberto Ortega
@date Abril, 2012
*/

#ifndef __Logic_LUA_AttackEntity_H
#define __Logic_LUA_AttackEntity_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que hay que atacar a otra entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class LUA_MAttackEntity : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MAttackEntity();

		/**
		Método que establece en el mensaje la entidad a la que hay que atacar.

		@param entity ID de la entidad a la que atacar que debe guardar el mensaje.
		*/
		void setEntity(unsigned int entity);

		/**
		Método que establece en el mensaje si hay que atacar o hay que dejar de atacar.

		@param attack Cierto si hay que atacar y Falso para dejar de atacar.
		*/
		void setAttack(bool attack) { _attack = attack;};

		/**
		Método que devuelve la entidad a la que hay que atacar guardada en el mensaje.

		@return Id de la entidad guardada en el mensaje.
		*/
		unsigned int getEntity();

		/**
		Método que nos dice si hay que atacar.

		@return Bool que es cierto si hay que atacar y falso si hay que dejar de atacar.
		*/
		bool getAttack() { return _attack;};

		/*
		Implementación del método send heredado de la clase LUA_IMessage
		*/
		virtual void send();

	protected:

		/**
		Atributo que indica la entidad a la que hay que atacar.
		*/
		unsigned int _entity;

		/**
		Atributo que indica si hay que atacar.
		*/
		bool _attack;

	}; // class LUA_MAttackEntity

} // namespace Logic

#endif // __Logic_LUA_AttackEntity_H