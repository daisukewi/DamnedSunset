#ifndef __Logic_SendBillboard_CPP
#define __Logic_SendBillboard_CPP

#include "SendBillboard.h"

namespace Logic
{
	MSendBillboard::MSendBillboard()
	{
		IMessage();
		_type = "MSendBillboard";
		_tipoBillboard = "";
	}
}
#endif