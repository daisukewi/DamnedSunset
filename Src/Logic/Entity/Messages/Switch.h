/**
@file Switch.h

Contiene la declaración del mensaje de cambiar de estado una entidad.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_Switch_H
#define __Logic_Switch_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar del cambio de estado de una entidad.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class CSwitch : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		CSwitch();
		
		/**
		Método que establece en el mensaje el estado.
		*/
		void setState(int state);

		/**
		Método para obtener el valor del estado almacenado en el mensaje.
		*/
		int getState();

	protected:

		/**
		Atributo que indica el estado al que debe moverse la entidad.
		*/
		int _state;

	}; // class CSwitch

} // namespace Logic

#endif // __Logic_Switch_H