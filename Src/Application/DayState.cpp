//---------------------------------------------------------------------------
// LoadState.cpp
//---------------------------------------------------------------------------

/**
@file DayState.h

Contiene la implementación del estado en el que se realiza la fase de día

@see Application::CApplicationState
@see Application::CGameState

@author Alberto Ortega
@date Mayo, 2012
*/

#include "DayState.h"

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
	bool CDayState::init() 
	{
		CApplicationState::init();

		return true;

	} // init


	//--------------------------------------------------------

	void CDayState::release() 
	{

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CDayState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana de interfaz
		//GUI::CServer::getSingletonPtr()->getInterfazController()->activate();

		// Mostramos el ratón
		CEGUI::MouseCursor::getSingleton().show();

		// El siguiente código es para sincronizar el ratón de CEGUI con el de OIS.
		const OIS::MouseState state = GUI::CInputManager::getSingletonPtr()->getMouseState();
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();  
		CEGUI::System::getSingleton().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);




	} // activate

	//--------------------------------------------------------

	void CDayState::deactivate() 
	{
		// Desactivamos la ventana de tiempo y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();

		// Desactivamos la ventana de interfaz
		//GUI::CServer::getSingletonPtr()->getInterfazController()->deactivate();

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

	void CDayState::tick(unsigned int msecs) 
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

	bool CDayState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CDayState::keyReleased(GUI::TKey key)
	{

		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->setState("menu");
			break;
		case GUI::Key::G:
			_app->setState("game");
			break;
		default:
			return false;
		}
		return true;


	} // keyReleased

	//--------------------------------------------------------
	
	bool CDayState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CDayState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CDayState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------


} // namespace Application
