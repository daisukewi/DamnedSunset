/**
@file DayNight.cpp

Contiene la implementación del componente que controla el cambio del día a la noche

@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/

#include "DayNightController.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/ModelFactory.h"

#include "Logic/Entity/Messages/DayNight.h"
#include "Logic/Entity/Messages/Damaged.h"

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

		if (entityInfo->hasAttribute("safeLimit")){
			_safeLimit = entityInfo->getFloatAttribute("safeLimit");
		}

		if (entityInfo->hasAttribute("initPoint")){
			_initPoint = entityInfo->getFloatAttribute("initPoint");
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
		//HACK, solo para ver que funciona bien
		Graphics::CModelFactory::getSingletonPtr()->CreateCapsule(_entity->getMap()->getScene(),"","physic_debug_blue50",_safeLimit,_initPoint,0.5);
		
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

				//Avisar a las entidades de que queda poco para que se haga de día
				MDayNight *dayNightMessage = new MDayNight();
				dayNightMessage->setTime(TIME_TYPE::DAY_ALARM);
				Logic::CServer::getSingletonPtr()->getMap()->sendMessageAll(dayNightMessage, _entity);


				BaseSubsystems::CServer::getSingletonPtr()->addClockListener(_dayTimeAlarm, this);

				_timeType = TIME_TYPE::DAY_ALARM;
				break;

			}
			case TIME_TYPE::DAY_ALARM:{

				//Avisar a las entidades de que se ha hecho de día
				MDayNight *dayNightMessage = new MDayNight();
				dayNightMessage->setTime(TIME_TYPE::DAY);
				Logic::CServer::getSingletonPtr()->getMap()->sendMessageAll(dayNightMessage, _entity);

				//Hacer daño a las entidades (enemy y player) que se han quedado fuera de la cúpula
				MDamaged *damageMessage = new MDamaged();
				damageMessage->setHurt(4000);
				Logic::CMap::TEntityMap* entityMap = Logic::CServer::getSingletonPtr()->getMap()->getEntityMap();
				Logic::CMap::TEntityMap::const_iterator it, end;
				it = entityMap->begin();
				end = entityMap->end();
				damageMessage->addPtr();
				for(; it != end; it++)
				{
					std::string aux = (*it).second->getType();

					//Comprobar el tipo de entidad
					if (!aux.compare("Enemy") || !aux.compare("Player")){
					
						//Comprobar la distancia del centro a la que se encuentra
						if (_initPoint.distance((*it).second->getPosition()) > _safeLimit)
							(*it).second->emitMessage(damageMessage);
					}

				}
				damageMessage->removePtr();



				_timeType = TIME_TYPE::DAY;
				Application::CGaleonApplication::getSingletonPtr()->setState("day");
				
				break;

			}
		}
	}


	//---------------------------------------------------------

} // namespace Logic

