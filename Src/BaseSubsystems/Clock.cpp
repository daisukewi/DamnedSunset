//---------------------------------------------------------------------------
// Clock.cpp
//---------------------------------------------------------------------------

/**
@file Clock.cpp

Contiene la implementación de un interfaz para un temporizador.

@see BaseSubsystems::IClock

@author David Llansó
@date Julio, 2010
*/

#include "Clock.h"
#include <cassert>
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace BaseSubsystems {

	void IClock::updateTime()
	{
		unsigned long newTime = getPhysicalTime();
		_lastRealFrameDuration = newTime - _lastTime;
		_lastFrameDuration =  _lastRealFrameDuration / _factorRalentizar;
		_lastTime = newTime;

		//Para que el tiempo no pueda ser mayor de uno, suele darse cuando ponemos un punto de interrupcion, y da resultados raros, asi lo evitamos
		//Si el tick dura mas de medio segundo, lo fijamos en medio segundo
		assert((_lastFrameDuration = _lastFrameDuration > 500 ? 500 : _lastFrameDuration) || true);
		assert((_lastRealFrameDuration = _lastRealFrameDuration > 500 ? 500 : _lastRealFrameDuration) || true);

		notifyListeners();

	} // updateTime

	//--------------------------------------------------------

	void IClock::addListener(int clock, IClockListener* listener)
	{
		unsigned int thaid = listener->getThaId();
		_listeners.push_front(TListenerEntry (clock, TListenerRef (thaid, listener)));

	} // addListener

	//--------------------------------------------------------

	void IClock::notifyListeners()
	{
		TListenersList::iterator it, end;
		it = _listeners.begin();
		end = _listeners.end();

		while (it != end)
		{
			// Actualizo el cronómetro del listener con el tiempo transcurrido.
			it->first -= _lastFrameDuration;

			// Si el cronómetro ha llegado a cero o menos, notifico al listener y lo anoto para borrarlo de la lista.
			if (it->first <= 0)
			{
				unsigned int tha_id = it->second.first;
				if (tha_id == 0 || Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(tha_id) != NULL)
				{
					try
					{
						it->second.second->timeElapsed();
					}
					catch (std::exception* e)
					{
						
					}
				}
				_listeners.remove(*it++);
			}
			else
				++it;
		}

	} // notifyListeners

	//--------------------------------------------------------

} // namespace BaseSubsystems
