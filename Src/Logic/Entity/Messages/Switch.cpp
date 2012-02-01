/**
@file Switch.cpp

Contiene la implementación del mensaje de cambiar de estado una entidad.

@author Alberto Plaza
@date Enero, 2012
*/

#include "Switch.h"

namespace Logic
{

	MSwitch::MSwitch()
	{
		IMessage();

		_type = "MSwitch";

	} // MSwitch

	//---------------------------------------------------------

	void MSwitch::setState(int state)
	{
		_state = state;
	
	} // setState

	//---------------------------------------------------------

	int MSwitch::getState()
	{
		return _state;
	
	} // getState

} // namespace Logic