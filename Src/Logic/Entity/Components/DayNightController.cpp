/**
@file DayNight.cpp

Contiene la implementaci�n del componente que controla el cambio del d�a a la noche

@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/

#include "DayNightController.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"
#include "Graphics/ModelFactory.h"

#include "Logic/Entity/Messages/DayNight.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic\Entity\Messages\ActivarComponente.h"

#include "BaseSubsystems/Server.h"

#include "Application/GaleonApplication.h"


namespace Logic
{
	IMP_FACTORY(CDayNightController);
	
	//---------------------------------------------------------

	bool CDayNightController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("dayTime")){
			_dayTime = entityInfo->getFloatAttribute("dayTime");
		}

		if(entityInfo->hasAttribute("dayTimeAlarm")){
			_dayTimeAlarm = entityInfo->getFloatAttribute("dayTimeAlarm");
		}

		if (entityInfo->hasAttribute("nightTime")){
			_nightTime = entityInfo->getFloatAttribute("nightTime");
		}

		if (_dayTimeAlarm > _nightTime){
			std::cout << "El tiempo de alarma tiene que ser menor al tiempo que dura la noche \n";
			//return false;
		}
		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CDayNightController::activate()
	{
		_timeType = TIME_TYPE::DAY;
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CDayNightController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CDayNightController::accept(IMessage *message)
	{
		return (!message->getType().compare("MDayNight"));
		
	} // accept
	
	//---------------------------------------------------------

	void CDayNightController::process(IMessage *message)
	{
		if (!message->getType().compare("MDayNight")){
			MDayNight *m = static_cast <MDayNight*> (message);

			if (m->getTime() == TIME_TYPE::NIGHT){
				
				MDayNight *dayNightMessage = new MDayNight();
				dayNightMessage->setTime(TIME_TYPE::NIGHT);
				//Avisar a las entidades de que se ha hecho de noche
				Logic::CServer::getSingletonPtr()->getMap()->sendMessageAll(dayNightMessage, _entity);
				
				BaseSubsystems::CServer::getSingletonPtr()->addClockListener(_nightTime - _dayTimeAlarm, this);
				_timeType = TIME_TYPE::NIGHT;

				//Cambiamos la camara
				Logic::MActivarComponente *m1 = new Logic::MActivarComponente();
				m1->setActivar(false);
				m1->setNombreComponente("CDayCameraController");
			
				Logic::MActivarComponente *m2 = new Logic::MActivarComponente();
				m2->setActivar(true);
				m2->setNombreComponente("CCameraController");
				_entity->emitMessage(m1);
				_entity->emitMessage(m2);

				Graphics::CScene* sm = Graphics::CServer::getSingletonPtr()->getActiveScene();
				sm->setAmbientLight(0.40f, 0.40f, 0.58f);

				Application::CGaleonApplication::getSingletonPtr()->setState("game");
			}
		}
	} // process
	
	//---------------------------------------------------------

	void CDayNightController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

	void CDayNightController::timeElapsed(){
		switch (_timeType){
			case TIME_TYPE::NIGHT:{

				//Avisar a las entidades de que queda poco para que se haga de d�a
				MDayNight *dayNightMessage = new MDayNight();
				dayNightMessage->setTime(TIME_TYPE::DAY_ALARM);
				Logic::CServer::getSingletonPtr()->getMap()->sendMessageAll(dayNightMessage, _entity);

				BaseSubsystems::CServer::getSingletonPtr()->addClockListener(_dayTimeAlarm, this);

				Graphics::CScene* sm = Graphics::CServer::getSingletonPtr()->getActiveScene();
				sm->setAmbientLight( 0.65f, 0.63f, 0.60f );

				_timeType = TIME_TYPE::DAY_ALARM;
				break;
			}
			case TIME_TYPE::DAY_ALARM:{

				//Avisar a las entidades de que se ha hecho de d�a
				MDayNight *dayNightMessage = new MDayNight();
				dayNightMessage->setTime(TIME_TYPE::DAY);
				Logic::CServer::getSingletonPtr()->getMap()->sendMessageAll(dayNightMessage, _entity);

				Graphics::CScene* sm = Graphics::CServer::getSingletonPtr()->getActiveScene();
				sm->setAmbientLight(0.65f, 0.65f, 0.76f);

				_timeType = TIME_TYPE::DAY;
				Application::CGaleonApplication::getSingletonPtr()->setState("day");
				
				break;
			}
		}
	}

	//---------------------------------------------------------

} // namespace Logic

