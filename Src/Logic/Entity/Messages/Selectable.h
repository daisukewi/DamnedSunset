/**
@file Selectable.h

Contiene la declaración del mensaje enviado para preguntar a una entidad si es seleccionable

@see Logic::IMessage

@author Alberto Ortega
@date Enero, 2012
*/

#ifndef __Logic_Selectable_H
#define __Logic_Selectable_H

#include "Logic/Entity/Message.h"


namespace Logic 
{

	class MSelectable : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MSelectable() : IMessage("MSelectable") {};

	};

} // namespace Logic

#endif // __Logic_Selectable_H