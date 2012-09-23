//---------------------------------------------------------------------------
// GameState.cpp
//---------------------------------------------------------------------------

/**
@file GameState.cpp

Contiene la implementaci�n del estado de juego.

@see Application::CApplicationState
@see Application::CGameState

@author David Llans�
@date Agosto, 2010
*/

#include "GameState.h"
#include "PauseState.h"

#include "Logic/Server.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"

#include "Logic\Entity\Messages\ActivarComponente.h"

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


#include "BaseSubsystems\Estadisticas.h"

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

		ScriptManager::CServer::getSingletonPtr()->executeProcedure("inicializarInterfaz");

		// Activamos la ventana de interfaz
		//ScriptManager::CServer::getSingletonPtr()->executeProcedure("activarInterfazNoche");
		//GUI::CServer::getSingletonPtr()->getInterfazController()->activate();
		//GUI::CServer::getSingletonPtr()->getInterfazController()->setEsDia(false);

		// Mostramos el rat�n
		CEGUI::MouseCursor::getSingleton().show();

		// El siguiente c�digo es para sincronizar el rat�n de CEGUI con el de OIS.
		const OIS::MouseState state = GUI::CInputManager::getSingletonPtr()->getMouseState();
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();  
		CEGUI::System::getSingleton().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);

		//Activar el componente de control de la c�mara de noche
		Logic::MActivarComponente *m = new Logic::MActivarComponente();
		m->setActivar(true);
		m->setNombreComponente("CCameraController");
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod")->emitMessage(m);

		//Inicializamos la interfaz
		ScriptManager::CServer::getSingletonPtr()->executeProcedure("cambiarANoche");

	} // activate

	//--------------------------------------------------------

	void CGameState::deactivate() 
	{
		// Desactivamos la ventana de tiempo y el rat�n.
		//CEGUI::MouseCursor::getSingleton().hide();

		// Desactivamos la ventana de interfaz
		//GUI::CServer::getSingletonPtr()->getInterfazController()->deactivate();

		/*// Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador y la c�mara.
		GUI::CServer::getSingletonPtr()->getCameraController()->deactivate();
		GUI::CServer::getSingletonPtr()->getPlayerController()->deactivate();
		
		// Desactivamos el mapa de la partida.
		Logic::CServer::getSingletonPtr()->deactivateMap();
		*/
		//UnloadLevel();

		// Desactivar el componente de control de la c�mara de noche
		Logic::MActivarComponente *m = new Logic::MActivarComponente();
		m->setActivar(false);
		m->setNombreComponente("CCameraController");
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod")->emitMessage(m);
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CGameState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

		// Simulaci�n f�sica
		Physics::CServer::getSingletonPtr()->tick(msecs / 1000.0f);

		// Actualizamos la l�gica de juego.
		Logic::CServer::getSingletonPtr()->tick(msecs);

		//Actualizamos la interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->tick(msecs);

		PRINT_STATS(msecs);
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
			CPauseState::returnState = "game";
			_app->setState("pause");
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
