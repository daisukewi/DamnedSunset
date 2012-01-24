/**
@file Message.cpp

Contiene la implementación de la clase base de los mensajes.

@author Alberto Plaza
@date Enero, 2012
*/

#include "Message.h"

namespace Logic
{
	void IMessage::removePtr()
	{
		_numPtr--;

		if (_numPtr <= 0)
			delete(this);

	} // removePtr

	//---------------------------------------------------------

} // namespace Logic