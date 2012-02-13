/**
@file Life.cpp

Contiene la implementación del componente que controla la vida de una entidad.
 
@see Logic::CLife
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/

#include "Life.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Application/BaseApplication.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/Billboard.h"
#include "Graphics.h"
#include "Graphics/AnimatedEntity.h"

#include "assert.h"

//Mensajes
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackEntity.h"

#include "GUI/Server.h"
#include "GUI/InterfazController.h"

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::CLife() : IComponent(), _life(100.f), _maxLife(100.0f) {
	}

	CLife::~CLife() {
		if (_billboard)
			delete _billboard;
	}

	bool CLife::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("life"))
			_life = entityInfo->getFloatAttribute("life");
		if(entityInfo->hasAttribute("maxLife"))
			_maxLife = entityInfo->getFloatAttribute("maxLife");
		
		//Billboard
		_billboard = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardLifeMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardLifeMaterial"));
		if(entityInfo->hasAttribute("billboardLifeWith") && entityInfo->hasAttribute("billboardLifeHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardLifeWith"),entityInfo->getFloatAttribute("billboardLifeHeight"));
		if(entityInfo->hasAttribute("billboardLifePosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardLifePosition");
			_billboard->setPosition(v.x,v.y,v.z);
		}	
		float porcentajeVida = _life/_maxLife;
		_billboard->setPosicionImagen((1.0f-porcentajeVida*1.0)/2.0f/*inicioX*/, 0.0f, 0.5f+(1.0f-porcentajeVida*0.5f)/2.0f/*finX*/, 1.0f);
		return true;
	} // spawn
	
	//---------------------------------------------------------

	bool CLife::accept(IMessage *message)
	{
		return (message->getType().compare("MDamaged") == 0) || !message->getType().compare("MSendBillboard");

	} // accept
	
	//---------------------------------------------------------

	void CLife::process(IMessage *message)
	{
		if (!message->getType().compare("MDamaged"))
		{
				MDamaged *md = static_cast <MDamaged*> (message);
				// Disminuir la vida de la entidad
				_life -= md->getHurt();
				
				if (_life <= 0) {
					_life = 0;
					// Si han matado al jugador salir de la partida
					if (_entity->isPlayer())
						Application::CBaseApplication::getSingletonPtr()->setState("gameOver");
					// Si han matado al enemigo matarlo
					else if (!_entity->getType().compare("Enemy"))
					{
						MAttackEntity *m = new MAttackEntity();
						m->setAttack(false);
						md->getKiller()->emitMessage(m, this);

						/*
						Graphics::CStaticEntity *muerto = new Graphics::CEntity(
						muerto->setPosition(_entity->getPosition());
						muerto->setVisible(true);
						Graphics::CScene::addStaticEntity
						*/
					
						Map::CEntity * muertoInfo = Map::CMapParser::getSingletonPtr()->getEntitieInfo("Entity");
						muertoInfo->setName("EnemyDeath");
						
						char* cordX = new char[10];
						sprintf(cordX, "%f", _entity->getPosition().x);
						char* cordY = new char[10];
						sprintf(cordY, "%f", _entity->getPosition().y);
						char* cordZ = new char[10];
						sprintf(cordZ, "%f", _entity->getPosition().z);
						std::stringstream ss;
						ss << '{' << cordX << ',' << ' ' << cordY << ',' << ' ' << cordZ << '}';
						std::cout << ss.str() << '\n';
						std::cout << _entity->getPosition() << '\n';
						muertoInfo->setAttribute("position", ss.str());
						muertoInfo->setAttribute("orientation", "90");
						muertoInfo->setAttribute("model", "loco.mesh");

						Logic::CEntity *muerto = Logic::CEntityFactory::getSingletonPtr()->createEntity(muertoInfo, _entity->getMap());
						std::cout << muerto->getPosition() << '\n';

						CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
					}
				}
				// @todo Poner la animación de herido.
				// @todo Si la vida es menor que 0 poner animación de morir.

				float porcentajeVida = _life/_maxLife;
				_billboard->setPosicionImagen((1.0f-porcentajeVida*1.0)/2.0f/*inicioX*/, 0.0f, 0.5f+(1.0f-porcentajeVida*0.5f)/2.0f/*finX*/, 1.0f);

				if (!_entity->getName().compare("Jack"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('1',_life/_maxLife);
				}
				if (!_entity->getName().compare("Erick"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('2',_life/_maxLife);
				}
				if (!_entity->getName().compare("Amor"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('3',_life/_maxLife);
				}

				// Si la entidad se ha curado paramos
				if (_life >= _maxLife)
				{
					_life = _maxLife;
					MAttackEntity *m = new MAttackEntity();
					m->setAttack(false);
					md->getKiller()->emitMessage(m, this);
				}
		}
	} // process
} // namespace Logic

