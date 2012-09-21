/**
@file DispararPotente.cpp

Contiene la implementación del componente que controla la habilidad disparos potentes, que consiste
en quitar vida a las entidades contenidas en el sector circular del que lanza los disparos.

@see Logic::CDispararPotente
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/

#include "DispararPotente.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Entity/Messages/DisparosPotentes.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

namespace Logic 
{
	IMP_FACTORY(CDispararPotente);
	
	//---------------------------------------------------------

	CDispararPotente::CDispararPotente() : IComponent() {

	}

	CDispararPotente::~CDispararPotente() {
		if (_billboard)
			delete _billboard;
	}

	bool CDispararPotente::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		// Billboard que señala el alcance del disparo
		_billboard = new Graphics::CBillboard(entity);
		if(entityInfo->hasAttribute("billboardDisparoMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardDisparoMaterial"));
		if(entityInfo->hasAttribute("billboardDisparoWith") && entityInfo->hasAttribute("billboardDisparoHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardDisparoWith"),entityInfo->getFloatAttribute("billboardDisparoHeight"));
		_billboard->setPerpendicular();
		_billboard->setVisible(false);

		if(entityInfo->hasAttribute("angleDisparoPotente"))
			_angleAction = entityInfo->getFloatAttribute("angleDisparoPotente");
		if(entityInfo->hasAttribute("radioDisparoPotente"))
			_radioAction = entityInfo->getFloatAttribute("radioDisparoPotente");
		if(entityInfo->hasAttribute("damageDisparoPotente"))
			_damagePowerShoot = entityInfo->getFloatAttribute("damageDisparoPotente");

		return true;
	} // spawn


	bool CDispararPotente::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	void CDispararPotente::deactivate()
	{	

	} // deactivate
	//---------------------------------------------------------

	bool CDispararPotente::accept(IMessage *message)
	{
		return !message->getType().compare("MDisparosPotentes");
	} // accept
	
	//---------------------------------------------------------

	void CDispararPotente::process(IMessage *message)
	{
		if (!message->getType().compare("MDisparosPotentes"))
		{
			MDisparosPotentes *m_disp = static_cast <MDisparosPotentes*> (message);

			if (m_disp->getOrdenDisparos() == mostrarCono)
			{
				_billboard->setVisible(true);
			} 
			else if (m_disp->getOrdenDisparos() == ocultarCono)
			{
				_billboard->setVisible(false);
			}
			else if (m_disp->getOrdenDisparos() == disparar)
			{
				// DISPARAMOS LA RÁFAGA DE BALAS

				// Ocultamos el billboard
				_billboard->setVisible(false);

				// Posicion destino solo con X, Y.
				Vector2 posDestino = *m_disp->getPosition();
				// Posicion destino con X, Y, Z.
				Vector3 posDestino3 = Vector3(posDestino.x,4,posDestino.y);

				// Calculamos el vector de direccion al que apunta el ratón
				Vector3 v = Vector3(posDestino3.x - _entity->getPosition().x, 0, posDestino3.z - _entity->getPosition().z);
				v.normalise();

				Logic::CEntity* * entidadesColision;
				int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(),
					_radioAction, entidadesColision);

				// Envío del mensaje al componente que se encarga de mostrar los efectos de partículas
				MParticleEffect *rc_message = new MParticleEffect();
				rc_message->setPoint(_entity->getPosition());
				rc_message->setEffect("Explosion");
				_entity->emitInstantMessage(rc_message,this);

				// Envío del mensaje al componente que se encarga de reproducir los sonidos
				MSoundEffect *rc2_message = new MSoundEffect();
				rc2_message->setSoundEffect("media/sounds/empuje.mp3");
				_entity->emitInstantMessage(rc2_message,this);

				for(int i = 0; i < numColisiones; ++i)
				{
					// Entidad que se encuentra dentro del círculo de acción
					CEntity * entidad = entidadesColision[i];
					
					if (!(entidad->getTag() == "Player"))
					{
						Vector3 targ = entidad->getPosition() - _entity->getPosition();

						// Si está en el sector circular seleccionado se daña a la entidad
						if ((v.angleBetween(targ)).valueDegrees() < _angleAction/2.0f && _entity->getEntityID() != entidad->getEntityID())
						{
							// Enviamos mensaje de daño a la entidad
							MDamaged *mDamaged = new MDamaged();
							mDamaged->setHurt(_damagePowerShoot);
							mDamaged->setKiller(0);
							entidad->emitMessage(mDamaged, this);
						}
					}
				}
				
			}
		}

	} // process

} // namespace Logic