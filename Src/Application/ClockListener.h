/**
@file ClockListener.h

Contiene la declaración de un interfaz para un listener del temporizador.

@author Alberto Plaza
@date Febrero, 2012
*/

#ifndef __Application_ClockListener_H
#define __Application_ClockListener_H

namespace Application
{
	/**
	Listener del reloj de la aplicación.

	Cada componente que quiera ser avisado por la aplicación pasado un tiempo deberá
	implementar esta interfaz cuyos métodos serán llamados por el temporizador de la
	aplicación y deberán ser implementados por la clase oyente.

	@author Alberto Plaza
	@date Febrero, 2012
	*/
	class IClockListener
	{
	public:

		/**
		Constructor por defecto de la clase
		*/
		IClockListener();

		/**
		Destructor
		*/
		virtual ~IClockListener();

		/**
		Método que será llamado por el temporizador de la aplicación
		para que la clase oyente sepa que ha expirado su temporizador.
		*/
		virtual void timeElapsed() = 0;

	}; // IClockListener

} // namespace Application

#endif //  __Application_ClockListener_H