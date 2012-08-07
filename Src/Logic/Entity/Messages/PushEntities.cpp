/**
@file PushEntities.cpp

Contiene la implementación del mensaje que da la orden de empujar las entidades alrededor de Jack.

@author Luis Mendoza
@date Agosto, 2012
*/

#include "PushEntities.h"

namespace Logic
{

	MPushEntities::MPushEntities()
	{
		IMessage();

		_type = "MPushEntities";

	} // MPushEntities

} // namespace Logic