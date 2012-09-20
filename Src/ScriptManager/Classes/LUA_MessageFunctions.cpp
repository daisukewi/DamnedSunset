/**
@file LUA_MessageFunctions.cpp

LUA

@author Daniel Flamenco
@date Mayo, 2012
*/

#include <cassert>

#include "BaseSubsystems/Math.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"

#include "Logic/Entity/Messages/EmplaceBuilding.h"
#include "Logic/Entity/Messages/LanzarGranada.h"
#include "Logic/Entity/Messages/PushEntities.h"
#include "Logic/Entity/Messages/DisparosPotentes.h"
#include "Logic/Entity/Messages/LanzarLlamas.h"
#include "Logic/Entity/Messages/CureEntity.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/ActivateReduceDamage.h"
#include "Logic/Entity/Messages/ActivateHealZone.h"
#include "Logic/Entity/Messages/ActivarTiempoBala.h"
#include "Logic/Entity/Messages/Aturdido.h"
#include "Logic/Entity/Messages/Healed.h"


#include "Logic/Server.h"

#include "Physics/Server.h"

#include "ScriptManager/Server.h"

namespace ScriptManager
{

	void startBuild(std::string building)
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::START_BUILDING);
		build->setBuildingType(building);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	//---------------------------------------------------------

	void cancelBuild()
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::CANCEL_BUILDING);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	//---------------------------------------------------------

	void emplaceBuild()
	{
		Logic::MEmplaceBuilding* build = new Logic::MEmplaceBuilding();
		build->setAction(Logic::BuildingAction::EMPLACE_BUILDING);
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(build);
	}

	//---------------------------------------------------------

	void startGrenade(unsigned int entityID, float point_x, float point_y, float point_z)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarGranada *m = new Logic::MLanzarGranada();
		//m->setPosition(Vector2(entity->getPosition().x, entity->getPosition().y));
		m->setPosition(Vector2(point_x, point_y));
		m->setOrdenGranada(Logic::OrdenGranada::mostrar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void cancelGrenade(unsigned int entityID, float point_x, float point_y, float point_z)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarGranada *m = new Logic::MLanzarGranada();
		//m->setPosition(Vector2(entity->getPosition().x, entity->getPosition().y));
		m->setPosition(Vector2(point_x, point_y));
		m->setOrdenGranada(Logic::OrdenGranada::ocultar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void launchGrenade(unsigned int entityID, float point_x, float point_y, float point_z)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarGranada *m = new Logic::MLanzarGranada();
		//m->setPosition(Vector2(entity->getPosition().x, entity->getPosition().y));
		m->setPosition(Vector2(point_x, point_z));
		m->setOrdenGranada(Logic::OrdenGranada::lanzar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void empujarCircle(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MPushEntities *m = new Logic::MPushEntities();

		entity->emitMessage(m);
	}

		//---------------------------------------------------------

	void enemigosContraEnemigos(unsigned int entityID)
	{
		Logic::CEntity * norah = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::CEntity* * entidadesColision;
		int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions( norah->getPosition(),80,entidadesColision);

		//Iniciamos la tabla de los enemigos afectados
		std::stringstream script1;
		script1 << "enemigosConfundidos = {}";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script1.str().c_str());


		for(int i = 0; i < numColisiones; ++i)
		{
			if ( !entidadesColision[i]->getTag().compare("enemy") ) {
				//Entidad enemiga que atacara a otros enemigos
				Logic::CEntity * entidad = entidadesColision[i];

				float distX = entidad->getPosition().x - norah->getPosition().x;
				float distZ = entidad->getPosition().z - norah->getPosition().z;
				float distance2 = distX * distX + distZ * distZ;

				//Solo entraran al estado los que esten a una distancia menor de 40
				if (distance2 < 40 * 40) {
					std::stringstream script2;
					script2 << "enemyEvent(\"AttackOtherEnemies\", " << entidad->getEntityID() << ")";
					ScriptManager::CServer::getSingletonPtr()->executeScript(script2.str().c_str());

					//Mandamos un mensaje para que salga el icono de aturdido
					Logic::MAturdido *message = new Logic::MAturdido();
					message->setAturdido(true);
					entidad->emitMessage(message);
				}

				//Atacaran hasta a los que esten a una distancia de 80

				//Añadimos el enemigo a la tabla de los enemigos afectados entre los que se pueden atacar
				std::stringstream script3;
				script3 << "enemigosConfundidos[" << i+1 << "] = " << entidad->getEntityID();
				ScriptManager::CServer::getSingletonPtr()->executeScript(script3.str().c_str());
			}
		}
	}

	void detenerEnemigosContraEnemigos(unsigned int entityID)
	{
		//Mandamos un mensaje para que salga el icono de aturdido
		Logic::MAturdido *message = new Logic::MAturdido();
		message->setAturdido(false);
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		if (entity)
			entity->emitMessage(message);
	}
	//---------------------------------------------------------

	void atacarJack(unsigned int entityID)
	{
		Logic::CEntity * jack = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::CEntity* * entidadesColision;
		int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(jack->getPosition(), 40, entidadesColision);

		for(int i = 0; i < numColisiones; ++i)
		{
			if (!entidadesColision[i]->getTag().compare("enemy")) 
			{
				//Entidad enemiga que atacará a Jack
				Logic::CEntity * entidad = entidadesColision[i];

				std::stringstream script;
				script << "enemyEvent(\"AttackJack\", " << entidad->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

				Logic::MAttackEntity *message = new Logic::MAttackEntity();
				message->setAttack(true);
				message->setEntity(jack);
				entidad->emitMessage(message);
			}
		}
	}

	//---------------------------------------------------------

	void activateBulletTime(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MActivarTiempoBala *m = new Logic::MActivarTiempoBala();
		m->setTime(5.0f);
		unsigned int norah = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Norah")->getEntityID();
		unsigned int jack = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack")->getEntityID();
		unsigned int erick = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick")->getEntityID();
		m->addEntity(norah);
		m->addEntity(jack);
		m->addEntity(erick);
		
		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void startPowerShoot(unsigned int entityID, float point_x, float point_y, float point_z)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MDisparosPotentes *m = new Logic::MDisparosPotentes();
		m->setPosition(Vector2(point_x, point_z));
		m->setOrdenDisparos(Logic::OrdenDisparos::mostrarCono);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void cancelPowerShoot(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MDisparosPotentes *m = new Logic::MDisparosPotentes();
		m->setPosition(Vector2(0, 0));
		m->setOrdenDisparos(Logic::OrdenDisparos::ocultarCono);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void launchPowerShoot(unsigned int entityID, float point_x, float point_y, float point_z)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MDisparosPotentes *m = new Logic::MDisparosPotentes();
		m->setPosition(Vector2(point_x, point_z));
		m->setOrdenDisparos(Logic::OrdenDisparos::disparar);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void startFlameThrower(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarLlamas *m = new Logic::MLanzarLlamas();
		m->setPosition(Vector2(0, 0));
		m->setOrdenLlamas(Logic::OrdenLlamas::mostrarBLlamas);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void cancelFlameThrower(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarLlamas *m = new Logic::MLanzarLlamas();
		m->setPosition(Vector2(0, 0));
		m->setOrdenLlamas(Logic::OrdenLlamas::ocultarBLamas);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void launchFlameThrower(unsigned int entityID, float point_x, float point_y, float point_z)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MLanzarLlamas *m = new Logic::MLanzarLlamas();
		m->setPosition(Vector2(point_x, point_z));
		m->setOrdenLlamas(Logic::OrdenLlamas::lanzarLlamas);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------
	
	void activateReduceDamage(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MActivateReduceDamage *m = new Logic::MActivateReduceDamage();
		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void activateHealZone(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		Logic::MActivateHealZone *m = new Logic::MActivateHealZone();
		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void activateMassHeal(unsigned int entityID, float heal)
	{
		Logic::CEntity *healer = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);

		/*Logic::CEntity *jackEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack");
		Logic::CEntity *erickEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick");
		Logic::CEntity *norahEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Norah");

		Logic::MHealed *m_heal = new Logic::MHealed();
		m_heal->setHeal(heal);
		m_heal->setHealer(healer);*/

		Logic::CEntity *playerEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByTag("Player");
		while (playerEntity != NULL) {
			Logic::MHealed *m_heal = new Logic::MHealed();
			m_heal->setHeal(heal);
			m_heal->setHealer(healer);
			playerEntity->emitMessage(m_heal);

			playerEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByTag("Player", playerEntity);
		}
	}

	//---------------------------------------------------------

	void startCure(unsigned int entityID, unsigned int entityIDTarget)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		Logic::CEntity *entityTarget = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityIDTarget);

		Logic::MCureEntity *m = new Logic::MCureEntity();
		m->setEntity(entityTarget);
		m->setCure(true);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

	void cancelCure(unsigned int entityID)
	{
		Logic::CEntity *entity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(entityID);
		
		Logic::MCureEntity *m = new Logic::MCureEntity();
		m->setCure(false);

		entity->emitMessage(m);
	}

	//---------------------------------------------------------

} // namespace ScriptManager