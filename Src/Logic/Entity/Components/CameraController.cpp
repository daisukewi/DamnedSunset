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

#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

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

		_bossEntity = NULL;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CCameraController::activate()
	{
		_bossEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack");

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

			_bossEntity = m->getEntity();

			_entity->setPosition(_bossEntity->getPosition());
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

		// Si nos estamos desplazando y tenemos a la vista nuestra entidad
		// de referencia calculamos la próxima posición
		// Calculamos si hay vectores de dirección de avance y strafe,
		// hayamos la dirección de la suma y escalamos según la
		// velocidad y el tiempo transcurrido.
		Vector3 direction(Vector3::ZERO);
		Vector3 directionStrafe(Vector3::ZERO);
		bool south, north, east, west;

		if (_bossEntity != NULL)
		{
			Vector3 cuerda = _entity->getPosition() - _bossEntity->getPosition();
			direction = Math::getDirection(_entity->getYaw());
			directionStrafe = Math::getDirection(_entity->getYaw() + Math::PI/2);

			_up &= Math::Proy(cuerda, direction) <= 15;
			_down &= Math::Proy(cuerda, direction * (-1)) <= 20;
			_right &= Math::Proy(cuerda, directionStrafe * (-1)) <= 15;
			_left &= Math::Proy(cuerda, directionStrafe) <= 15;
			_upMouse &= Math::Proy(cuerda, direction) <= 15;
			_downMouse &= Math::Proy(cuerda, direction * (-1)) <= 20;
			_rightMouse &= Math::Proy(cuerda, directionStrafe * (-1)) <= 15;
			_leftMouse &= Math::Proy(cuerda, directionStrafe) <= 15;

			south = Math::Proy(cuerda, direction) > 17;
			north = Math::Proy(cuerda, direction * (-1)) > 22;
			east = Math::Proy(cuerda, directionStrafe) > 17;
			west = Math::Proy(cuerda, directionStrafe * (-1)) > 17;

		}

		if(_up || _down || _left || _right || _upMouse || _downMouse || _leftMouse || _rightMouse 
			|| north || south || east || west)
		{
			if (!(_up || _down || _upMouse || _downMouse || north || south))
				direction = Vector3::ZERO;
			else if(_down || _downMouse || south)
				direction *= -1;

			if (!(_left || _right || _leftMouse || _rightMouse || east || west))
				directionStrafe = Vector3::ZERO;
			else if(_right || _rightMouse || east)
				directionStrafe *= -1;

			direction += directionStrafe;
			direction.normalise();
			direction *= msecs * _speed;

			_entity->setPosition(_entity->getPosition() + direction);

		}

	} // tick

} // namespace Logic

