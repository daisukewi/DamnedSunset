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

#include "Logic/Entity/Messages/UbicarCamara.h"
#include "Logic/Entity/Messages/CameraControl.h"

namespace Logic 
{
	IMP_FACTORY(CCameraController);
	
	//---------------------------------------------------------

	bool CCameraController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CCameraController::activate()
	{
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
		}
		else if (!message->getType().compare("MUbicarCamara"))
		{
			MUbicarCamara *m = static_cast <MUbicarCamara*> (message);

			_entity->setPosition(m->getPosition());
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

	void CCameraController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Si nos estamos desplazando calculamos la próxima posición
		// Calculamos si hay vectores de dirección de avance y strafe,
		// hayamos la dirección de la suma y escalamos según la
		// velocidad y el tiempo transcurrido.
		if(_up || _down || _left || _right || _upMouse || _downMouse || _leftMouse || _rightMouse)
		{
			Vector3 direction(Vector3::ZERO);
			Vector3 directionStrafe(Vector3::ZERO);

			if(_up || _down || _upMouse || _downMouse)
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

	} // tick

} // namespace Logic

