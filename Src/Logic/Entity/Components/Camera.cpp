/**
@file Camera.cpp

Contiene la implementación del componente que controla la cámara gráfica
de una escena.
 
@see Logic::CCamera
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "Camera.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Logic/Entity/Messages/UbicarCamara.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Camera.h"

namespace Logic 
{
	IMP_FACTORY(CCamera);
	
	//---------------------------------------------------------

	bool CCamera::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_graphicsCamera = _entity->getMap()->getScene()->getCamera();
		if(!_graphicsCamera)
			return false;

		if(entityInfo->hasAttribute("distance"))
			_distance = entityInfo->getFloatAttribute("distance");

		if(entityInfo->hasAttribute("height"))
			_height = entityInfo->getFloatAttribute("height");

		if(entityInfo->hasAttribute("targetName"))
			_targetName = entityInfo->getStringAttribute("targetName");

		if(entityInfo->hasAttribute("targetDistance"))
			_targetDistance = entityInfo->getFloatAttribute("targetDistance");

		if(entityInfo->hasAttribute("targetHeight"))
			_targetHeight = entityInfo->getFloatAttribute("targetHeight");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CCamera::activate()
	{
		//_target = CServer::getSingletonPtr()->getPlayer();
		_target = CServer::getSingletonPtr()->getMap()->getEntityByName(_targetName);

		//Almacenar la posición inicial de la cámara
		Vector3 position = _target->getPosition();
		Vector3 direction = -_distance * Math::getDirection(_target->getOrientation());
		direction.y = _height;

		_finalDirection.z = direction.z;
		_finalDirection.x = direction.x;
		_finalDirection.y  = direction.y;

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CCamera::deactivate()
	{
		_target = 0;

	} // deactivate
	
	//---------------------------------------------------------
	bool CCamera::accept(IMessage *message){
		return (!message->getType().compare("MUbicarCamara"));
	}
	//---------------------------------------------------------

	void CCamera::process(IMessage *message){
		if (!message->getType().compare("MUbicarCamara")){
			MUbicarCamara *m = static_cast <MUbicarCamara*> (message);
			_finalCameraHeight = m->getHeight() + _height;
			if (_finalCameraHeight < 150){
				_finalCameraHeight = 150;
			}else if (_finalCameraHeight > 300){
				_finalCameraHeight = 300;
			}
			_finalDirection.y = _finalCameraHeight;
		}
	}
	//---------------------------------------------------------
	void CCamera::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if(_target)
		{
			float aux = (float)msecs/100.0;
			// Actualizamos la posición de la cámara.
			Vector3 position = _target->getPosition();
			Vector3 direction = -_distance * Math::getDirection(_target->getOrientation());
			direction.y = _height;

			Vector3 dir = Math::Lerp( direction,_finalDirection,  aux);
			_height = dir.y;
			_graphicsCamera->setCameraPosition(position + dir);

			// Y la posición hacia donde mira la cámara.
			direction = _targetDistance * Math::getDirection(_target->getOrientation());
			direction.y = _targetHeight;
			_graphicsCamera->setTargetCameraPosition(position + direction);
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

