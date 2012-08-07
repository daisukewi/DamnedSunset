/**
@file IASleep.h

Contiene la declaracióm del mensaje enviado paradormir las IA de los enemigos

@see Logic::IMessage

@author Alberto Ortega
@date Agosto, 2012
*/

#ifndef __Logic_IASleep_H
#define __Logic_IASleep_H

#include "Logic/Entity/Message.h"

namespace Logic 
{

	class MIASleep : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MIASleep();

		/**
		Método que devuelve el tiempo que va a ser dormida la IA

		@return int
		*/
		int getTime();

		/**
		Método que establece el tiempo que va a ser dormida la IA

		@param time
		*/
		void setTime(int time);

	private:

		/**
		Atributo que contiene el tiempo que tiene que ser dormida la IA
		*/
		int _time;

	};

} // namespace Logic

#endif // __Logic_IASleep_H