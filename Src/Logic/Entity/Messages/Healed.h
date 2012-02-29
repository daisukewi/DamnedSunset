/**
@file Healed.h

Contiene la declaración del mensaje de curación.

@see Logic::IMessage

@author Luis Mendoza
@date Febrero, 2012
*/

#ifndef __Logic_Healed_H
#define __Logic_Healed_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad de que ha sido curada.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class MHealed : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MHealed();

		/**
		Método que establece en el mensaje la curación causada.

		@param heal entero que indica la curación causada.
		*/
		void setHeal(float heal);

		/**
		Método que establece en el mensaje la entidad que cura.

		@param healer entidad que cura.
		*/
		void setHealer(CEntity* healer);

		/**
		Método que devuelve la curación.

		@return Curación.
		*/
		float getHeal();

		/**
		Método que devuelve la entidad que cura.

		@return Entidad que cura.
		*/
		CEntity *getHealer();

	protected:

		/**
		Atributo que indica la curación causada.
		*/
		float _heal;

		/**
		Entidad que cura.
		*/
		CEntity* _healer;

	}; // class MHealed

} // namespace Logic

#endif // __Logic_Healed_H