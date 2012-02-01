/**
@file Selectable.cpp

Contiene la implementación del mensaje enviado para preguntar a una entidad si es seleccionable

@author Alberto Ortega
@date Enero, 2012
*/

#include "Selectable.h"

namespace Logic
{
	MSelectable::MSelectable()
	{
		IMessage();

		_type = "MSelectable";
	
	} // MSelectable

} // namespace Logic