/**
@file SetRealTime.h

Contiene la declaraci�n del mensaje para indicar si se tiene que vasar en el tiempo real

@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Mayo, 2012
*/

#ifndef __Logic_SetRealTime_H
#define __Logic_SetRealTime_H

#include "Logic/Entity/Message.h"

namespace Logic 
{

	/**
	Clase mensaje que avisa a la entidad que tiene q usar o no el tiempo real
	*/
	class MSetRealTime : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MSetRealTime();

		void setRealTime(bool realTime) {_realTime = realTime;}
		bool getRealTime() {return _realTime;}

	protected:
		bool _realTime;
	};

}

#endif