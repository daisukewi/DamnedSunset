//---------------------------------------------------------------------------
// OgreClock.h
//---------------------------------------------------------------------------

/**
@file OgreClock.h

Contiene la declaración de un temporizador basado en Ogre.

@see Application::COgreClock

@author David Llansó
@date Julio, 2010
*/

#ifndef __Application_OgreClock_H
#define __Application_OgreClock_H

#include "Clock.h"
#include "ClockListener.h"

#include <list>
#include <utility>

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class Timer;
}

namespace Application 
{
	/**
	Este temporizador  getTime() que deberá ser implementado en 
	las clases hijas y que devuelve el tiempo desde que se inició la
	aplicación, y getTimeSinceLastRequest que devuelve el tiempo transcurrido
	desde la última llamada al método. 

	@remarks Esta clase pide en su constructor una instancia del reloj de
	Ogre por lo que BaseSubsystems::CServer deverá haber sido inicializado
	antes de la construcción de esta clase.

	@ingroup applicationGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class COgreClock : public IClock
	{
	public:
		/** 
		Constructor de la clase 
		*/
		COgreClock();

		/** 
		Destructor 
		*/
		virtual ~COgreClock() {}

		/**
		Hace avanzar la hora del reloj, para que
		getTime() y getLastFrameDuration() devuelvan
		los nuevos valores. Además se encarga de comprobar
		si hay que avisar a alguno de los listeners de que su tiempo
		ha pasado.
		*/
		virtual void updateTime();

		/**
		Añade un nuevo oyente del temporizador con el tiempo tras el cual quiere
		ser avisado.

		@param clock tiempo tras el cual el oyente quiere ser avisado (en milisegundos).
		@param listener oyente del temporizador.
		*/
		void addListener(unsigned int clock, IClockListener* listener);

	protected:

		/**
		 Método que devuelve la "hora física" del sistema
		 en milisegundos.

		 Utiliza el reloj de Ogre.

		@return Hora en milisegundos.
		*/
		virtual unsigned long getPhysicalTime();

		/**
		Temporizador de Ogre.
		*/
		Ogre::Timer* _timer;

		/**
		Tipo Lista de oyentes del temporizador
		*/
		typedef std::list<std::pair<unsigned int, IClockListener*>> TListenersList;

		/**
		Lista de todos los oyentes del temporizador.
		*/
		TListenersList _listeners;

		/**
		Lista de oyentes a borrar en cada tick.
		*/
		TListenersList _deferredRemoveListenersList;

	}; // COgreClock

} // namespace Application

#endif //  __Application_OgreClock_H
