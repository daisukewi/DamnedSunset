/**
@file CommunicationPort.cpp

Contiene la implementación de la clase que se encarga del intercambio 
de los mensajes.

@see Logic::CCommunicationPort

@author Alberto Plaza
@date Enero, 2012
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
		bool accepted = acceptPadre(message);
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
			processPadre(*it);
			(*it)->removePtr();
		}

		_messages.clear();

	} // processMessages

} // namespace Logic
