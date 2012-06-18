//---------------------------------------------------------------------------
// LoadState.cpp
//---------------------------------------------------------------------------

/**
@file LoadState.h

Contiene la declaración del estado en el que se cargan los recursos

@see Application::CApplicationState
@see Application::CGameState

@author Alberto Ortega
@date Abril, 2012
*/

#include "LoadState.h"

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
	bool CLoadState::init() 
	{
		CApplicationState::init();
		
		return true;

	} // init


	//--------------------------------------------------------

	void CLoadState::release() 
	{


		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CLoadState::activate() 
	{
		CApplicationState::activate();

		//Cargar el nivel
		LoadLevel();

		// Activamos el mapa que ha sido cargado para la partida.
		Logic::CServer::getSingletonPtr()->activateMap();

		// Queremos que el GUI maneje al jugador y la cámara.
		GUI::CServer::getSingletonPtr()->getPlayerController()->activate();
		GUI::CServer::getSingletonPtr()->getCameraController()->activate();

		/*
		// Mostramos el ratón
		CEGUI::MouseCursor::getSingleton().show();

		// El siguiente código es para sincronizar el ratón de CEGUI con el de OIS.
		const OIS::MouseState state = GUI::CInputManager::getSingletonPtr()->getMouseState();
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();  
		CEGUI::System::getSingleton().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);*/

	} // activate

	//--------------------------------------------------------

	void CLoadState::deactivate() 
	{
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CLoadState::tick(unsigned int msecs) 
	{
		//Incializar el estado de día del juego
		//para hacer pruebas, esperar a pulsar la tecla esc para inicializar el juego
		_app->setState("day");

	} // tick

	//--------------------------------------------------------

	bool CLoadState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CLoadState::keyReleased(GUI::TKey key)
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
	
	bool CLoadState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CLoadState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CLoadState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	bool CLoadState::LoadLevel()
	{
		// Crear la escena física.
		Physics::CServer::getSingletonPtr()->createScene();

		//ScriptManager::CServer::getSingletonPtr()->CreateNewState();

		// Cargamos el archivo con las definiciones de las entidades del nivel.
		if (!Logic::CEntityFactory::getSingletonPtr()->loadBluePrints("blueprints.txt"))
			return false;

		// Cargamos el nivel y los arquetipos a partir de los nombres de los ficheros de script. 
		if (!Logic::CServer::getSingletonPtr()->loadLevel("map", "archetype"))
			return false;



		return true;
	}


} // namespace Application
