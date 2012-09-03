/**
@file Damaged.h

Contiene la declaraci�n del mensaje de da�o.

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
	Tipo de acci�n a realizar cuando se env�a un mensaje de da�o.
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
	Clase mensaje que se encargar� de avisar a una entidad de que ha sido herida.

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
		M�todo que establece en el mensaje el da�o causado.

		@param hurt entero que indica el da�o causado.
		*/
		void setHurt(float hurt);

		/**
		M�todo que establece en el mensaje la entidad que ataca.

		@param killer entidad que ataca.
		*/
		void setKiller(CEntity* killer);

		/**
		M�todo que devuelve el da�o causado.

		@return Da�o causado.
		*/
		float getHurt();

		/**
		M�todo que devuelve la entidad atacante.

		@return Entidad que causa el da�o.
		*/
		CEntity *getKiller();

		/**
		M�todo que devuelve la acci�n que se va a realizar
		
		@return _damageAction
		*/
		DamageAction getDamageAction();
		
		/**
		M�todo que establece la acci�n que se va a realizar
		
		@param damageAction Acci�n que se va a realizar
		*/
		void setDamageAction(DamageAction damageAction);
		
		/**
		M�todo que establece la modificaci�n de da�o
		
		@param damageModification
		*/
		void setDamageModification(float damageModification);
		
		/**
		M�todo que devuelve la modificaci�n de da�o
		
		@return damageModification float
		*/
		float getDamageModification();
		
	protected:

		/**
		Atributo que indica el da�o causado.
		*/
		float _hurt;

		/**
		Entidad que ataca.
		*/
		CEntity* _killer;
		
		/**
		Acci�n que se quiere realizar con el mensaje
		*/
		DamageAction _damageAction;
		
		/**
		Cantidad de da�o a reducir / aumentar
		*/
		float _damageModification;
		

	}; // class MDamaged

} // namespace Logic

#endif // __Logic_Damaged_H