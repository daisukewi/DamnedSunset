/**
@file ActivateSkill.h

Contiene la declaración del mensaje para activar una habilidad que se gestionará en el SelectionController.

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
	Clase mensaje que se encargará de activar una habilidad de una entidad.

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
		Método que establece en el mensaje si la habilidad está activada.

		@param bool Skill habilidad activada.
		*/
		void setSkill(bool skill);

		/**
		Método que nos dice si la habilidad está activada.

		@return Bool habilidad activada.
		*/
		bool getSkill();

	protected:

		/**
		Atributo que indica si la habilidad está activada o no.
		*/
		bool _skill;

	}; // class MActivateSkill

} // namespace Logic

#endif // __Logic_ActivateSkill_H