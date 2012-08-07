/**
@file IASleep.cpp

Contiene la implementación del mensaje enviado paradormir las IA de los enemigos

@author Alberto Ortega
@date Agosto, 2012
*/

#include "IASleep.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace Logic
{
	MIASleep::MIASleep()
	{
		IMessage();

		_type = "MIASleep";
	
	} // MIASleep

	int MIASleep::getTime()
	{
		return _time;
	}

	void MIASleep::setTime(int time)
	{
		_time = time;
	}



} // namespace Logic