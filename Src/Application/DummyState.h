//---------------------------------------------------------------------------
// DummyState.h
//---------------------------------------------------------------------------

/**
@file DummyState.h

Contiene la declaración de un estado tonto que no hace
nada más que volver al menú cuando se pulsa el botón.

@see Application::CApplicationState
@see Application::CDummyState

@author David Llansó
@date Agosto, 2010
*/

#ifndef __Application_DummyState_H
#define __Application_DummyState_H

#include "ApplicationState.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Application 
{
	class CBaseApplication;
}

namespace CEGUI
{
	class EventArgs;
	class Window;
}

namespace Application 
{
	/**
	Como su nombre indica, éste es un estado tonto que no hace
	nada más que volver al menú cuando se pulsa el botón.
	<p>
	Este estado es CEGUI dependiente, lo cual no es deseable, la aplicación
	debería ser independiente de las tecnologías usadas.

	@ingroup applicationGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class CDummyState : public CApplicationState 
	{
	public:
		/** 
		Constructor de la clase 
		*/
		CDummyState(CBaseApplication *app) : CApplicationState(app)
				{}

		/** 
		Destructor 
		*/
		virtual ~CDummyState();

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

	private:

		/**
		Ventana CEGUI que muestra el estado dummy.
		*/
		CEGUI::Window* _dummyWindow;
		
		/**
		Función que se quiere realizar cuando se pulse el botón return.
		Simplemente cambia al estado de menú.
		*/
		bool returnReleased(const CEGUI::EventArgs& e);

	}; // CDummyState

} // namespace Application

#endif //  __Application_DummyState_H
