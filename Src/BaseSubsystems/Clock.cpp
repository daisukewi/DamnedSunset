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

		_currentTime += _lastFrameDuration;
		notifyListeners();

	} // updateTime

	//--------------------------------------------------------

	void IClock::addListener(int clock, IClockListener* listener)
	{
		unsigned int tha_id = listener->getThaId();
		unsigned int his_time = _currentTime + clock; // Calculamos el momento cuando se debe avisar
		TListenerEntry tha_element(his_time, TListenerRef (tha_id, listener));

		if (_listeners.empty())
			_listeners.push_front(tha_element);
		else
		{
			// Insertamos el listener en la cola ordenada.
			TListenersList::iterator it = _listeners.begin();
			while (it != _listeners.end() && it->first <= his_time)
				++it;

			if (it == _listeners.end())
				_listeners.push_back(tha_element);
			else
				_listeners.insert(it, tha_element);
		}
		
	} // addListener

	//--------------------------------------------------------

	void IClock::notifyListeners()
	{
		TListenersList::iterator it, end;
		it = _listeners.begin();
		end = _listeners.end();

		// Avisamos a los que tengamos primeros en la cola
		// que ya haya pasado su tiempo
		while (it != end && it->first <= _currentTime)
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

	} // notifyListeners

	//--------------------------------------------------------

} // namespace BaseSubsystems
