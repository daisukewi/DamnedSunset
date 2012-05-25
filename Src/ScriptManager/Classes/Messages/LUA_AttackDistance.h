/**
@file LUA_AttackDistance.h

Contiene la declaraci�n del mensaje de ataque a distancia  una entidad.

@see Logic::IMessage

@author Alberto Ortega
@date Mayo, 2012
*/

#ifndef __Logic_LUA_AttackDistance_H
#define __Logic_LUA_AttackDistance_H


#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargar� de avisar a una entidad de que hay que atacar a otra entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class LUA_MAttackDistance : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MAttackDistance();

		/**
		M�todo que establece en el mensaje la entidad a la que hay que atacar.

		@param entity ID de la entidad a la que atacar que debe guardar el mensaje.
		*/
		void setEntity(unsigned int entity);

		/**
		M�todo que establece en el mensaje si hay que atacar o hay que dejar de atacar.

		@param attack Cierto si hay que atacar y Falso para dejar de atacar.
		*/
		void setAttack(bool attack) { _attack = attack;};

		/**
		M�todo que devuelve la entidad a la que hay que atacar guardada en el mensaje.

		@return Id de la entidad guardada en el mensaje.
		*/
		unsigned int getEntity();

		/**
		M�todo que nos dice si hay que atacar.

		@return Bool que es cierto si hay que atacar y falso si hay que dejar de atacar.
		*/
		bool getAttack() { return _attack;};

		/**
		M�todo que indica si el ataque es continuo

		@return _continue
		*/
		bool getContinue() { return _continue;};

		/**
		M�todo para indicar si el ataque tiene que ser continuo
		@param cotinue
		*/
		void setContinue(bool con) { _continue = con; };

		/*
		Implementaci�n del m�todo send heredado de la clase LUA_IMessage
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

		/**
		Atributo que indica si el ataque tiene que ser continuo
		*/
		bool _continue;

	}; // class MLUA_AttackDistance

} // namespace Logic

#endif // __Logic_LUA_AttackDistance_H