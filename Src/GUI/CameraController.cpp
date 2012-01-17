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
			switch(key.keyId)
			{
			case GUI::Key::UPARROW:
				m._string = "stopUp";
				break;
			case GUI::Key::DOWNARROW:
				m._string = "stopDown";
				break;
			case GUI::Key::LEFTARROW:
				m._string = "stopLeft";
				break;
			case GUI::Key::RIGHTARROW:
				m._string = "stopRight";
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
		/*if(_controlledTarget)
		{
			Logic::TMessage m;
			m._type = Logic::Message::CONTROL;
			m._string = "turn";
			m._float = -(float)mouseState.movX * TURN_FACTOR;
			_controlledTarget->emitMessage(m);
			return true;
		}*/
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
