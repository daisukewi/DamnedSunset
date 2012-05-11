/**
@file CameraController.cpp

Contiene la implementación del componente que controla el movimiento de la cámara por la escena.

@see Logic::IComponent

@author Alberto Plaza
@date Enero, 2012
*/

#include "CameraController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics.h"
#include "Graphics/Scene.h"
#include "Graphics/Camera.h"

#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

#include "Logic/Entity/Messages/UbicarCamara.h"
#include "Logic/Entity/Messages/CameraControl.h"

#include "Sound/Server.h"

namespace Logic 
{
	IMP_FACTORY(CCameraController);
	
	//---------------------------------------------------------

	bool CCameraController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;


		if(entityInfo->hasAttribute("mouseDistance"))
			_mouseDistance = entityInfo->getIntAttribute("mouseDistance");

		if(entityInfo->hasAttribute("cameraDistance"))
			_cameraDistance = entityInfo->getIntAttribute("cameraDistance");

		if(entityInfo->hasAttribute("cameraVelocity"))
			_cameraVelocity = entityInfo->getIntAttribute("cameraVelocity");

		if(entityInfo->hasAttribute("zoomVelocity"))
			_zoomVelocity = entityInfo->getIntAttribute("zoomVelocity");

		_bossEntity = NULL;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CCameraController::activate()
	{
		_bossEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack");
		_bossPosition = _bossEntity->getPosition();
		_finalPosition = _bossEntity->getPosition();
		_graphicsCamera = _entity->getMap()->getScene()->getCamera();
		_entity->setPosition(_finalPosition);
		_movement = Vector3::ZERO;
		_cameraHeight = 0.0;
		_scroll = false;
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CCameraController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CCameraController::accept(IMessage *message)
	{
		return (!message->getType().compare("MCameraControl") || !message->getType().compare("MUbicarCamara"));

	} // accept
	
	//---------------------------------------------------------

	void CCameraController::process(IMessage *message)
	{
		if (!message->getType().compare("MCameraControl"))
		{
			MCameraControl *m = static_cast <MCameraControl*> (message);
			_mouse = m->getMouse();

			if(!m->getMovement().compare("up"))
				up();
			else if(!m->getMovement().compare("down"))
				down();
			else if(!m->getMovement().compare("left"))
				left();
			else if(!m->getMovement().compare("right"))
				right();
			else if(!m->getMovement().compare("stopUpDown"))
				stopUpDown();
			else if(!m->getMovement().compare("stopLeftRight"))
				stopLeftRight();
			if(m->getScroll()!=0){
				//zoom(m->getScroll());
				_scrollValue = m->getScroll();
				_scroll = true;
			}
		}
		else if (!message->getType().compare("MUbicarCamara"))
		{
			MUbicarCamara *m = static_cast <MUbicarCamara*> (message);

			_bossEntity = m->getEntity();
			_finalPosition = _bossEntity->getPosition();
			
		}

	} // process

	//---------------------------------------------------------

	void CCameraController::up()
	{
		if (_mouse)
			_upMouse = true;
		else
			_up = true;

		_mouse = false;

	} // up

	//---------------------------------------------------------

	void CCameraController::down()
	{
		if (_mouse)
			_downMouse = true;
		else
			_down = true;

		_mouse = false;

	} // down

	//---------------------------------------------------------

	void CCameraController::left()
	{
		if (_mouse)
			_leftMouse = true;
		else
			_left = true;

		_mouse = false;

	} // left

	//---------------------------------------------------------

	void CCameraController::right()
	{
		if (_mouse)
			_rightMouse = true;
		else
			_right = true;

		_mouse = false;

	} // right

	//---------------------------------------------------------

	void CCameraController::stopUpDown()
	{
		if (_mouse)
			_upMouse = _downMouse = false;
		else
			_up = _down = false;

		_mouse = false;

	} // stopUpDown

	//---------------------------------------------------------

	void CCameraController::stopLeftRight()
	{
		if (_mouse)
			_leftMouse = _rightMouse = false;
		else
			_left = _right = false;

		_mouse = false;

	} // stopLeft

	//---------------------------------------------------------

	void CCameraController::zoom(int wheel)
	{
	/*	Vector3 direction = _bossEntity->getPosition() - _entity->getPosition();
		direction.y = 0.0f;

		if (wheel > 0 && _entity->getPosition().y > -35)
		{
			_entity->setPosition(_entity->getPosition() + 0.50 * Vector3(0, _entity->getPosition().y - 35, 0));
			_entity->setPosition(_entity->getPosition() + 0.25 * direction);
		}
		else if (wheel < 0 && direction.length() < 30)
		{
			_entity->setPosition(_entity->getPosition() - 0.50 * Vector3(0, _entity->getPosition().y - 35, 0));
			_entity->setPosition(_entity->getPosition() - 0.25 * direction);
		}
		*/
		
	} // zoom

	//---------------------------------------------------------

	void CCameraController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_bossEntity != NULL)
		{

			Vector3 bossPositionAct  = _bossEntity->getPosition();
			Vector3 cuerda = bossPositionAct - _bossPosition;
			
			if (_up || _upMouse){
				_movement.z = _mouseDistance;
				_movement.x = _mouseDistance;
			}else if(_down || _downMouse){
				_movement.z = -_mouseDistance;
				_movement.x = -_mouseDistance;
			}else{
				_movement.z = 0;
				_movement.x = 0;
			}
			if (_left || _leftMouse){
				_movement.x = _mouseDistance;
				_movement.z = -_mouseDistance;
			}else if(_right || _rightMouse){
				_movement.x = -_mouseDistance;
				_movement.z = _mouseDistance;
			}
			
			cuerda.normalise();

			if (_bossPosition == bossPositionAct){
				cuerda.z = 0;
				cuerda.x = 0;
			}else{
				cuerda.x *= _cameraDistance;
				cuerda.z *= _cameraDistance;
			}

			_bossPosition = bossPositionAct;

			//Posición a la que tiene que llegar a mirar la cámara
			_finalPosition = _bossPosition + cuerda + _movement;

			float aux = msecs / _cameraVelocity ;
			Vector3 pos = Math::Lerp( _entity->getPosition(),_finalPosition,  aux);
			
			_entity->setPosition(pos);
		
			//Posicionar el listener de los sonidos
			Sounds::CServer::getSingletonPtr()->setListenerPos(Vector3(_entity->getPosition().x,_entity->getPosition().y,_entity->getPosition().z));

		}

		if (_scroll){
		
			
			if (_scrollValue > 0)
			{
				Vector3 position = _entity->getPosition();
				Vector3 direction = -40 * Math::getDirection(_entity->getOrientation());
				direction.y = 40;
				_graphicsCamera->setTargetCameraPosition(position + direction);
			}
			else if (_scrollValue < 0 )
			{
				_graphicsCamera->setCameraPosition(Vector3(100,100,100));
			}
			/*// Actualizamos la posición de la cámara.

			float aux = msecs / _zoomVelocity ;
			Vector3 pos = Math::Lerp( _graphicsCamera->getCameraPosition(),_finalPosition,  aux);
			
			_entity->setPosition(pos);
	*/
			_scroll = false;
			//Posicionar el listener de los sonidos
			Sounds::CServer::getSingletonPtr()->setListenerPos(Vector3(_entity->getPosition().x,_entity->getPosition().y,_entity->getPosition().z));
		}	
	} // tick

} // namespace Logic

