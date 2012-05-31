/**
@file CameraController.cpp

Contiene la implementación del controlador de teclas de la cámara.

@author Alberto Plaza
@date Enero, 2012
*/
#include "CameraController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Messages/CameraControl.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic\Entity\Message.h"

#include "GUI\Server.h"
#include "GUI\InterfazController.h"

#include "ScriptManager\Server.h"

#include <cassert>

//#define TURN_FACTOR 0.001f

namespace GUI {

	CCameraController::CCameraController() : _controlledTarget(0)
	{

	} // CCameraController

	//--------------------------------------------------------

	CCameraController::~CCameraController()
	{
		deactivate();

	} // ~CCameraController

	//--------------------------------------------------------

	void CCameraController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CCameraController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	//--------------------------------------------------------

	bool CCameraController::keyPressed(TKey key)
	{
		if(_controlledTarget)
		{
			Logic::MCameraControl *m = new Logic::MCameraControl();

			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m->setMouse(false);

			switch(key.keyId)
			{
			case GUI::Key::UPARROW:
				m->setMovement("up");
				break;
			case GUI::Key::DOWNARROW:
				m->setMovement("down");
				break;
			case GUI::Key::LEFTARROW:
				m->setMovement("left");
				break;
			case GUI::Key::RIGHTARROW:
				m->setMovement("right");
				break;
			case GUI::Key::R:
				ScriptManager::CServer::getSingletonPtr()->reloadScripts();
				break;
			}
			m->setScroll(0);
			_controlledTarget->emitMessage(m);
		}
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CCameraController::keyReleased(TKey key)
	{
		if(_controlledTarget)
		{
			Logic::MCameraControl *m = new Logic::MCameraControl();
			
			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m->setMouse(false);

			switch(key.keyId)
			{
			case GUI::Key::UPARROW:
			case GUI::Key::DOWNARROW:
				m->setMovement("stopUpDown");
				break;

			case GUI::Key::LEFTARROW:
			case GUI::Key::RIGHTARROW:
				m->setMovement("stopLeftRight");
				break;
			}
			m->setScroll(0);
			_controlledTarget->emitMessage(m);
		}
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CCameraController::mouseMoved(const CMouseState &mouseState)
	{
		if(_controlledTarget)
		{
			Logic::MCameraControl *m1 = new Logic::MCameraControl();

			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m1->setMouse(true);

			if (mouseState.posRelX <= 0)
				m1->setMovement("left");
			else if (mouseState.posRelX >= 1)
				m1->setMovement("right");
			else if ((mouseState.posRelX > 0) && (mouseState.posRelX < 1))
				m1->setMovement("stopLeftRight");
			m1->setScroll(0);
			_controlledTarget->emitMessage(m1);

			Logic::MCameraControl *m2 = new Logic::MCameraControl();

			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m2->setMouse(true);
			m2->setScroll(0);

			if (mouseState.posRelY <= 0)
				m2->setMovement("up");
			else if (mouseState.posRelY >= 1)
				m2->setMovement("down");
			else if ((mouseState.posRelY > 0) && (mouseState.posRelY < 1))
				m2->setMovement("stopUpDown");

			_controlledTarget->emitMessage(m2);

			if (mouseState.scroll != 0)
			{
				Logic::MCameraControl *m_wheel = new Logic::MCameraControl();

				// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
				m_wheel->setMouse(true);
			
				m_wheel->setScroll(mouseState.scroll);
				_controlledTarget->emitMessage(m_wheel);
			}
		}
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CCameraController::mousePressed(const CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CCameraController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI
