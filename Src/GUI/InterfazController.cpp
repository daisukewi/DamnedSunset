
#include "InterfazController.h"
#include "InputManager.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

#include "Logic/Maps/Map.h"

#include <cassert>

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

#include <CEGUIUDim.h>

//Mensajes
#include "Logic/Entity/Messages/UbicarCamara.h"


//Includes para crear entidades dinamicamente
#include "Map/MapEntity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"


#include "Logic\Entity\Message.h"
#include "Logic\Entity\Messages\EmplaceBuilding.h"
#include "Logic\Entity\Messages\Damaged.h"
#include "Logic\Entity\Messages\EntitySelected.h"
#include "Logic\Entity\Messages\ActivateSkill.h"

#include "Logic\Entity\Messages\CrearBillboardMovimiento.h"

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
		_entidadDios = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("TargetCamera");

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
		Logic::MDamaged *m = new Logic::MDamaged();
		m->setHurt(msecs/1000.0f);

		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack")->emitMessage(m);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick")->emitMessage(m);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Amor")->emitMessage(m);
	}

	void CInterfazController::actualizarBarraVida(char numPersonaje, float porcentajeVida) {
		std::string urlVida = "Interfaz/iVida";
		urlVida+=numPersonaje;
		_interfazWindow->getChild(urlVida)->setWidth(CEGUI::UDim(porcentajeVida*0.2,.0f));
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
		this->cargarBoton('4',"jeringa");
	}
	

	/**
		GESTIONA LA NAVEGACION ENTRE LOS BOTONES
	**/
	bool CInterfazController::clickPersonaje1(const CEGUI::EventArgs& e)
	{
		this->menuJugador1();
		this->sendClickMessage("Jack");

		return true;
	}
	bool CInterfazController::clickPersonaje2(const CEGUI::EventArgs& e)
	{
		this->menuJugador2();
		this->sendClickMessage("Erick");

		return true;
	}
	bool CInterfazController::clickPersonaje3(const CEGUI::EventArgs& e)
	{
		this->menuJugador3();
		this->sendClickMessage("Amor");

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

		Logic::MEmplaceBuilding *buildMessage = new Logic::MEmplaceBuilding();
		buildMessage->setAction(Logic::BuildingMessage::START_BUILDING);
		buildMessage->setBuildingType("Turret");

		return player->emitMessage(buildMessage);
	}
	bool CInterfazController::clickB3(const CEGUI::EventArgs& e)
	{

		return true;
	}
	bool CInterfazController::clickB4(const CEGUI::EventArgs& e)
	{
		/** PRUBA PARA VER QUE FUNCIONA sacar los valores del arquetipo*/
		Map::CEntity * mapEntity = Map::CMapParser::getSingletonPtr()->getEntitieInfo("Barril");
		//Hay que cambiarle el nombre xq sino solo se crearia el primero (coja la vida1 x coger cualquier cosa)
		std::stringstream ss;
		ss << _vida1;
		mapEntity->setName(ss.str());
		Logic::CEntity *entity = Logic::CEntityFactory::getSingletonPtr()->createEntity(mapEntity,Logic::CServer::getSingletonPtr()->getMap());
		/* FIN PRUEBA */

		/**MENSAJE PRUEBA PARA BILLBOARD DE MOVIMIENTO**/
		Logic::MCrearBillboardMovimiento *m = new Logic::MCrearBillboardMovimiento();
		m->setPosX(20);
		m->setPosY(20);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("World")->emitMessage(m);
		

		if (_jugadorSel == 3)
		{
			Logic::MActivateSkill *m_skill = new Logic::MActivateSkill();
			m_skill->setSkill(true);
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(m_skill);
		}
		return true;
	}

	void CInterfazController::sendClickMessage(std::string name)
	{
		Logic::CEntity *player = Logic::CServer::getSingletonPtr()->getPlayer();
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName(name);

		Logic::MEntitySelected *m_selection = new Logic::MEntitySelected();
		m_selection->setSelectedEntity(entity);
		player->emitMessage(m_selection);

	}
} // namespace GUI
