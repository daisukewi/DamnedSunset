/**
@file CommunicationPort.cpp

Contiene la implementaci�n de la clase que se encarga del intercambio 
de los mensajes.

@see Logic::CCommunicationPort

@author David Llans� Garc�a
@date Julio, 2010
*/

#include "CommunicationPort.h"

namespace Logic {

	CCommunicationPort::~CCommunicationPort()
	{
		_messages.clear();

	} // ~CCommunicationPort

	//---------------------------------------------------------

	bool CCommunicationPort::set(IMessage *message)
	{
		bool accepted = accept(message);
		if(accepted)
		{
			message->addPtr();
			_messages.push_back(message);
		}

		return accepted;

	} // set
	
	//---------------------------------------------------------

	void CCommunicationPort::processMessages()
	{
		TMessageList::const_iterator it = _messages.begin();
		for(; it != _messages.end(); it++)
		{
			process(*it);
			it._Ptr->_Myval->removePtr();
		}

		_messages.clear();

	} // processMessages

} // namespace Logic
