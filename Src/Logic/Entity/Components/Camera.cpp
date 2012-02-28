/**
@file Camera.cpp

Contiene la implementaci�n del componente que controla la c�mara gr�fica
de una escena.
 
@see Logic::CCamera
@see Logic::IComponent

@author David Llans�
@date Agosto, 2010
*/

#include "Camera.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Camera.h"

#include "BaseSubsystems/Server.h" // @TEMPORIZADOR Include de los ficheros necesarios

#include <iostream> // @TEMPORIZADOR Include para hacer pruebas. Habr� que quitarlo cuando todo funcione bien.

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

		/*
		@TEMPORIZADOR Cada vez que quiera empezar a contar aviso al reloj con el tiempo de
		temporizador (IMPORTANTE: tiempo en milisegundos) y la interfaz a la quiero que avise;
		en este caso "this".
		El reloj empezar� a contar a partir del frame siguiente a esta instrucci�n. Ahora mismo
		no creo que notemos nada raro por eso, pero est� bien que lo sep�is por si en un futuro
		ocurren cosas raras.
		*/
		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(1000, this);

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CCamera::deactivate()
	{
		_target = 0;

	} // deactivate
	
	//---------------------------------------------------------

	void CCamera::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if(_target)
		{
			// Actualizamos la posici�n de la c�mara.
			Vector3 position = _target->getPosition();
			Vector3 direction = -_distance * Math::getDirection(_target->getOrientation());
			direction.y = _height;
			_graphicsCamera->setCameraPosition(position + direction);

			// Y la posici�n hacia donde mira la c�mara.
			direction = _targetDistance * Math::getDirection(_target->getOrientation());
			direction.y = _targetHeight;
			_graphicsCamera->setTargetCameraPosition(position + direction);
		}

	} // tick

	//---------------------------------------------------------

	void CCamera::timeElapsed()
	{
		/* 
		@TEMPORIZADOR Implementaci�n del m�todo de la interfaz que va a ser llamado cuando se acabe el tiempo.
		Aunque parezca que el m�todo es as�ncrono en realidad no lo es. Est� enganchado al tick del reloj
		que se ejecuta al final de cada frame. Por lo tanto esta llamada se ejecutar� al final del frame
		en el que se termine el temporizador. Ahora mismo no creo que haya mucha diferencia pero est� bien
		que lo sep�is por si en un futuro ocurren cosas raras.
		Aqu� ir� el c�digo que quer�is que se ejecute cuando el temporizador llegue a cero.
		*/

		std::cout << "Soy la c�mara y soy avisado despu�s de un intervalo de 1 segundo. Me vuelvo a apuntar para dentro de otro segundo." << std::endl;
		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(1000, this);

	} // timeElapsed

	//---------------------------------------------------------

} // namespace Logic

