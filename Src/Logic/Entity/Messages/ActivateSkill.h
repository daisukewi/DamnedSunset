/**
@file ActivateSkill.h

Contiene la declaraci�n del mensaje para activar una habilidad que se gestionar� en el SelectionController.

@see Logic::IMessage

@author Luis Mendoza
@date Febrero, 2012
*/

#ifndef __Logic_ActivateSkill_H
#define __Logic_ActivateSkill_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargar� de activar una habilidad de una entidad.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class MActivateSkill : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MActivateSkill();

		/**
		M�todo que establece en el mensaje si la habilidad est� activada.

		@param bool Skill habilidad activada.
		*/
		void setSkill(bool skill);

		/**
		M�todo que nos dice si la habilidad est� activada.

		@return Bool habilidad activada.
		*/
		bool getSkill();

	protected:

		/**
		Atributo que indica si la habilidad est� activada o no.
		*/
		bool _skill;

	}; // class MActivateSkill

} // namespace Logic

#endif // __Logic_ActivateSkill_H