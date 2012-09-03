/**
@file Damaged.h

Contiene la declaración del mensaje de daño.

@see Logic::IMessage

@author Luis Mendoza
@date Enero, 2012
*/

#ifndef __Logic_Damaged_H
#define __Logic_Damaged_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{

	/**
	Tipo de acción a realizar cuando se envía un mensaje de daño.
	*/
	namespace DamageMessage
	{
		enum DamageAction
		{
			SET_DAMAGE_MODIFICATION,
			ADD_DAMAGE_MODIFICATION,
			RESET_DAMAGE_MODIFICATION,
			DAMAGE,
		};
	}

	typedef DamageMessage::DamageAction DamageAction;
	
	
	/**
	Clase mensaje que se encargará de avisar a una entidad de que ha sido herida.

	@author Luis Mendoza
	@date Enero, 2012
	*/
	class MDamaged : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MDamaged();

		/**
		Método que establece en el mensaje el daño causado.

		@param hurt entero que indica el daño causado.
		*/
		void setHurt(float hurt);

		/**
		Método que establece en el mensaje la entidad que ataca.

		@param killer entidad que ataca.
		*/
		void setKiller(CEntity* killer);

		/**
		Método que devuelve el daño causado.

		@return Daño causado.
		*/
		float getHurt();

		/**
		Método que devuelve la entidad atacante.

		@return Entidad que causa el daño.
		*/
		CEntity *getKiller();

		/**
		Método que devuelve la acción que se va a realizar
		
		@return _damageAction
		*/
		DamageAction getDamageAction();
		
		/**
		Método que establece la acción que se va a realizar
		
		@param damageAction Acción que se va a realizar
		*/
		void setDamageAction(DamageAction damageAction);
		
		/**
		Método que establece la modificación de daño
		
		@param damageModification
		*/
		void setDamageModification(float damageModification);
		
		/**
		Método que devuelve la modificación de daño
		
		@return damageModification float
		*/
		float getDamageModification();
		
	protected:

		/**
		Atributo que indica el daño causado.
		*/
		float _hurt;

		/**
		Entidad que ataca.
		*/
		CEntity* _killer;
		
		/**
		Acción que se quiere realizar con el mensaje
		*/
		DamageAction _damageAction;
		
		/**
		Cantidad de daño a reducir / aumentar
		*/
		float _damageModification;
		

	}; // class MDamaged

} // namespace Logic

#endif // __Logic_Damaged_H