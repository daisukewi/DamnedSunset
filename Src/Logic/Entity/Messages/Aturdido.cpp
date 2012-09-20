#ifndef __Logic_Aturdido_CPP
#define __Logic_Aturdido_CPP

#include "Aturdido.h"

namespace Logic
{
	MAturdido::MAturdido()
	{
		IMessage();
		_aturdido = true;
		_type = "MAturdido";
	}

	MAturdido::~MAturdido() 
	{
	}
}
#endif