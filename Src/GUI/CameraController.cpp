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

				int n = ScriptManager::CServer::getSingletonPtr()->getGlobal("numero", 200);
				bool error = true;
				bool b = ScriptManager::CServer::getSingletonPtr()->getGlobal("booleano", error);
				std::string s = ScriptManager::CServer::getSingletonPtr()->getGlobal("cadena", "error");

				if (n != 200)
					std::cout << "Variable numérica recuperada desde lua. Valor: " << n << std::endl;
				else
					std::cout << "Algo raro ha pasado al recuperar la variable numérica" << std::endl;

				if (!error)
					std::cout << "Variable booleana recuperada desde lua. Valor: " << b << std::endl;
				else
					std::cout << "Algo raro ha pasado al recuperar la variable booleana" << std::endl;

				if (s != "error")
					std::cout << "Variable cadena recuperada desde lua. Valor: " << s << std::endl;
				else
					std::cout << "Algo raro ha pasado al recuperar la variable cadena" << std::endl;

				int n2 = ScriptManager::CServer::getSingletonPtr()->getField("tabla", "numero", 200);
				bool error2 = true;
				bool b2 = ScriptManager::CServer::getSingletonPtr()->getField("tabla", "booleano", error2);
				std::string s2 = ScriptManager::CServer::getSingletonPtr()->getField("tabla", "cadena", "error");

				if (n2 != 200)
					std::cout << "Variable numérica recuperada desde una tabla en lua. Valor: " << n2 << std::endl;
				else
					std::cout << "Algo raro ha pasado al recuperar la variable numérica desde una tabla" << std::endl;

				if (!error2)
					std::cout << "Variable booleana recuperada desde una tabla en lua. Valor: " << b2 << std::endl;
				else
					std::cout << "Algo raro ha pasado al recuperar la variable booleana desde una tabla" << std::endl;

				if (s2 != "error")
					std::cout << "Variable cadena recuperada desde una tabla en lua lua. Valor: " << s2 << std::endl;
				else
					std::cout << "Algo raro ha pasado al recuperar la variable cadena desde una tabla" << std::endl;

				if (!ScriptManager::CServer::getSingletonPtr()->executeProcedure("proc1"))
					std::cout << "Algo raro ha pasado al ejecutar el procedimiento \"proc1\"" << std::endl;

				if (!ScriptManager::CServer::getSingletonPtr()->executeProcedure("proc2", 40))
					std::cout << "Algo raro ha pasado al ejecutar el procedimiento \"proc2\"" << std::endl;

				int result = 0;
				if (!ScriptManager::CServer::getSingletonPtr()->executeFunction("funcion", 30, result))
					std::cout << "Algo raro ha pasado al ejecutar la función \"funcion\"" << std::endl;
				else
					std::cout << "Parámetro devuelto por la función \"funcion\": " << result << std::endl;

				break;
			}
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

			_controlledTarget->emitMessage(m1);

			Logic::MCameraControl *m2 = new Logic::MCameraControl();

			// Atributo del mensaje que va a indicar si se está moviendo la cámara con el ratón o no.
			m2->setMouse(true);

			if (mouseState.posRelY <= 0)
				m2->setMovement("up");
			else if (mouseState.posRelY >= 1)
				m2->setMovement("down");
			else if ((mouseState.posRelY > 0) && (mouseState.posRelY < 1))
				m2->setMovement("stopUpDown");

			_controlledTarget->emitMessage(m2);
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
	
		GUI::CInterfazController* controller = GUI::CServer::getSingletonPtr()->getInterfazController();
		
		if(!controller->isMouseOnInterface()){

			if (_controlledTarget){

			Logic::MMouseEvent *m_message = new Logic::MMouseEvent();

			if (mouseState.button == Button::LEFT)
				m_message->setAction(Logic::TMouseAction::LEFT_CLICK);
			else if (mouseState.button == Button::RIGHT)
				m_message->setAction(Logic::TMouseAction::RIGHT_CLICK);
			else if (mouseState.button == Button::MIDDLE)
				m_message->setAction(Logic::TMouseAction::MIDDLE_CLICK);


			_controlledTarget->emitMessage(m_message);
			}

		}
		return false;


	} // mouseReleased

} // namespace GUI
