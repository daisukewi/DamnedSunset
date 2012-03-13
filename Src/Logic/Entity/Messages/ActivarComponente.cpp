/**
@file ActivarComponente.cpp

Contiene la implementacion del mensaje ActivarComponente

@author Isaac Gallarzagoitia
@date Marzo, 2012
*/

#include "ActivarComponente.h"

namespace Logic
{

	MActivarComponente::MActivarComponente()
	{
		IMessage();

		_type = "MActivarComponente";
		_nombreComponente = "";
	}


} // namespace Logic