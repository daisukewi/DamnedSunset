/**
@file CommunicationPort.cpp

Contiene la implementación de la clase que se encarga del intercambio 
de los mensajes.

@see Logic::CCommunicationPort

@author David Llansó García
@date Julio, 2010
*/

#include "CommunicationPort.h"

namespace Logic {

	CCommunicationPort::~CCommunicationPort()
	{
		_messages.clear();

	} // ~CCommunicationPort
	
	//---------------------------------------------------------

	bool CCommunicationPort::set(const TMessage &message) // @MENSAJES
	{
		bool accepted = accept(message);
		if(accepted)
			_messages.push_back(message);

		return accepted;

	} // set

	//---------------------------------------------------------

	bool CCommunicationPort::set(IMessage *message)
	{
		bool accepted = accept(message);
		if(accepted)
		{
			message->addPtr();
			_messagesPtr.push_back(message);
		}

		return accepted;

	} // set
	
	//---------------------------------------------------------

	void CCommunicationPort::processMessages()
	{
		TMessageList::const_iterator it = _messages.begin();
		for(; it != _messages.end(); it++)
			process(*it);

		_messages.clear();

		// @MENSAJES

		TMessageListPtr::const_iterator itPtr = _messagesPtr.begin();
		for(; itPtr != _messagesPtr.end(); itPtr++)
		{
			process(*itPtr);
			itPtr._Ptr->_Myval->removePtr();
		}

		_messagesPtr.clear();

	} // processMessages

} // namespace Logic
