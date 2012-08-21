//---------------------------------------------------------------------------
// PauseState.h
//---------------------------------------------------------------------------

/**
@file PauseState.h

Contiene la declaración del estado en el que se esta en pausa

@see Application::CApplicationState
@see Application::CGameState

@author Daniel Flamenco
@date Agosto, 2012
*/

#ifndef __Application_PauseState_H
#define __Application_PauseState_H

#include "ApplicationState.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Application 
{
	class CBaseApplication;
}

namespace Graphics 
{
	class CScene;
	class CCamera;
	class CEntity;
	class CStaticEntity;
	class CAnimatedEntity;
}

namespace CEGUI
{
	class EventArgs;
	class Window;
}

namespace Application 
{
	/*
	Se encarga de mostrar una pantalla de pausa
	

	@ingroup applicationGroup

	@author Daniel Flamenco
	@date Agosto, 2012
	*/
	class CPauseState : public CApplicationState 
	{
	public:
		/** 
		Constructor de la clase 
		*/
		CPauseState(CBaseApplication *app) : CApplicationState(app), 
				_scene(0) {}

		/** 
		Destructor 
		*/
		virtual ~CPauseState() {}

		/**
		Función llamada cuando se crea el estado (se "engancha" en la
		aplicación, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init();

		/**
		Función llamada cuando se elimina ("desengancha") el
		estado de la aplicación.
		*/
		virtual void release();

		/**
		Función llamada por la aplicación cuando se activa
		el estado.
		*/
		virtual void activate();

		/**
		Función llamada por la aplicación cuando se desactiva
		el estado.
		*/
		virtual void deactivate();

		/**
		Función llamada por la aplicación para que se ejecute
		la funcionalidad del estado.

		@param msecs Número de milisegundos transcurridos desde
		la última llamada (o desde la áctivación del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs);

		// Métodos de CKeyboardListener
		
		/**
		Método que será invocado siempre que se pulse una tecla. 
		Será la aplicación quién llame a este método cuando el 
		estado esté activo. Esta clase NO se registra en el 
		InputManager sino que es la aplicación quien lo hace y 
		delega en los estados.

		@param key Código de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool keyPressed(GUI::TKey key);
		
		/**
		Método que será invocado siempre que se termine la pulsación
		de una tecla. Será la aplicación quién llame a este método 
		cuando el estado esté activo. Esta clase NO se registra en
		el InputManager sino que es la aplicación quien lo hace y 
		delega en los estados.

		@param key Código de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool keyReleased(GUI::TKey key);

		// Métodos de CMouseListener
		
		/**
		Método que será invocado siempre que se mueva el ratón. La
		aplicación avisa de este evento al estado actual.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool mouseMoved(const GUI::CMouseState &mouseState);
		
		/**
		Método que será invocado siempre que se pulse un botón. La
		aplicación avisa de este evento al estado actual.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool mousePressed(const GUI::CMouseState &mouseState);

		/**
		Método que será invocado siempre que se termine la pulsación
		de un botón. La aplicación avisa de este evento al estado 
		actual.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners. 
		*/
		virtual bool mouseReleased(const GUI::CMouseState &mouseState);

		static char* returnState;

	protected:

		/**
		Escena del estado.
		*/
		Graphics::CScene* _scene;

	private:

		/**
		Ventana CEGUI.
		*/
		CEGUI::Window* _window;

		/**
		Función que se quiere realizar cuando se pulse el botón start.
		Simplemente cambia al estado de juego.
		*/
		bool resumeReleased(const CEGUI::EventArgs& e);

		/**
		Función que se quiere realizar cuando se pulse el botón exit.
		Simplemente termina la aplicación.
		*/
		bool exitReleased(const CEGUI::EventArgs& e);

	}; // CPauseState

} // namespace Application

#endif //  __Application_PauseState_H
