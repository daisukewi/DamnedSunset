//---------------------------------------------------------------------------
// GaleonApplication.cpp
//---------------------------------------------------------------------------

/**
@file GaleonApplication.cpp

Contiene la implementación de la clase aplicacion para aplicaciones
basadas en Ogre. Esta clase maneja la ejecución de todo el juego.

@see Application::CGaleonApplication
@see Application::C3DApplication

@author David Llansó
@date Septiembre, 2010
*/
#include "GaleonApplication.h"

#include "ExitState.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "GameState.h"
#include "LoadState.h"
#include "UnloadState.h"
#include "DayState.h"
#include "PauseState.h"

namespace Application {

	CGaleonApplication::CGaleonApplication() : C3DApplication()
	{

	} // CGaleonApplication

	//--------------------------------------------------------

	CGaleonApplication::~CGaleonApplication()
	{

	} // ~CGaleonApplication

	//--------------------------------------------------------

	bool CGaleonApplication::init() 
	{
		// Inicializamos la clase de la que heredamos.
		if (!C3DApplication::init())
			return false;

		// Creamos los estados. La aplicación se hace responsable de
		// destruirlos.
		if(!addState("gameOver", new CGameOverState(this)))
			return false;

		if(!addState("menu", new CMenuState(this)))
			return false;
		
		if(!addState("game", new CGameState(this)))
			return false;

		if(!addState("exit", new CExitState(this)))
			return false;

		//Estado en el que se gestiona la fase de día del juego
		if (!addState("day", new CDayState(this)))
			return false;

		//Estado en el que son cargados los recursos de la escena antes de iniciar la partida
		if (!addState("load", new CLoadState(this)))
			return false;

		//Estado en el que son descargados los recursos de la escen
		if (!addState("unload", new CUnloadState(this)))
			return false;

		//Estado que muestra un menu de pausa
		if (!addState("pause", new CPauseState(this)))
			return false;
		
		if(!setState("menu"))
			return false;

		return true;

	} // init

	//--------------------------------------------------------

	void CGaleonApplication::release()
	{
		// Desactivamos y eliminamos todos los estados.
		releaseAllStates();

		C3DApplication::release();

	} // release

} // namespace Application
