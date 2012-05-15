/**
@file DayCameraController.cpp

Contiene la implementación del componente que controla el movimiento de la cámara por la escena en la fase de día

@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/

#include "DayCameraController.h"

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
	IMP_FACTORY(CDayCameraController);
	
	//---------------------------------------------------------

	bool CDayCameraController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;


		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getIntAttribute("speed");


		_bossEntity = NULL;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CDayCameraController::activate()
	{

		_graphicsCamera = _entity->getMap()->getScene()->getCamera();
		_cameraHeight = 0.0;
		_scroll = false;
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CDayCameraController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CDayCameraController::accept(IMessage *message)
	{
		return (!message->getType().compare("MCameraControl") || !message->getType().compare("MUbicarCamara"));

	} // accept
	
	//---------------------------------------------------------

	void CDayCameraController::process(IMessage *message)
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

	void CDayCameraController::up()
	{
		if (_mouse)
			_upMouse = true;
		else
			_up = true;

		_mouse = false;

	} // up

	//---------------------------------------------------------

	void CDayCameraController::down()
	{
		if (_mouse)
			_downMouse = true;
		else
			_down = true;

		_mouse = false;

	} // down

	//---------------------------------------------------------

	void CDayCameraController::left()
	{
		if (_mouse)
			_leftMouse = true;
		else
			_left = true;

		_mouse = false;

	} // left

	//---------------------------------------------------------

	void CDayCameraController::right()
	{
		if (_mouse)
			_rightMouse = true;
		else
			_right = true;

		_mouse = false;

	} // right

	//---------------------------------------------------------

	void CDayCameraController::stopUpDown()
	{
		if (_mouse)
			_upMouse = _downMouse = false;
		else
			_up = _down = false;

		_mouse = false;

	} // stopUpDown

	//---------------------------------------------------------

	void CDayCameraController::stopLeftRight()
	{
		if (_mouse)
			_leftMouse = _rightMouse = false;
		else
			_left = _right = false;

		_mouse = false;

	} // stopLeft

	//---------------------------------------------------------

	void CDayCameraController::zoom(int wheel)
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

	void CDayCameraController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if(_up || _down || _left || _right || _upMouse || _downMouse || _leftMouse || _rightMouse)
		{
			Vector3 direction(Vector3::ZERO);
			Vector3 directionStrafe(Vector3::ZERO);

			if(_up || _down || _upMouse || _downMouse )
			{
				direction = Math::getDirection(_entity->getYaw());
				if(_down || _downMouse)
					direction *= -1;
			}

			if(_left || _right || _leftMouse || _rightMouse)
			{
				directionStrafe = 
						Math::getDirection(_entity->getYaw() + Math::PI/2);
				if(_right || _rightMouse)
					directionStrafe *= -1;
			}

			direction += directionStrafe;
			direction.normalise();
			direction *= msecs * _speed;
			
			_entity->setPosition(_entity->getPosition() + direction);

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

