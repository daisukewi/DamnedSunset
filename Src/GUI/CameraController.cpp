#include "CameraController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Messages/CameraControl.h"

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
			Logic::CCameraControl *m = new Logic::CCameraControl();

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

			default:
				return false;
			}
			_controlledTarget->emitMessage(m);
			return true;
		}
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CCameraController::keyReleased(TKey key)
	{
		if(_controlledTarget)
		{
			Logic::CCameraControl *m = new Logic::CCameraControl();

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

			default:
				return false;
			}
			_controlledTarget->emitMessage(m);
			return true;
		}
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CCameraController::mouseMoved(const CMouseState &mouseState)
	{
		if(_controlledTarget)
		{
			Logic::CCameraControl *m1 = new Logic::CCameraControl();

			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m1->setMouse(true);

			if (mouseState.posRelX <= 0)
				m1->setMovement("left");
			else if (mouseState.posRelX >= 1)
				m1->setMovement("right");
			else if ((mouseState.posRelX > 0) && (mouseState.posRelX < 1))
				m1->setMovement("stopLeftRight");

			_controlledTarget->emitMessage(m1);

			Logic::CCameraControl *m2 = new Logic::CCameraControl();

			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m2->setMouse(true);

			if (mouseState.posRelY <= 0)
				m2->setMovement("up");
			else if (mouseState.posRelY >= 1)
				m2->setMovement("down");
			else if ((mouseState.posRelY > 0) && (mouseState.posRelY < 1))
				m2->setMovement("stopUpDown");

			_controlledTarget->emitMessage(m2);
			return true;
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
		if (_controlledTarget){

			Logic::TMessage m1;
			m1._vector2.x = mouseState.posRelX;
			m1._vector2.y = mouseState.posRelY;
			m1._type = Logic::Message::CAMERA_CLICK;
			_controlledTarget->emitMessage(m1);

			return true;
		}
		return false;

	} // mouseReleased

} // namespace GUI
