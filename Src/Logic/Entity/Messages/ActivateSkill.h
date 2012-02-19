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
	Tipo de habilidada activadad
	*/
	enum TSkill
		{
			DEACTIVATE,
			CURE,
			ATTACK,

		};
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
		M�todo que establece en el mensaje la habilidad quye hay que activar

		@param bool Skill habilidad activada.
		*/
		void setSkill(int skill);

		/**
		M�todo que nos dice que habilidad est� activada

		@return int habilidad activada.
		*/
		int getSkill();

	protected:

		/**
		Atributo que indica que habilidad hay que activar
		*/
		int _skill;

	}; // class MActivateSkill

} // namespace Logic

#endif // __Logic_ActivateSkill_H