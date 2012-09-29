//---------------------------------------------------------------------------
// UnloadState.cpp
//---------------------------------------------------------------------------

/**
@file UnloadState.h

Contiene la declaración del estado en el que se cargan los recursos

@see Application::CApplicationState
@see Application::CGameState

@author Alberto Ortega
@date Abril, 2012
*/

#include "UnloadState.h"

#include "Logic/Server.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/CameraController.h"
#include "GUI/InterfazController.h"

#include "Physics/Server.h"
#include "ScriptManager/Server.h"

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
	bool CUnloadState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra una pantalla de carga
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Saving.layout");

		_window = CEGUI::WindowManager::getSingleton().getWindow("Saving");

		return true;

	} // init

	//--------------------------------------------------------

	void CUnloadState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CUnloadState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->setGUISheet(_window);
		_window->setVisible(true);
		_window->activate();

		// Desactivamos la ventana de tiempo y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();

	} // activate

	//--------------------------------------------------------

	void CUnloadState::deactivate() 
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

		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CUnloadState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

		//Después de descargar la escena, volver al menú
		_app->setState("menu");

	} // tick

	//--------------------------------------------------------

	bool CUnloadState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CUnloadState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::RETURN:
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CUnloadState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CUnloadState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CUnloadState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	void CUnloadState::UnloadLevel()
	{
		Logic::CServer::getSingletonPtr()->unLoadLevel();

		Logic::CEntityFactory::getSingletonPtr()->unloadBluePrints();

		Map::CMapParser::getSingletonPtr()->releaseEntityList();

		ScriptManager::CServer::getSingletonPtr()->ResetCurrentState();
		
		// Liberamos la escena física.
		Physics::CServer::getSingletonPtr()->destroyScene();
	}

} // namespace Application
