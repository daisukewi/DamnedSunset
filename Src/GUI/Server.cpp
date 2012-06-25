/**
@file Server.cpp

Contiene la implementación de la clase CServer, Singleton que se encarga de
la gestión de la interfaz con el usuario (entrada de periféricos, CEGui...).

@see GUI::CServer

@author David Llansó
@date Agosto, 2010
*/

#include "Server.h"

#include "PlayerController.h"
#include "CameraController.h"
#include "InterfazController.h"
#include "InputManager.h"

#include "Ogre.h"
#include "OgreRoot.h"

#include "BaseSubsystems/Server.h"

#include <cassert>
#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <CEGUISchemeManager.h>
#include <CEGUIFontManager.h>
#include <ScriptingModules\LuaScriptModule\CEGUILua.h>
#include "ScriptManager/Server.h"
#include "RendererModules\Ogre\CEGUIOgreRenderer.h"

namespace GUI {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer() : _playerController(0), _mouseRelPosX(0), _mouseRelPosY(0)
	{
		_instance = this;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicialización de GUI::CServer no permitida!");

		new CServer();

		if (!_instance->open())
		{
			Release();
			return false;
		}

		return true;

	} // Init

	//--------------------------------------------------------

	void CServer::Release()
	{
		assert(_instance && "GUI::CServer no está inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		_playerController = new CPlayerController();
		_interfazController = new CInterfazController();
		_cameraController = new CCameraController();
		
		_GUISystem = BaseSubsystems::CServer::getSingletonPtr()->getGUISystem();

		//@TODO: Si vemos que tal y nos quedamos con CEGUI poner esta inicialización de CEGUI en el archivo xml
		// de configuración inicial.
		ScriptManager::CServer::getSingletonPtr()->loadExeScript("interfaz/initCEGUI");

#ifndef NON_EXCLUSIVE_MODE_IN_WINDOW_MODE 
		// Establecemos cual será el puntero del ratón.
		_GUISystem->setDefaultMouseCursor("OgreTrayImages","MouseArrow");
#endif	

		CInputManager::getSingletonPtr()->addMouseListener(this);
		CInputManager::getSingletonPtr()->addKeyListener(this);

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

		delete _playerController;
		delete _cameraController;

	} // close

	//--------------------------------------------------------

	bool CServer::keyPressed(TKey key)
	{
		_GUISystem->injectKeyDown(key.keyId);    
		_GUISystem->injectChar(key.text);    

		
		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CServer::keyReleased(TKey key)
	{
		_GUISystem->injectKeyUp(key.keyId);

		
		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CServer::mouseMoved(const CMouseState &mouseState)
	{
		_mouseRelPosX = mouseState.posRelX;
		_mouseRelPosY = mouseState.posRelY;

#if defined NON_EXCLUSIVE_MODE_IN_WINDOW_MODE
		_GUISystem->injectMousePosition((float)mouseState.posAbsX,(float)mouseState.posAbsY);
#else 
		_GUISystem->injectMouseMove((float)mouseState.movX,(float)mouseState.movY);
#endif	
		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CServer::mousePressed(const CMouseState &mouseState)
	{
		switch (mouseState.button)
		{
		case Button::LEFT:
			_GUISystem->injectMouseButtonDown(CEGUI::LeftButton);
		case Button::RIGHT:
			_GUISystem->injectMouseButtonDown(CEGUI::RightButton);
		case Button::MIDDLE:
			_GUISystem->injectMouseButtonDown(CEGUI::MiddleButton);
		}

		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CServer::mouseReleased(const CMouseState &mouseState)
	{
		switch (mouseState.button)
		{
		case Button::LEFT:
			_GUISystem->injectMouseButtonUp(CEGUI::LeftButton);
		case Button::RIGHT:
			_GUISystem->injectMouseButtonUp(CEGUI::RightButton);
		case Button::MIDDLE:
			_GUISystem->injectMouseButtonUp(CEGUI::MiddleButton);
		}

		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	Vector2 CServer::getMouseRelPos()
	{
		return Vector2(_mouseRelPosX, _mouseRelPosY);

	} //getMouseRelPos


	Vector2 CServer::positionRelToAbs(Vector2 posRel)
	{
		float screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		float screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
		return Vector2(posRel.x * screenWidth , posRel.y * screenHeight );
	}//positionRelToAbs
} // namespace GUI
