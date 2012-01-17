#include "CameraController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"


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

	bool CCameraController::accept(const TMessage &message)
	{
		return message._type == Message::CAMERA_CONTROL;

	} // accept
	
	//---------------------------------------------------------

	void CCameraController::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::CAMERA_CONTROL:
			if(!message._string.compare("up"))
				up();
			else if(!message._string.compare("down"))
				down();
			else if(!message._string.compare("left"))
				left();
			else if(!message._string.compare("right"))
				right();
			else if(!message._string.compare("stopUp"))
				stopUp();
			else if(!message._string.compare("stopDown"))
				stopDown();
			else if(!message._string.compare("stopLeft"))
				stopLeft();
			else if(!message._string.compare("stopRight"))
				stopRight();
		}

	} // process
	
	//---------------------------------------------------------

	void CCameraController::up()
	{
		_up = true;

	} // up

	//---------------------------------------------------------

	void CCameraController::down()
	{
		_down = true;

	} // down

	//---------------------------------------------------------

	void CCameraController::left()
	{
		_left = true;

	} // left

	//---------------------------------------------------------

	void CCameraController::right()
	{
		_right = true;

	} // right

	//---------------------------------------------------------

	void CCameraController::stopUp()
	{
		_up = false;

	} // stopUp

	//---------------------------------------------------------

	void CCameraController::stopDown()
	{
		_down = false;

	} // stopDown

	//---------------------------------------------------------

	void CCameraController::stopLeft()
	{
		_left = false;

	} // stopLeft

	//---------------------------------------------------------

	void CCameraController::stopRight()
	{
		_right = false;

	} // stopRight

	//---------------------------------------------------------

	void CCameraController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Si nos estamos desplazando calculamos la próxima posición
		// Calculamos si hay vectores de dirección de avance y strafe,
		// hayamos la dirección de la suma y escalamos según la
		// velocidad y el tiempo transcurrido.
		if(_up || _down || _left || _right)
		{
			Vector3 direction(Vector3::ZERO);
			Vector3 directionStrafe(Vector3::ZERO);

			if(_up || _down)
			{
				direction = Math::getDirection(_entity->getYaw());
				if(_down)
					direction *= -1;
			}

			if(_left || _right)
			{
				directionStrafe = 
						Math::getDirection(_entity->getYaw() + Math::PI/2);
				if(_right)
					directionStrafe *= -1;
			}

			direction += directionStrafe;
			direction.normalise();
			direction *= msecs * _speed;

			_entity->setPosition(_entity->getPosition() + direction);

		}

	} // tick

} // namespace Logic

