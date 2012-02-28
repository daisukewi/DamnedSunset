/**
@file ClockListener.h

Contiene la declaraci�n de un interfaz para un listener del temporizador.

@author Alberto Plaza
@date Febrero, 2012
*/

#ifndef __BaseSubsystems_ClockListener_H
#define __BaseSubsystems_ClockListener_H

namespace BaseSubsystems
{
	/**
	Listener del reloj de la aplicaci�n.

	Cada componente que quiera ser avisado por la aplicaci�n pasado un tiempo deber�
	implementar esta interfaz cuyos m�todos ser�n llamados por el temporizador de la
	aplicaci�n y deber�n ser implementados por la clase oyente.

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
		M�todo que ser� llamado por el temporizador de la aplicaci�n
		para que la clase oyente sepa que ha expirado su temporizador.
		*/
		virtual void timeElapsed() = 0;

	}; // IClockListener

} // namespace BaseSubsystems

#endif //  __BaseSubsystems_ClockListener_H