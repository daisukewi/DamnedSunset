/**
@file LUA_CambiarDIaNoche.h

LUA

Contiene la declaración del mensaje de cambiar dia y noche

@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Mayo, 2012
*/

#ifndef __Logic_LUA_CambiarDiaNoche_H
#define __Logic_LUA_CambiarDiaNoche_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que hay que atacar a otra entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class LUA_MCambiarDiaNoche : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MCambiarDiaNoche();

		/**
		Indica si va a amanecer o anochecer

		@param cambiarADia Cierto para cambiar a dia, falso para cambiar a noche
		*/
		void setCambiarADia(bool cambiarADia) { _cambiarADia = cambiarADia;};

		/*
		Implementación del método send heredado de la clase LUA_IMessage
		*/
		virtual void send();

	protected:
		/**
		Atributo que indica si hay que atacar.
		*/
		bool _cambiarADia;

	}; // class LUA_MAttackEntity

} // namespace Logic

#endif // __Logic_LUA_AttackEntity_H