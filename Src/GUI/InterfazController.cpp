
#include "InterfazController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

#include <cassert>

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

#include <CEGUIUDim.h>

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
		_vida1 = 100000;

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

		_vida1 -= msecs;
		_vida1 %= 100000;
		float barra = _vida1 /100000.0f * 0.2;
		_interfazWindow->getChild("Interfaz/iVida1")->setWidth(CEGUI::UDim(barra,.0f));

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
		_interfazWindow->getChild("Interfaz/Menu1")->setVisible(true);
		_interfazWindow->getChild("Interfaz/Menu2")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu3")->setVisible(false);
		return true;
	}
	bool CInterfazController::clickPersonaje2(const CEGUI::EventArgs& e)
	{
		printf("Personaje2\n");
		_interfazWindow->getChild("Interfaz/Menu1")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu2")->setVisible(true);
		_interfazWindow->getChild("Interfaz/Menu3")->setVisible(false);
		return true;
	}
	bool CInterfazController::clickPersonaje3(const CEGUI::EventArgs& e)
	{
		printf("Personaje3\n");
		_interfazWindow->getChild("Interfaz/Menu1")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu2")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu3")->setVisible(true);
		return true;
	}
} // namespace GUI
