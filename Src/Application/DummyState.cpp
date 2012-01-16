//---------------------------------------------------------------------------
// DummyState.cpp
//---------------------------------------------------------------------------

/**
@file DummyState.cpp

Contiene la implementación de un estado tonto que no hace
nada más que volver al menú cuando se pulsa el botón.

@see Application::CApplicationState
@see Application::CDummyState

@author David Llansó
@date Agosto, 2010
*/

#include "DummyState.h"

#include "GUI/Server.h"

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

namespace Application {

	CDummyState::~CDummyState() 
	{
	} // ~CDummyState

	//--------------------------------------------------------

	bool CDummyState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el estado dummy
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Dummy.layout");
		_dummyWindow = CEGUI::WindowManager::getSingleton().getWindow("Dummy");
		
		// Asociamos el boton del estado con la funcion que se debe ejecutar.
		CEGUI::WindowManager::getSingleton().getWindow("Dummy/Return")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CDummyState::returnReleased, this));
	
		return true;

	} // init

	//--------------------------------------------------------

	void CDummyState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CDummyState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el estado dummy y activamos el ratón.
		CEGUI::System::getSingletonPtr()->setGUISheet(_dummyWindow);
		_dummyWindow->setVisible(true);
		_dummyWindow->activate();
		CEGUI::MouseCursor::getSingleton().show();

	} // activate

	//--------------------------------------------------------

	void CDummyState::deactivate() 
	{		
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::MouseCursor::getSingleton().hide();
		_dummyWindow->deactivate();
		_dummyWindow->setVisible(false);
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CDummyState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CDummyState::keyReleased(GUI::TKey key)
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
		
	bool CDummyState::returnReleased(const CEGUI::EventArgs& e)
	{
		_app->setState("menu");
		return true;

	} // startReleased

} // namespace Application
