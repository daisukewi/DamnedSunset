/**
@file EntityDeath.h

Contiene la declaración del mensaje por la muerte de una entidad.

@see Logic::IMessage

@author Luis Mendoza
@date Febrero, 2012
*/

#ifndef __Logic_EntityDeath_H
#define __Logic_EntityDeath_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar de que una entidad ha muerto.

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class MEntityDeath : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MEntityDeath();

		/**
		Método que establece en el mensaje la entidad que ha muerto.

		@param entity entidad que está muerta.
		*/
		void setEntityDeath(CEntity* entity);

		/**
		Método que devuelve la entidad muerta.

		@return Entidad muerta.
		*/
		CEntity *getEntityDeath();

	protected:

		/**
		Entidad muerta.
		*/
		CEntity* _entityDeath;

	}; // class MEntityDeath

} // namespace Logic

#endif // __Logic_EntityDeath_H