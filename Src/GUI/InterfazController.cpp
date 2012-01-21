
#include "InterfazController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

#include <cassert>

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

namespace GUI {

	CInterfazController::CInterfazController()
	{

	} 

	//--------------------------------------------------------

	CInterfazController::~CInterfazController()
	{
		deactivate();
	}

	bool CInterfazController::init()
	{
		// Cargamos la interfaz
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Interfaz.layout");
		_interfazWindow = CEGUI::WindowManager::getSingleton().getWindow("Interfaz");

		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje1")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje1, this));

		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje2")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje2, this));

		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje3")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje3, this));
		_time = 0;
		return true;
	}
	//--------------------------------------------------------

	void CInterfazController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);

		// Activamos la ventana de interfaz
		CEGUI::System::getSingletonPtr()->setGUISheet(_interfazWindow);
		_interfazWindow->setVisible(true);
		_interfazWindow->activate();
	}

	//--------------------------------------------------------

	void CInterfazController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);

		_interfazWindow->deactivate();
		_interfazWindow->setVisible(false);
	} // deactivate

	void CInterfazController::tick(unsigned int msecs)
	{
		_time += msecs;
		std::stringstream text;
		text << "Time: " << _time/1000;
		_interfazWindow->getChild("Interfaz/Tiempo")->setText(text.str());
	}
	//--------------------------------------------------------

	bool CInterfazController::keyPressed(TKey key)
	{
		return false;
	}

	//--------------------------------------------------------

	bool CInterfazController::keyReleased(TKey key)
	{
		return false;

	}

	bool CInterfazController::clickPersonaje1(const CEGUI::EventArgs& e)
	{
		printf("Personaje1\n");
		return true;
	}
	bool CInterfazController::clickPersonaje2(const CEGUI::EventArgs& e)
	{
		printf("Personaje2\n");
		return true;
	}
	bool CInterfazController::clickPersonaje3(const CEGUI::EventArgs& e)
	{
		printf("Personaje3\n");
		return true;
	}
} // namespace GUI
