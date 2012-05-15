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

namespace BaseSubsystems {

	void IClock::updateTime() {
		unsigned long newTime = getPhysicalTime();
		_lastRealFrameDuration = newTime - _lastTime;
		_lastFrameDuration =  _lastRealFrameDuration / _factorRalentizar;
		_lastTime = newTime;

		//Para que el tiempo no pueda ser mayor de uno, suele darse cuando ponemos un punto de interrupcion, y da resultados raros, asi lo evitamos
		//Si el tick dura mas de medio segundo, lo fijamos en medio segundo
		assert((_lastFrameDuration = _lastFrameDuration>500?500:_lastFrameDuration) || true);
		assert((_lastRealFrameDuration = _lastRealFrameDuration>500?500:_lastRealFrameDuration) || true);

		notifyListeners();

	} // updateTime

	//--------------------------------------------------------

	void IClock::addListener(int clock, IClockListener* listener)
	{
		_listeners.push_front(std::pair<int, IClockListener*> (clock, listener));

	} // addListener

	//--------------------------------------------------------

	void IClock::notifyListeners()
	{
		TListenersList::iterator it, end;
		it = _listeners.begin();
		end = _listeners.end();

		for (; it != end; it++)
		{
			// Actualizo el cronómetro del listener con el tiempo transcurrido.
			it->first -= _lastFrameDuration;

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

	} // notifyListeners

	//--------------------------------------------------------

} // namespace BaseSubsystems
