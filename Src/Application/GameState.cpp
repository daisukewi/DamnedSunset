//---------------------------------------------------------------------------
// GameState.cpp
//---------------------------------------------------------------------------

/**
@file GameState.cpp

Contiene la implementación del estado de juego.

@see Application::CApplicationState
@see Application::CGameState

@author David Llansó
@date Agosto, 2010
*/

#include "GameState.h"

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
	bool CGameState::init() 
	{
		CApplicationState::init();

		return true;

	} // init


	//--------------------------------------------------------

	void CGameState::release() 
	{

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CGameState::activate() 
	{
		CApplicationState::activate();

		//LoadLevel();
	/*	
		// Activamos el mapa que ha sido cargado para la partida.
		Logic::CServer::getSingletonPtr()->activateMap();

		// Queremos que el GUI maneje al jugador y la cámara.
		GUI::CServer::getSingletonPtr()->getPlayerController()->activate();
		GUI::CServer::getSingletonPtr()->getCameraController()->activate();*/

		// Activamos la ventana de interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->activate();
		GUI::CServer::getSingletonPtr()->getInterfazController()->setEsDia(false);

		// Mostramos el ratón
		CEGUI::MouseCursor::getSingleton().show();

		// El siguiente código es para sincronizar el ratón de CEGUI con el de OIS.
		const OIS::MouseState state = GUI::CInputManager::getSingletonPtr()->getMouseState();
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();  
		CEGUI::System::getSingleton().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);

	} // activate

	//--------------------------------------------------------

	void CGameState::deactivate() 
	{
		// Desactivamos la ventana de tiempo y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();

		// Desactivamos la ventana de interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->deactivate();

		/*// Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador y la cámara.
		GUI::CServer::getSingletonPtr()->getCameraController()->deactivate();
		GUI::CServer::getSingletonPtr()->getPlayerController()->deactivate();
		
		// Desactivamos el mapa de la partida.
		Logic::CServer::getSingletonPtr()->deactivateMap();
		*/
		//UnloadLevel();
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CGameState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

		// Simulación física
		Physics::CServer::getSingletonPtr()->tick(msecs / 1000.0f);

		// Actualizamos la lógica de juego.
		Logic::CServer::getSingletonPtr()->tick(msecs);

		//Actualizamos la interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->tick(msecs);
	} // tick

	//--------------------------------------------------------

	bool CGameState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CGameState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->setState("unload");
			break;
		case GUI::Key::D:
			//_app->setState("day");
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CGameState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CGameState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CGameState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------


} // namespace Application
