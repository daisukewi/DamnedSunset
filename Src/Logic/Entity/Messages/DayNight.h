/**
@file DayNight.h

Contiene la declaración del mensaje que indica en que fase del día se está

@see Logic::IMessage

@author Alberto Ortega
@date Mayo, 2012
*/

#ifndef __Logic_DayNight_H
#define __Logic_DayNight_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

#include "Logic/Entity/Components/DayNightController.h"

namespace Logic 
{
	/**
	Mensaje usado para avisar a las entidades en que fase del día se está y al "dios" para indicarle que hay que pasar de la fase de día a la de noche

	@author Alberto Ortega
	@date Mayo, 2012
	*/
	class MDayNight : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MDayNight();

		/**
		Método que establece la fase

		@param dayTime fase
		*/
		void setTime(TIME_TYPE timeType);

		/**
		Método que devuelve la fase

		@return fase 
		*/
		TIME_TYPE getTime();

	protected:

		/**
		Atributo que indica la fase 
		*/
		TIME_TYPE _timeType;

	}; // class MDayNight

} // namespace Logic

#endif // __Logic_MDayNight_H

