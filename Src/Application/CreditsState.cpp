//---------------------------------------------------------------------------
// CreditsState.cpp
//---------------------------------------------------------------------------

/**
@file CreditsState.cpp

Contiene la implementación del estado de game over.

@see Application::CApplicationState
@see Application::CCreditsState

@author David Llansó
@date Agosto, 2010
*/

#include "CreditsState.h"

#include "GUI/Server.h"

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

namespace Application {

	CCreditsState::~CCreditsState() 
	{
	} // ~CGameOverState

	//--------------------------------------------------------

	bool CCreditsState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Credits.layout");
		_gameOverWindow = CEGUI::WindowManager::getSingleton().getWindow("Credits");
		
		/*CEGUI::WindowManager::getSingleton().getWindow("GameOver/Exit")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CCreditsState::exitReleased, this));*/
	
		return true;

	} // init

	//--------------------------------------------------------

	void CCreditsState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CCreditsState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->setGUISheet(_gameOverWindow);
		_gameOverWindow->setVisible(true);
		_gameOverWindow->activate();
		CEGUI::MouseCursor::getSingleton().show();

	} // activate

	//--------------------------------------------------------

	void CCreditsState::deactivate() 
	{		
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();
		_gameOverWindow->deactivate();
		_gameOverWindow->setVisible(false);
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CCreditsState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CCreditsState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CCreditsState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->exitRequest();
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CCreditsState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CCreditsState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CCreditsState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased
			
	//--------------------------------------------------------

	bool CCreditsState::exitReleased(const CEGUI::EventArgs& e)
	{
		_app->exitRequest();
		return true;

	} // exitReleased

} // namespace Application
