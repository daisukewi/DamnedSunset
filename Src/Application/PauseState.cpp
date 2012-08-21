//---------------------------------------------------------------------------
// PauseState.cpp
//---------------------------------------------------------------------------

/**
@file PauseState.h

Contiene la declaración del estado en el que se cargan los recursos

@see Application::CApplicationState
@see Application::CGameState

@author Daniel Flamenco
@date Agosto, 2012
*/

#include "PauseState.h"

#include "Logic/Server.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/CameraController.h"
#include "GUI/InterfazController.h"

#include "GUI/Server.h"
#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

namespace GUI 
{
	class CInterfazController;
}

namespace Application {

	char* CPauseState::returnState = "day";

	bool CPauseState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra una pantalla de carga
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Pause.layout");

		_window = CEGUI::WindowManager::getSingleton().getWindow("Pause");

		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		CEGUI::WindowManager::getSingleton().getWindow("Pause/Resume")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
			CEGUI::SubscriberSlot(&CPauseState::resumeReleased, this));

		CEGUI::WindowManager::getSingleton().getWindow("Pause/Exit")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
			CEGUI::SubscriberSlot(&CPauseState::exitReleased, this));

		return true;

	} // init

	//--------------------------------------------------------

	void CPauseState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CPauseState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->setGUISheet(_window);
		_window->setVisible(true);
		_window->activate();

		// Mostramos el ratón
		CEGUI::MouseCursor::getSingleton().show();

	} // activate

	//--------------------------------------------------------

	void CPauseState::deactivate() 
	{
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CPauseState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CPauseState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CPauseState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->setState(returnState);
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------

	bool CPauseState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------

	bool CPauseState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CPauseState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	bool CPauseState::resumeReleased(const CEGUI::EventArgs& e)
	{
		//Ir al estado de juego
		_app->setState(returnState);
		//_app->setState("game");
		return true;

	} // startReleased

	//--------------------------------------------------------

	bool CPauseState::exitReleased(const CEGUI::EventArgs& e)
	{
		_app->setState("unload");
		return true;

	} // exitReleased

} // namespace Application
