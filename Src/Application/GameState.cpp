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

#include "Physics/Server.h"

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>

namespace Application {

	bool CGameState::init() 
	{
		CApplicationState::init();

		// Crear la escena física.
		Physics::CServer::getSingletonPtr()->createScene();

		// Cargamos el archivo con las definiciones de las entidades del nivel.
		if (!Logic::CEntityFactory::getSingletonPtr()->loadBluePrints("blueprints.txt"))
			return false;

		// Cargamos el nivel a partir del nombre del mapa. 
		if (!Logic::CServer::getSingletonPtr()->loadLevel("map.txt"))
			return false;

		// Cargamos la ventana que muestra el tiempo de juego transcurrido.
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Time.layout");
		_timeWindow = CEGUI::WindowManager::getSingleton().getWindow("Time");

		// Cargamos la interfaz
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Interfaz.layout");
		_interfazWindow = CEGUI::WindowManager::getSingleton().getWindow("Interfaz");

		return true;

	} // init

	//--------------------------------------------------------

	void CGameState::release() 
	{
		Logic::CServer::getSingletonPtr()->unLoadLevel();

		Logic::CEntityFactory::getSingletonPtr()->unloadBluePrints();

		// Liberamos la escena física.
		Physics::CServer::getSingletonPtr()->destroyScene();

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CGameState::activate() 
	{
		CApplicationState::activate();
		
		// Activamos el mapa que ha sido cargado para la partida.
		Logic::CServer::getSingletonPtr()->activateMap();

		// Queremos que el GUI maneje al jugador y la cámara.
		GUI::CServer::getSingletonPtr()->getPlayerController()->activate();
		GUI::CServer::getSingletonPtr()->getCameraController()->activate();

		// Activamos la ventana que nos muestra el tiempo transcurrido y activamos el ratón.
		CEGUI::System::getSingletonPtr()->setGUISheet(_timeWindow);
		_timeWindow->setVisible(true);
		_timeWindow->activate();

		// Activamos la ventana de interfaz
		CEGUI::System::getSingletonPtr()->setGUISheet(_interfazWindow);
		_interfazWindow->setVisible(true);
		_interfazWindow->activate();

		CEGUI::MouseCursor::getSingleton().show();

	} // activate

	//--------------------------------------------------------

	void CGameState::deactivate() 
	{
		// Desactivamos la ventana de tiempo y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();
		_timeWindow->deactivate();
		_timeWindow->setVisible(false);

		// Desactivamos la ventana de interfaz
		_interfazWindow->deactivate();
		_interfazWindow->setVisible(false);

		// Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador.
		GUI::CServer::getSingletonPtr()->getPlayerController()->deactivate();
		
		// Desactivamos el mapa de la partida.
		Logic::CServer::getSingletonPtr()->deactivateMap();
		
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

		_time += msecs;
		
		std::stringstream text;
		text << "Time: " << _time/1000;
		_timeWindow->setText(text.str());

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
			_app->setState("menu");
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

} // namespace Application
