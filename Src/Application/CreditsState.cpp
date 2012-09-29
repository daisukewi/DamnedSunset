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

	const int CCreditsState::nCreditWindows = 6;
	const unsigned int CCreditsState::transitionTime = 8000;

	CCreditsState::~CCreditsState()
	{
	} // ~CGameOverState

	//--------------------------------------------------------

	bool CCreditsState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Credits.layout");
		_mainWindow = CEGUI::WindowManager::getSingleton().getWindow("Credits");

		for (int i = 0; i < nCreditWindows; ++i)
		{
			std::stringstream name;
			name << "Credits/Credits" << i;
			CEGUI::Window* window = CEGUI::WindowManager::getSingleton().getWindow(name.str());
			_creditsWindow.push_back(window);
		}
	
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

		CEGUI::MouseCursor::getSingleton().hide();
		CEGUI::System::getSingletonPtr()->setGUISheet(_mainWindow);
		_mainWindow->setVisible(true);
		_mainWindow->activate();

		for (int i = 0; i < nCreditWindows; ++i)
		{
			CEGUI::Window* window = _creditsWindow[i];
			window->setAlpha(0.0f);
		}

		_currentWindow = 0;
		_acuTime = 0;
		CEGUI::Window* window = _creditsWindow[_currentWindow];
		window->setAlpha(1.0f);

	} // activate

	//--------------------------------------------------------

	void CCreditsState::deactivate() 
	{
		for (int i = 0; i < nCreditWindows; ++i)
		{
			CEGUI::Window* window = _creditsWindow[i];

			window->setVisible(false);
		}

		_mainWindow->setVisible(false);
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CCreditsState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

		_acuTime += msecs;
		if (_acuTime >= transitionTime)
		{
			_acuTime = 0;

			if (_currentWindow >= (nCreditWindows - 1))
			{
				_app->exitRequest();
				return;
			}
			
			CEGUI::Window* window1 = _creditsWindow[_currentWindow];
			window1->setAlpha(0.0f);

			CEGUI::Window* window2 = _creditsWindow[++_currentWindow];
			window2->setAlpha(1.0f);
		}

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
		return false;

	} // exitReleased

} // namespace Application
