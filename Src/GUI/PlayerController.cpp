/**
@file PlayerController.cpp

Contiene la implementación de la clase CPlayerController. Se encarga de
recibir eventos del teclado y del ratón y de interpretarlos para
mover al jugador.

@see GUI::CPlayerController

@author David Llansó
@date Agosto, 2010
*/

#include "PlayerController.h"
#include "InputManager.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

#include "Logic/Entity/Messages/MouseEvent.h"

#include <cassert>

#define TURN_FACTOR 0.001f

namespace GUI {

	CPlayerController::CPlayerController() : _controlledAvatar(0)
	{

	} // CPlayerController

	//--------------------------------------------------------

	CPlayerController::~CPlayerController()
	{
		deactivate();

	} // ~CPlayerController

	//--------------------------------------------------------

	void CPlayerController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CPlayerController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	//--------------------------------------------------------

	bool CPlayerController::keyPressed(TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CPlayerController::keyReleased(TKey key)
	{
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CPlayerController::mouseMoved(const CMouseState &mouseState)
	{
		Logic::TMessage m;
		m._type = Logic::Message::MOUSE_MOVE;
		m._vector2 = Vector2(mouseState.posRelX, mouseState.posRelY);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(m);
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CPlayerController::mousePressed(const CMouseState &mouseState)
	{
		return false;
	} // mousePressed

	//--------------------------------------------------------

	bool CPlayerController::mouseReleased(const CMouseState &mouseState)
	{
		Logic::MMouseEvent *m_message = new Logic::MMouseEvent();

		if (mouseState.button == Button::LEFT)
			m_message->setAction(Logic::TMouseAction::LEFT_CLICK);
		else if (mouseState.button == Button::RIGHT)
			m_message->setAction(Logic::TMouseAction::RIGHT_CLICK);
		else if (mouseState.button == Button::MIDDLE)
			m_message->setAction(Logic::TMouseAction::MIDDLE_CLICK);

		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(m_message);

		return false;
	} // mouseReleased

} // namespace GUI
