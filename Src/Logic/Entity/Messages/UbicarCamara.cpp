/**
@file CameraControl.cpp

Contiene la implementación del mensaje de control de la cámara.

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_UbicarCamara_CPP
#define __Logic_UbicarCamara_CPP

#include "UbicarCamara.h"

namespace Logic
{
	CUbicarCamara::CUbicarCamara()
	{
		IMessage();
		_type = "CUbicarCamara";
	}
}
#endif