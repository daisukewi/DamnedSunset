/**
@file Healed.h

Contiene la declaraci�n del mensaje de curaci�n.

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
	Clase mensaje que se encargar� de avisar a una entidad de que ha sido curada.

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
		M�todo que establece en el mensaje la curaci�n causada.

		@param heal entero que indica la curaci�n causada.
		*/
		void setHeal(float heal);

		/**
		M�todo que establece en el mensaje la entidad que cura.

		@param healer entidad que cura.
		*/
		void setHealer(CEntity* healer);

		/**
		M�todo que devuelve la curaci�n.

		@return Curaci�n.
		*/
		float getHeal();

		/**
		M�todo que devuelve la entidad que cura.

		@return Entidad que cura.
		*/
		CEntity *getHealer();

	protected:

		/**
		Atributo que indica la curaci�n causada.
		*/
		float _heal;

		/**
		Entidad que cura.
		*/
		CEntity* _healer;

	}; // class MHealed

} // namespace Logic

#endif // __Logic_Healed_H