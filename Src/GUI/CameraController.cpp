#include "CameraController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

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
			Logic::TMessage m;
			m._type = Logic::Message::CAMERA_CONTROL;
			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m._bool = false;
			switch(key.keyId)
			{
			case GUI::Key::UPARROW:
				m._string = "up";
				break;
			case GUI::Key::DOWNARROW:
				m._string = "down";
				break;
			case GUI::Key::LEFTARROW:
				m._string = "left";
				break;
			case GUI::Key::RIGHTARROW:
				m._string = "right";
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
			Logic::TMessage m;
			m._type = Logic::Message::CAMERA_CONTROL;
			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m._bool = false;
			switch(key.keyId)
			{
			case GUI::Key::UPARROW:
			case GUI::Key::DOWNARROW:
				m._string = "stopUpDown";
				break;

			case GUI::Key::LEFTARROW:
			case GUI::Key::RIGHTARROW:
				m._string = "stopLeftRight";
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
			Logic::TMessage m1;
			m1._type = Logic::Message::CAMERA_CONTROL;
			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m1._bool = true;

			if (mouseState.posRelX <= 0)
				m1._string = "left";
			else if (mouseState.posRelX >= 1)
				m1._string = "right";
			else if ((mouseState.posRelX > 0) && (mouseState.posRelX < 1))
				m1._string = "stopLeftRight";

			_controlledTarget->emitMessage(m1);

			Logic::TMessage m2;
			m2._type = Logic::Message::CAMERA_CONTROL;
			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m2._bool = true;

			if (mouseState.posRelY <= 0)
				m2._string = "up";
			else if (mouseState.posRelY >= 1)
				m2._string = "down";
			else if ((mouseState.posRelY > 0) && (mouseState.posRelY < 1))
				m2._string = "stopUpDown";

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
		return false;

	} // mouseReleased

} // namespace GUI
