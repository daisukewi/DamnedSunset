/**
@file Switch.cpp

Contiene la implementación del mensaje de cambiar de estado una entidad.

@author Alberto Plaza
@date Enero, 2012
*/

#include "Switch.h"

namespace Logic
{

	CSwitch::CSwitch()
	{
		IMessage();

		_type = "CSwitch";

	} // CSwitch

	//---------------------------------------------------------

	void CSwitch::setState(int state)
	{
		_state = state;
	
	} // setState

	//---------------------------------------------------------

	int CSwitch::getState()
	{
		return _state;
	
	} // getState

} // namespace Logic