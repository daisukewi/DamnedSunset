
#include "InterfazController.h"
#include "InputManager.h"

#include "Logic/Server.h"
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
		this->ocultarBotones();

		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje1")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje1, this));

		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje2")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje2, this));

		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje3")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje3, this));

		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/Menu/b1")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickB1, this));
		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/Menu/b2")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickB2, this));
		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/Menu/b3")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickB3, this));
		CEGUI::WindowManager::getSingleton().getWindow("Interfaz/Menu/b4")->
			subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickB4, this));
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
		float barra = _vida1 /100000.0 * 0.2;
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

	/**
		VISUALIZAR LOS DISTINTOS BOTONES Y MENUS
	**/
	void CInterfazController::ocultarBotones() {
		_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b1")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b2")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b3")->setVisible(false);
		_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b4")->setVisible(false);
	}
	void CInterfazController::cargarBoton(char numBoton, std::string nombreBoton) {
		std::string nombreHijo = "Interfaz/Menu/b";
		nombreHijo+=numBoton;
		std::string imagen1 = "set:InterfazUtils image:";
		std::string imagen2 = "set:InterfazUtils image:";
		std::string imagen3 = "set:InterfazUtils image:";
		imagen1.append(nombreBoton);
		imagen2.append(nombreBoton)+='2';
		imagen3.append(nombreBoton)+='3';

		_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setProperty("NormalImage",imagen1);
		_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setProperty("HoverImage",imagen2);
		_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setProperty("PushedImage",imagen3);
		_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setVisible(true);
	}

	void CInterfazController::menuJugador1() {
		_estado = normal;
		_jugadorSel = 1;
		this->ocultarBotones();
		this->cargarBoton('1', "martillo");
		this->cargarBoton('4',"granada");
	}
	void CInterfazController::menuJugador2() {
		_estado = normal;
		_jugadorSel = 2;
		this->ocultarBotones();
		this->cargarBoton('1',"martillo");
	}

	void CInterfazController::menuJugador3() {
		_estado = normal;
		_jugadorSel = 3;
		this->ocultarBotones();
		this->cargarBoton('1',"martillo");
	}
	

	/**
		GESTIONA LA NAVEGACION ENTRE LOS BOTONES
	**/
	bool CInterfazController::clickPersonaje1(const CEGUI::EventArgs& e)
	{
		this->menuJugador1();
		return true;
	}
	bool CInterfazController::clickPersonaje2(const CEGUI::EventArgs& e)
	{
		this->menuJugador2();
		return true;
	}
	bool CInterfazController::clickPersonaje3(const CEGUI::EventArgs& e)
	{
		this->menuJugador3();
		return true;
	}
	bool CInterfazController::clickB1(const CEGUI::EventArgs& e)
	{
		switch (_estado) {
		case normal:
			//BOTON CONSTRUIR
			_estado = construir;
			this->ocultarBotones();
			this->cargarBoton('1',"volver");
			this->cargarBoton('2',"torreta");
			break;
		case construir:
			//BOTON VOLVER
			_estado = normal;
			switch (_jugadorSel) {
				case 1: this->menuJugador1(); break;
				case 2: this->menuJugador2(); break;
				case 3: this->menuJugador3(); break;
			}
			break;
		}
		return true;
	}
	bool CInterfazController::clickB2(const CEGUI::EventArgs& e)
	{
		Logic::CEntity *player = Logic::CServer::getSingletonPtr()->getPlayer();

		Logic::TMessage m;
		m._type = Logic::Message::BUILD_START;
		m._string = "Turret";

		return player->emitMessage(m);
	}
	bool CInterfazController::clickB3(const CEGUI::EventArgs& e)
	{

		return true;
	}
	bool CInterfazController::clickB4(const CEGUI::EventArgs& e)
	{

		return true;
	}
} // namespace GUI
