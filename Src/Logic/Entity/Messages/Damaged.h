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

	protected:

		/**
		Atributo que indica el daño causado.
		*/
		float _hurt;

		/**
		Entidad que ataca.
		*/
		CEntity* _killer;

	}; // class MDamaged

} // namespace Logic

#endif // __Logic_Damaged_H