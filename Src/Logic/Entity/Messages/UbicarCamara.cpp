/**
@file CameraControl.cpp

Contiene la implementación del mensaje de control de la cámara.

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __GUI_UbicarCamara_H
#define __GUI_UbicarCamara_H

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