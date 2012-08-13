/**
@file LanzadorLlamas.cpp

Contiene la implementación del componente que controla el lanzallamas.

@see Logic::CLanzadorLlamas
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/

#include "LanzadorLlamas.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Entity/Messages/LanzarLlamas.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

namespace Logic 
{
	IMP_FACTORY(CLanzadorLlamas);
	
	//---------------------------------------------------------

	CLanzadorLlamas::CLanzadorLlamas() : IComponent() {

	}

	CLanzadorLlamas::~CLanzadorLlamas() {
		if (_billboard)
			delete _billboard;
		delete _flamesDirection;
	}

	bool CLanzadorLlamas::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		// Billboard que señala el alcance del lanzallamas
		_billboard = new Graphics::CBillboard(entity);
		if(entityInfo->hasAttribute("billboardLlamasMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardLlamasMaterial"));
		if(entityInfo->hasAttribute("billboardLlamasWith") && entityInfo->hasAttribute("billboardLlamasHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardLlamasWith"),entityInfo->getFloatAttribute("billboardLlamasHeight"));
		_billboard->setPerpendicular();
		_billboard->setVisible(false);

		if(entityInfo->hasAttribute("angleLanzallamas"))
			_angleAction = entityInfo->getFloatAttribute("angleLanzallamas");
		if(entityInfo->hasAttribute("radioLanzallamas"))
			_radioAction = entityInfo->getFloatAttribute("radioLanzallamas");
		if(entityInfo->hasAttribute("damageLanzallamas"))
			_damageSecs = entityInfo->getFloatAttribute("damageLanzallamas");
		if(entityInfo->hasAttribute("timeLanzallamas"))
			_timeAction = entityInfo->getFloatAttribute("timeLanzallamas");

		_timeAcc = 0;
		_flamesOn = false;

		return true;
	} // spawn


	bool CLanzadorLlamas::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	void CLanzadorLlamas::deactivate()
	{	

	} // deactivate
	//---------------------------------------------------------

	bool CLanzadorLlamas::accept(IMessage *message)
	{
		return !message->getType().compare("MLanzarLlamas");
	} // accept
	
	//---------------------------------------------------------

	void CLanzadorLlamas::process(IMessage *message)
	{
		if (!message->getType().compare("MLanzarLlamas"))
		{
			MLanzarLlamas *m_flames = static_cast <MLanzarLlamas*> (message);

			if (m_flames->getOrdenLlamas() == mostrarBLlamas)
			{
				_billboard->setVisible(true);
			} 
			else if (m_flames->getOrdenLlamas() == ocultarBLamas)
			{
				_billboard->setVisible(false);
			}
			else if (m_flames->getOrdenLlamas() == lanzarLlamas)
			{
				// PULSAMOS EL LANZALLAMAS

				// Ocultamos el billboard
				_billboard->setVisible(false);
				_flamesOn = true;

				// Posicion destino solo con X, Y.
				Vector2 posDestino = *m_flames->getPosition();
				// Posicion destino con X, Y, Z.
				//Vector3 posDestino3 = Vector3(posDestino.x,4,posDestino.y);
				std::cout << posDestino;
				std::cout << _entity->getPosition();
				Vector3 posDestino3 = ((_entity->getPosition().length() + _radioAction)/(_entity->getPosition().length())) * _entity->getPosition();

				// Calculamos el vector de direccion al que apunta el ratón
				_flamesDirection = new Vector3(posDestino3.x - _entity->getPosition().x, 0, posDestino3.z - _entity->getPosition().z);
				_flamesDirection->normalise();

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
				rc2_message->setSoundEffect("media/sounds/Lanzallamas.ogg");
				_entity->emitInstantMessage(rc2_message,this);

				for(int i = 0; i < numColisiones; ++i)
				{
					// Entidad que se encuentra dentro del círculo de acción
					CEntity * entidad = entidadesColision[i];
					Vector3 targ = entidad->getPosition() - _entity->getPosition();

					// Si está en el sector circular seleccionado se daña a la entidad
					if ((_flamesDirection->angleBetween(targ)).valueDegrees() < _angleAction/2.0f)
					{
						// Enviamos mensaje de daño a la entidad
						MDamaged *mDamaged = new MDamaged();
						mDamaged->setHurt(_damageSecs);
						mDamaged->setKiller(0);
						entidad->emitMessage(mDamaged, this);
					}
				}
			}
		}

	} // process
	
	//---------------------------------------------------------

	void CLanzadorLlamas::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_flamesOn)
		{
			_timeAcc += msecs;

			if (_timeAcc >= 1000)
			{
				Logic::CEntity* * entidadesColision;
				int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(),
						_radioAction, entidadesColision);

				for(int i = 0; i < numColisiones; ++i)
				{
					// Entidad que se encuentra dentro del círculo de acción
					CEntity * entidad = entidadesColision[i];
					Vector3 targ = entidad->getPosition() - _entity->getPosition();
				
					// Si está en el sector circular seleccionado se daña a la entidad
					if ((_flamesDirection->angleBetween(targ)).valueDegrees() < _angleAction/2.0f)
					{
						// Enviamos mensaje de daño a la entidad
						MDamaged *mDamaged = new MDamaged();
						mDamaged->setHurt(_damageSecs);
						mDamaged->setKiller(0);
						entidad->emitMessage(mDamaged, this);
					}
				}
			}
		}

	} // tick

} // namespace Logic