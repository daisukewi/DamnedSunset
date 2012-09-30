/**
@file EntityDeathListener.cpp

Contiene la implementación del mensaje para añadir o quitar un listener de la muerte de la entidad.

@author Alberto Plaza
@date Febrero, 2012
*/

#include "EntityDeathListener.h"

namespace Logic
{

	MEntityDeathListener::MEntityDeathListener()
	{
		IMessage();

		_type = "MEntityDeathListener";

	} // MAddDeathListener

	//---------------------------------------------------------

	void MEntityDeathListener::setListener(IDeathListener *listener)
	{
		_listener = listener;
		
	} // setListener

	//---------------------------------------------------------

	IDeathListener* MEntityDeathListener::getListener()
	{
		return _listener;
		
	} // getListener

	//---------------------------------------------------------

	void MEntityDeathListener::setListenerID(unsigned int listenerID)
	{
		_listenerID = listenerID;
		
	} // setListenerID

	//---------------------------------------------------------

	unsigned int MEntityDeathListener::getListenerID()
	{
		return _listenerID;
		
	} // getListenerID

	//---------------------------------------------------------

	void MEntityDeathListener::setAdd(bool add)
	{
		_add = add;
		
	} // setAdd

	//---------------------------------------------------------

	bool MEntityDeathListener::getAdd()
	{
		return _add;
		
	} // getAdd

	//---------------------------------------------------------

} // namespace Logic