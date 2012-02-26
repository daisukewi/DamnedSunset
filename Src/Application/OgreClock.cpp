//---------------------------------------------------------------------------
// OgreClock.cpp
//---------------------------------------------------------------------------

/**
@file OgreClock.cpp

Contiene la implementación de un interfaz para un temporizador.

@see Application::COgreClock

@author David Llansó
@date Julio, 2010
*/

#include "OgreClock.h"
#include "BaseSubsystems/Server.h"

#include <OgreTimer.h>
#include <cassert>

namespace Application {

	COgreClock::COgreClock() : IClock() 
	{
		_timer = BaseSubsystems::CServer::getSingletonPtr()->getAppTimer();

	} // COgreClock

	//--------------------------------------------------------

	unsigned long COgreClock::getPhysicalTime()
	{
		assert(_timer);
		return _timer->getMilliseconds();
	} // getPhysicalTime

	//--------------------------------------------------------

	void COgreClock::addListener(unsigned int clock, IClockListener* listener)
	{
		_listeners.push_front(std::pair<unsigned int, IClockListener*> (clock, listener));

	} // addListener

	//--------------------------------------------------------

	void COgreClock::updateTime()
	{
		IClock::updateTime();

		TListenersList::iterator it, end;
		it = _listeners.begin();
		end = _listeners.end();

		for (; it != end; it++)
		{
			// Actualizo el cronómetro del listener con el tiempo transcurrido.
			it->first = it->first - _lastFrameDuration;

			// Si el cronómetro ha llegado a cero o menos, notifico al listener y lo anoto para borrarlo de la lista.
			if (it->first <= 0)
			{
				it->second->timeElapsed();
				_deferredRemoveListenersList.push_front(*it);
			}
		}

		// Borro los que he dejado pendientes de borrar
		it = _deferredRemoveListenersList.begin();
		end = _deferredRemoveListenersList.end();

		for (; it != end; it++)
		{
			_listeners.remove(*it);
		}

		_deferredRemoveListenersList.clear();
	
	} // updateTime

	//--------------------------------------------------------

} // namespace Application
