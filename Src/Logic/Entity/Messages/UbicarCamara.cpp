/**
@file UbicarCamara.cpp

Contiene la implementación del mensaje de control de la cámara.

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_UbicarCamara_CPP
#define __Logic_UbicarCamara_CPP

#include "UbicarCamara.h"

namespace Logic
{
	MUbicarCamara::MUbicarCamara()
	{
		IMessage();
		_type = "MUbicarCamara";
	}
}
#endif