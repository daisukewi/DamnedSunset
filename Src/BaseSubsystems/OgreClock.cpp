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
#include "Server.h"

#include <OgreTimer.h>
#include <cassert>

namespace BaseSubsystems {

	COgreClock::COgreClock() : IClock() 
	{
		_timer = CServer::getSingletonPtr()->getAppTimer();

	} // COgreClock

	//--------------------------------------------------------

	unsigned long COgreClock::getPhysicalTime()
	{
		assert(_timer);
		return _timer->getMilliseconds();
	} // getPhysicalTime

	//--------------------------------------------------------

} // namespace BaseSubsystems
