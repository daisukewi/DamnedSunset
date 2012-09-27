//---------------------------------------------------------------------------
// GameOverState.cpp
//---------------------------------------------------------------------------

/**
@file GameOverState.cpp

Contiene la implementación del estado de game over.

@see Application::CApplicationState
@see Application::CGameOverState

@author David Llansó
@date Agosto, 2010
*/

#include "GameOverState.h"

#include "Logic/Server.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"

#include "Physics/Server.h"
#include "ScriptManager/Server.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/CameraController.h"
#include "GUI/InterfazController.h"

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

namespace Application {

	CGameOverState::~CGameOverState() 
	{
	} // ~CGameOverState

	//--------------------------------------------------------

	bool CGameOverState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("GameOver.layout");
		_gameOverWindow = CEGUI::WindowManager::getSingleton().getWindow("GameOver");
		
		CEGUI::WindowManager::getSingleton().getWindow("GameOver/Exit")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CGameOverState::exitReleased, this));
	
		return true;

	} // init

	//--------------------------------------------------------

	void CGameOverState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CGameOverState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->setGUISheet(_gameOverWindow);
		_gameOverWindow->setVisible(true);
		_gameOverWindow->activate();
		CEGUI::MouseCursor::getSingleton().show();

	} // activate

	//--------------------------------------------------------

	void CGameOverState::deactivate() 
	{
		// Desactivamos la ventana de interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->deactivate();

		//Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador y la cámara.
		GUI::CServer::getSingletonPtr()->getCameraController()->deactivate();
		GUI::CServer::getSingletonPtr()->getPlayerController()->deactivate();

		// Desactivamos el mapa de la partida.
		//Logic::CServer::getSingletonPtr()->unLoadLevel();

		UnloadLevel();

		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();
		_gameOverWindow->deactivate();
		_gameOverWindow->setVisible(false);
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CGameOverState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CGameOverState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CGameOverState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->setState("credits");
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CGameOverState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CGameOverState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CGameOverState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased
			
	//--------------------------------------------------------

	bool CGameOverState::exitReleased(const CEGUI::EventArgs& e)
	{
		_app->setState("credits");
		return true;

	} // exitReleased

	//--------------------------------------------------------

	void CGameOverState::UnloadLevel()
	{
		Logic::CServer::getSingletonPtr()->unLoadLevel();

		Logic::CEntityFactory::getSingletonPtr()->unloadBluePrints();

		Map::CMapParser::getSingletonPtr()->releaseEntityList();

		ScriptManager::CServer::getSingletonPtr()->ResetCurrentState();

		// Liberamos la escena física.
		Physics::CServer::getSingletonPtr()->destroyScene();
	}

} // namespace Application
