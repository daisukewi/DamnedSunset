//---------------------------------------------------------------------------
// DummyState.h
//---------------------------------------------------------------------------

/**
@file DummyState.h

Contiene la declaraci�n de un estado tonto que no hace
nada m�s que volver al men� cuando se pulsa el bot�n.

@see Application::CApplicationState
@see Application::CDummyState

@author David Llans�
@date Agosto, 2010
*/

#ifndef __Application_DummyState_H
#define __Application_DummyState_H

#include "ApplicationState.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
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
	Como su nombre indica, �ste es un estado tonto que no hace
	nada m�s que volver al men� cuando se pulsa el bot�n.
	<p>
	Este estado es CEGUI dependiente, lo cual no es deseable, la aplicaci�n
	deber�a ser independiente de las tecnolog�as usadas.

	@ingroup applicationGroup

	@author David Llans�
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
		Funci�n llamada cuando se crea el estado (se "engancha" en la
		aplicaci�n, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init();

		/**
		Funci�n llamada cuando se elimina ("desengancha") el
		estado de la aplicaci�n.
		*/
		virtual void release();

		/**
		Funci�n llamada por la aplicaci�n cuando se activa
		el estado.
		*/
		virtual void activate();

		/**
		Funci�n llamada por la aplicaci�n cuando se desactiva
		el estado.
		*/
		virtual void deactivate();

		/**
		Funci�n llamada por la aplicaci�n para que se ejecute
		la funcionalidad del estado.

		@param msecs N�mero de milisegundos transcurridos desde
		la �ltima llamada (o desde la �ctivaci�n del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs);

		// M�todos de CKeyboardListener
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla. Ser� la aplicaci�n qui�n llame a este m�todo 
		cuando el estado est� activo. Esta clase NO se registra en
		el InputManager sino que es la aplicaci�n quien lo hace y 
		delega en los estados.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyReleased(GUI::TKey key);

	private:

		/**
		Ventana CEGUI que muestra el estado dummy.
		*/
		CEGUI::Window* _dummyWindow;
		
		/**
		Funci�n que se quiere realizar cuando se pulse el bot�n return.
		Simplemente cambia al estado de men�.
		*/
		bool returnReleased(const CEGUI::EventArgs& e);

	}; // CDummyState

} // namespace Application

#endif //  __Application_DummyState_H
