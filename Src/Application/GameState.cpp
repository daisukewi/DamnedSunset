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

#include <stdio.h>
#include <string.h>

namespace GUI 
{
	class CInterfazController;
}

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

		//Inicializamos la interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->init();


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

		// Activamos la ventana de interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->activate();

		// Mostramos el ratón
		CEGUI::MouseCursor::getSingleton().show();

		// El siguiente código es para sincronizar el ratón de CEGUI con el de OIS.
		const OIS::MouseState state = GUI::CInputManager::getSingletonPtr()->getMouseState();
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();  
		CEGUI::System::getSingleton().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);

		ScriptManager::CServer::getSingletonPtr()->loadExeScript("prueba1");
		ScriptManager::CServer::getSingletonPtr()->loadExeScript("prueba2");
		ScriptManager::CServer::getSingletonPtr()->executeScript("print(\"Hello world ejecutando a pelo\")");
		ScriptManager::CServer::getSingletonPtr()->executeScript("helloWorld()");

		int n = ScriptManager::CServer::getSingletonPtr()->getGlobal("numero", 200);
		bool error = true;
		bool b = ScriptManager::CServer::getSingletonPtr()->getGlobal("booleano", error);
		std::string s = ScriptManager::CServer::getSingletonPtr()->getGlobal("cadena", "error");

		if (n != 200)
			std::cout << "Variable numérica recuperada desde lua. Valor: " << n << std::endl;
		else
			std::cout << "Algo raro ha pasado al recuperar la variable numérica" << std::endl;

		if (!error)
			std::cout << "Variable booleana recuperada desde lua. Valor: " << b << std::endl;
		else
			std::cout << "Algo raro ha pasado al recuperar la variable booleana" << std::endl;

		if (s != "error")
			std::cout << "Variable cadena recuperada desde lua. Valor: " << s << std::endl;
		else
			std::cout << "Algo raro ha pasado al recuperar la variable cadena" << std::endl;

		int n2 = ScriptManager::CServer::getSingletonPtr()->getField("tabla", "numero", 200);
		bool error2 = true;
		bool b2 = ScriptManager::CServer::getSingletonPtr()->getField("tabla", "booleano", error2);
		std::string s2 = ScriptManager::CServer::getSingletonPtr()->getField("tabla", "cadena", "error");

		if (n2 != 200)
			std::cout << "Variable numérica recuperada desde una tabla en lua. Valor: " << n2 << std::endl;
		else
			std::cout << "Algo raro ha pasado al recuperar la variable numérica desde una tabla" << std::endl;

		if (!error2)
			std::cout << "Variable booleana recuperada desde una tabla en lua. Valor: " << b2 << std::endl;
		else
			std::cout << "Algo raro ha pasado al recuperar la variable booleana desde una tabla" << std::endl;

		if (s2 != "error")
			std::cout << "Variable cadena recuperada desde una tabla en lua lua. Valor: " << s2 << std::endl;
		else
			std::cout << "Algo raro ha pasado al recuperar la variable cadena desde una tabla" << std::endl;

		if (!ScriptManager::CServer::getSingletonPtr()->executeProcedure("proc1"))
			std::cout << "Algo raro ha pasado al ejecutar el procedimiento \"proc1\"" << std::endl;

		if (!ScriptManager::CServer::getSingletonPtr()->executeProcedure("proc2", 40))
			std::cout << "Algo raro ha pasado al ejecutar el procedimiento \"proc2\"" << std::endl;

		int result = 0;
		if (!ScriptManager::CServer::getSingletonPtr()->executeFunction("funcion", 30, result))
			std::cout << "Algo raro ha pasado al ejecutar la función \"funcion\"" << std::endl;
		else
			std::cout << "Parámetro devuelto por la función \"funcion\": " << result << std::endl;

	} // activate

	//--------------------------------------------------------

	void CGameState::deactivate() 
	{
		// Desactivamos la ventana de tiempo y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();

		// Desactivamos la ventana de interfaz
		GUI::CServer::getSingletonPtr()->getInterfazController()->deactivate();

		// Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador y la cámara.
		GUI::CServer::getSingletonPtr()->getCameraController()->deactivate();
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
