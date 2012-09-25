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

#include "ScriptManager/Server.h"

#include "assert.h"
#include "BaseSubsystems/Server.h"

//Mensajes
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/Healed.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/CureEntity.h"
#include "Logic/Entity/Messages/EntityDeathListener.h"
#include "Logic/Entity/Messages/EntityDeath.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"
#include "Logic/Entity/Messages/Aturdido.h"

#include "GUI/Server.h"
#include "GUI/InterfazController.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetAnimation.h"

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::CLife() : IComponent(), _life(100.f), _maxLife(100.0f), _death(false) {
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

		if(entityInfo->hasAttribute("lifeDamageSound"))
			_lifeDamageSound = entityInfo->getFloatAttribute("lifeDamageSound");
		if(entityInfo->hasAttribute("lifeDamageEffect"))
			_lifeDamageEffect = entityInfo->getFloatAttribute("lifeDamageEffect");
		if(entityInfo->hasAttribute("lifeCureSound"))
			_lifeCureSound = entityInfo->getStringAttribute("lifeCureSound");
		if(entityInfo->hasAttribute("lifeCureEffect"))
			_lifeCureEffect = entityInfo->getStringAttribute("lifeCureEffect");

		if(entityInfo->hasAttribute("deathFunction"))
		{
			_deathFunction = true;
			_luaDeathFunction = entityInfo->getStringAttribute("deathFunction").c_str();
		}
		else
			_deathFunction = false;

		if(entityInfo->hasAttribute("underAttackFunction"))
		{
			_underAttackFunction = true;
			_luaUnderAttackFunction = entityInfo->getStringAttribute("underAttackFunction").c_str();
		}
		else
			_underAttackFunction = false;

		
		
		//Billboard de vida
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
		float num = 0.5f - porcentajeVida/2.0f;
		_billboard->setPosicionImagen(num/*inicioX*/, 0.0f, num + 0.5f/*finX*/, 1.0f);
		

		//Billboard que indica si se tiene protección cuando es atacado
		_billboardReduceDamage = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardReduceDamageMaterial"))
			_billboardReduceDamage->setMaterial(entityInfo->getStringAttribute("billboardReduceDamageMaterial"));
		if(entityInfo->hasAttribute("billboardReduceDamageWith") && entityInfo->hasAttribute("billboardReduceDamageHeight"))
			_billboardReduceDamage->setDimensions(entityInfo->getFloatAttribute("billboardReduceDamageWith"),entityInfo->getFloatAttribute("billboardReduceDamageHeight"));
		if(entityInfo->hasAttribute("billboardReduceDamagePosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardReduceDamagePosition");
			_billboardReduceDamage->setPosition(v.x,v.y,v.z);
		}
		_billboardReduceDamage->setVisible(false);


		//Billboard que indica si está confundido
		_billboardConfusion = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardConfusionMaterial"))
			_billboardConfusion->setMaterial(entityInfo->getStringAttribute("billboardConfusionMaterial"));
		if(entityInfo->hasAttribute("billboardConfusionWith") && entityInfo->hasAttribute("billboardConfusionHeight"))
			_billboardConfusion->setDimensions(entityInfo->getFloatAttribute("billboardConfusionWith"),entityInfo->getFloatAttribute("billboardConfusionHeight"));
		if(entityInfo->hasAttribute("billboardConfusionPosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardConfusionPosition");
			_billboardConfusion->setPosition(v.x,v.y,v.z);
		}

		_billboardConfusion->setVisible(false);

		_damageModification = 1.0;
		
		// Relleno la tabla con la información del jugador.
		if (!_entity->getTag().compare("Player"))
		{
			//Crear la tabla
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		// Relleno la tabla con la información del enemigo.
		if (!_entity->getTag().compare("enemy"))
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;
	} // spawn
	
	//---------------------------------------------------------

	bool CLife::accept(IMessage *message)
	{
		return (!message->getType().compare("MDamaged")) || !message->getType().compare("MSendBillboard")
			   || !message->getType().compare("MHealed") || !message->getType().compare("MEntityDeathListener")
			   || !message->getType().compare("MAturdido");

	} // accept
	
	//---------------------------------------------------------

	void CLife::process(IMessage *message)
	{
		// Si es un mensaje de daño, se procesa y se comprueba que la entidad no ha muerto; con todo lo que ello conlleva.
		if (!message->getType().compare("MDamaged"))
		{
			MDamaged *md = static_cast <MDamaged*> (message);

			if (md->getDamageAction() == DamageMessage::DamageAction::DAMAGE)
			{
				//El mensaje de daño solo te deberia afectar si la entidad no esta muerta
				if (!_death)
				{
					if (_underAttackFunction)
					{
						std::stringstream scriptUnderAttack;
						scriptUnderAttack << _luaUnderAttackFunction << "(" << _entity->getEntityID() << ")";
						ScriptManager::CServer::getSingletonPtr()->executeScript(scriptUnderAttack.str().c_str());
					}

					
					// Disminuir la vida de la entidad 
					_life -= md->getHurt() * _damageModification;

					//Envío del mensaje al componente que se encarga de mostrar los efectos de partículas
					MParticleEffect *rc_message = new MParticleEffect();
					rc_message->setPoint(_entity->getPosition());
					rc_message->setEffect(_lifeDamageEffect);
					_entity->emitInstantMessage(rc_message,this);

					//Sonido
					MSoundEffect *m_sound = new MSoundEffect();
					m_sound->setSoundEffect(_lifeDamageSound);
					_entity->emitMessage(m_sound);

					if (_life <= 0) {
						//Muere la entidad
						_death = true;
						_life = 0;

						if (_deathFunction)
						{
							std::stringstream script;
							script << _luaDeathFunction << "(" << _entity->getEntityID() << ")";
							ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
						}

						if (!_entity->getTag().compare("enemy") || !_entity->getTag().compare("playerBuilding"))
						{
							/*MUERE UN ENEMIGO O UN EDIFICIO*/

							// @TODO @ENTITYDEATH Habrá que borrar este bloque de código cuando la notificación de la muerte de la entidad funcione bien.
							/*MAttackEntity *m = new MAttackEntity();
							m->setAttack(false);

							if (md->getKiller())
								md->getKiller()->emitMessage(m, this);*/

							// Notifico a todos mis oyentes de que la entidad ha muerto.
							notifyDeathListeners();

							/*
							Map::CEntity * muertoInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Entity");

							std::stringstream name;
							name << _entity->getEntityID();
							muertoInfo->setName(name.str());

							std::stringstream pos;
							pos << _entity->getPosition().x << ' ' << _entity->getPosition().y << ' ' << _entity->getPosition().z;
							muertoInfo->setAttribute("position", pos.str());
							muertoInfo->setAttribute("orientation", "90");
							muertoInfo->setAttribute("model", "loco.mesh");

							Logic::CEntity *muerto = Logic::CEntityFactory::getSingletonPtr()->createEntity(muertoInfo, _entity->getMap());
							*/

							
							MEntityDeath *m_death = new MEntityDeath();
							m_death->setEntityDeath(_entity);
							_entity->emitMessage(m_death);


							
							// HACK GORDO: pongo esto como arreglo provisional a la diferenciación de enemigos y edificios enemigos.
							// Cuando esté terminado el selection controller habrá que diferenciarlo aquí y allí.
							if (!_entity->getType().compare("Enemy"))
							{
								MSetAnimation *m_anim = new MSetAnimation();
								m_anim->setAnimationName("Death");
								m_anim->setLoop(false);
								_entity->emitMessage(m_anim, this);
							}

							if (!_entity->getType().compare("PanelSolar"))
							{
								std::stringstream script;
								script	<< "activarEdificiosCercanos(" << _entity->getEntityID() << ", " << "false" << ")";
								ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
							}

							//Destruimos la entidad en unos pocos milisegundos
							BaseSubsystems::CServer::getSingletonPtr()->addClockListener(1000, this);

						}
						else if (!_entity->getName().compare("Jack") || !_entity->getName().compare("Erick") || !_entity->getName().compare("Norah"))
						{
							MSetAnimation *m_anim = new MSetAnimation();
							m_anim->setAnimationName("Death");
							_entity->emitMessage(m_anim, this);


							/** MUERE UNO DE LOS 3 PERSONAJES*/
							notifyDeathListeners();

							//Los heroes no mueren realmente,
							//Desactivamos sus componentes
							MActivarComponente *m_deactComp = new MActivarComponente();
							m_deactComp->setActivar(false);
							m_deactComp->setNombreComponente("CRouteTo CAttack CLanzadorGranadas CHeal CScript CTiempoBala CSteeringMovement CDistanceAttack");
								//"CDistanceAttack CLanzadorGranadas CAttack CHeal CAnimatedGraphics CLife CBillboardSelected CPhysicCharacter CSteeringMovement CRouteTo CStateMachineExecutor CSelectable CScript CEmpujable CTiempoBala");
							_entity->emitMessage(m_deactComp, this);
						}
					}

					// Actualizamos la barra de vida
					actualizarVidaBillboard();

					// Actualizamos la barra de vida en la interfaz
					actualizarVidaInterfaz();

					// @todo Poner la animación de herido.
					// @todo Si la vida es menor que 0 poner animación de morir.
				} else {
					//Si entra aqui es que estas haciendo daño a una entidad muerta!!!

				}
			}else if (md->getDamageAction() == DamageMessage::DamageAction::SET_DAMAGE_MODIFICATION){
				_damageModification = md->getDamageModification();

				//std::cout << _entity->getName() << " SET: " << md->getDamageModification() << " "  << _damageModification << "\n";

			}else if (md->getDamageAction() == DamageMessage::DamageAction::ADD_DAMAGE_MODIFICATION)
			{
				_damageModification += md->getDamageModification(); 

				//std::cout << _entity->getName() << " ADD: " << md->getDamageModification() << " " << _damageModification << "\n";
				
			}else if (md->getDamageAction() == DamageMessage::DamageAction::RESET_DAMAGE_MODIFICATION)
			{
				_damageModification = 1.0; 
			
				//std::cout << _entity->getName() << " RESET: " << _damageModification << "\n";
			}

			if (_damageModification < 0)
					_damageModification = 0;
			if (_damageModification > 1)
				_damageModification = 1.0;

			if (_damageModification < 1.0)
				_billboardReduceDamage->setVisible(true);
			else 
				_billboardReduceDamage->setVisible(false);

		} else if (!message->getType().compare("MEntityDeathListener")) {
			// Si en un mensaje de listener se mira si hay que añadirlo o borrarlo y se hace.

			MEntityDeathListener *m = static_cast <MEntityDeathListener*> (message);

			if (m->getAdd())
				addListener(m->getListener());
			else
				removeListener(m->getListener());
			
		} else if (!message->getType().compare("MHealed"))
		{
			MHealed *mh = static_cast <MHealed*> (message);
			// Aumentar la vida de la entidad
			_life += mh->getHeal();

			// Si la entidad se ha curado del todo paramos
			if (_life >= _maxLife)
			{
				_life = _maxLife;
				MCureEntity *m = new MCureEntity();
				m->setCure(false);
				mh->getHealer()->emitMessage(m, this);
			}

			//Envío del mensaje al componente que se encarga de mostrar los efectos de partículas
			MParticleEffect *rc_message = new MParticleEffect();
			rc_message->setPoint(_entity->getPosition());
			rc_message->setEffect(_lifeCureEffect);
			_entity->emitMessage(rc_message,this);

			//Sonido
			MSoundEffect *m_sound = new MSoundEffect();
			m_sound->setSoundEffect(_lifeCureSound);
			_entity->emitMessage(m_sound);

			//Actualizamos la barra de vida
			actualizarVidaBillboard();
			actualizarVidaInterfaz();
		}else if (!message->getType().compare("MAturdido"))
		{
			MAturdido *m = static_cast <MAturdido*> (message);
			_billboardConfusion->setVisible(m->getAturdido());
		}

		// Relleno la tabla con la información del jugador.
		if (!_entity->getTag().compare("Player"))
		{
			//Crear la tabla
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		// Relleno la tabla con la información del enemigo.
		if (!_entity->getTag().compare("enemy"))
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

	} // process

	//---------------------------------------------------------

	void CLife::addListener(IDeathListener* listener)
	{
		_listeners.push_back(listener);
	
	} // addListener

	//---------------------------------------------------------

	void CLife::removeListener(IDeathListener* listener)
	{
		_listeners.remove(listener);

	} // removeListener

	//---------------------------------------------------------

	void CLife::notifyDeathListeners()
	{
		TListenersList::iterator it, end;
		it = _listeners.begin();
		end = _listeners.end();

		for (; it != end; it++)
			if ((*it) != NULL)
				(*it)->entityDeath(_entity);

		_listeners.clear();
		
	} // notifyDeathListeners

	//---------------------------------------------------------

	void CLife::timeElapsed()
	{
		//Eliminamos la entidad en el siguiente tick
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
	}

	//---------------------------------------------------------

	void CLife::actualizarVidaBillboard()
	{
		float porcentajeVida = _life/_maxLife;
		float num = 0.5f - porcentajeVida/2.0f;
		_billboard->setPosicionImagen(num/*inicioX*/, 0.0f, num + 0.5f/*finX*/, 1.0f);
	}

	//---------------------------------------------------------

	void CLife::actualizarVidaInterfaz()
	{
		if (!_entity->getName().compare("Jack"))
		{
			//Actualizamos la vida en la interfaz
			std::stringstream script;
			script << "actualizarBarraVida" << "(" << _entity->getEntityID() << ",1," << _life/_maxLife << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		if (!_entity->getName().compare("Erick"))
		{
			//Actualizamos la vida en la interfaz
			std::stringstream script;
			script << "actualizarBarraVida" << "(" << _entity->getEntityID() << ",2," << _life/_maxLife << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		if (!_entity->getName().compare("Norah"))
		{
			//Actualizamos la vida en la interfaz
			std::stringstream script;
			script << "actualizarBarraVida" << "(" << _entity->getEntityID() << ",3," << _life/_maxLife << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
	}

} // namespace Logic

