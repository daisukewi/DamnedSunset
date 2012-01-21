

#ifndef __GUI_InterfazController_H
#define __GUI_InterfazController_H

#include "InputManager.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CEntity;
}

namespace CEGUI
{
	class EventArgs;
	class Window;
}

// Declaraci�n de la clase
namespace GUI
{


	class CInterfazController : public CKeyboardListener
	{
	public:

		/**
		Constructor.
		*/
		CInterfazController ();

		/**
		Destructor.
		*/
		~CInterfazController();


		bool init();
		/**
		Activa la la clase, se registra en el CInputManager y as� empieza a 
		escuchar eventos.
		*/
		void activate();

		/**
		Desctiva la la clase, se deregistra en el CInputManager y deja de 
		escuchar eventos.
		*/
		void deactivate();

		void CInterfazController::tick(unsigned int msecs);
		/***************************************************************
		M�todos de CKeyboardListener
		***************************************************************/
		
		/**
		M�todo que ser� invocado siempre que se pulse una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool keyPressed(TKey key);
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool keyReleased(TKey key);

		bool clickPersonaje1(const CEGUI::EventArgs& e);
		bool clickPersonaje2(const CEGUI::EventArgs& e);
		bool clickPersonaje3(const CEGUI::EventArgs& e);

		unsigned int _time;

		CEGUI::Window* _interfazWindow;

	protected:

	private:
		
	};

} // namespace GUI

#endif
