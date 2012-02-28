/**
@file ClockListener.h

Contiene la declaración de un interfaz para un listener del temporizador.

@author Alberto Plaza
@date Febrero, 2012
*/

#ifndef __BaseSubsystems_ClockListener_H
#define __BaseSubsystems_ClockListener_H

namespace BaseSubsystems
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
		Constructor por defecto de la clase. En la clase base no hace nada.
		*/
		IClockListener() {}

		/**
		Destructor por defecto. En la clase base no hace nada.
		*/
		virtual ~IClockListener() {}

		/**
		Método que será llamado por el temporizador de la aplicación
		para que la clase oyente sepa que ha expirado su temporizador.
		*/
		virtual void timeElapsed() = 0;

	}; // IClockListener

} // namespace BaseSubsystems

#endif //  __BaseSubsystems_ClockListener_H