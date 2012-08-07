/**
@file PushEntities.h

Contiene la declaración del mensaje que da la orden de empujar las entidades alrededor de Jack.

@see Logic::IMessage

@author Luis Mendoza
@date Agosto, 2012
*/

#ifndef __Logic_PushEntities_H
#define __Logic_PushEntities_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de dar la orden de empujar las entidades alrededor de Jack.

	@author Luis Mendoza
	@date Agosto, 2012
	*/
	class MPushEntities : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MPushEntities();

	}; // class MPushEntities

} // namespace Logic

#endif // __Logic_PushEntities_H