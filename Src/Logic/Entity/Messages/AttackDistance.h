/**
@file AttackDistance.h

Contiene la declaraci�n del mensaje de ataque a distancia  una entidad.

@see Logic::IMessage

@author Alberto Ortega
@date Mayo, 2012
*/

#ifndef __Logic_AttackDistance_H
#define __Logic_AttackDistance_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargar� de avisar a una entidad de que hay que atacar a otra entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class MAttackDistance : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MAttackDistance();

		/**
		M�todo que establece en el mensaje la entidad a la que hay que atacar.

		@param entity Entidad a la que atacar que debe guardar el mensaje.
		*/
		void setEntity(CEntity* entity);

		/**
		M�todo que establece en el mensaje si hay que atacar o hay que dejar de atacar.

		@param attack Cierto si hay que atacar y Falso para dejar de atacar.
		*/
		void setAttack(bool attack) { _attack = attack;};

		/**
		M�todo que devuelve la entidad a la que hay que atacar guardada en el mensaje.

		@return Puntero a la entidad guardada en el mensaje.
		*/
		CEntity *getEntity();

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

		/**
		Asignar el ID de la entidad a atacar
		*/
		void setEntityID(unsigned int IDEntity) { _IDEntity = IDEntity;};

		/**
		Obtener el ID de la entida a atacar
		*/
		unsigned int getEntityID() { return _IDEntity; };

	protected:

		/**
		Atributo que indica la entidad a la que hay que atacar.
		*/
		CEntity* _entity;


		/**
		Atributo que indica el ID de la entidad a la que hay que atacar
		*/
		unsigned int _IDEntity;

		/**
		Atributo que indica si hay que atacar.
		*/
		bool _attack;

		/**
		Atributo que indica si el ataque tiene que ser continuo
		*/
		bool _continue;

	}; // class MAttackDistance

} // namespace Logic

#endif // __Logic_AttackDistance_H