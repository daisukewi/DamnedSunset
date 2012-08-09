/**
@file EmpujarEntidades.cpp

Contiene la implementación del componente que controla la habilidad de golpe de rabia,
empujar a las entidades que estén dentro del círculo de acción del personaje que lanza la habilidad.

@see Logic::CEmpujarEntidades
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/

#include "EmpujarEntidades.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"

namespace Logic 
{
	IMP_FACTORY(CEmpujarEntidades);
	
	//---------------------------------------------------------

	CEmpujarEntidades::CEmpujarEntidades() : IComponent() {

	}

	CEmpujarEntidades::~CEmpujarEntidades() {
	}

	bool CEmpujarEntidades::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("timeRabia"))
			_timeEmpujar = entityInfo->getFloatAttribute("timeRabia");
		if(entityInfo->hasAttribute("distRabiaSeg"))
			_distEmpujarSeg = entityInfo->getFloatAttribute("distRabiaSeg");

		return true;
	} // spawn


	bool CEmpujarEntidades::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	void CEmpujarEntidades::deactivate()
	{	

	} // deactivate
	//---------------------------------------------------------

	bool CEmpujarEntidades::accept(IMessage *message)
	{
		return !message->getType().compare("MPushEntities");
	} // accept
	
	//---------------------------------------------------------

	void CEmpujarEntidades::process(IMessage *message)
	{
		if (!message->getType().compare("MPushEntities"))
		{
			Logic::CEntity* * entidadesColision;
			int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(),20,entidadesColision);

			//Envío del mensaje al componente que se encarga de mostrar los efectos de partículas
			MParticleEffect *rc_message = new MParticleEffect();
			rc_message->setPoint(_entity->getPosition());
			rc_message->setEffect("Explosion");
			_entity->emitInstantMessage(rc_message,this);

			//Envío del mensaje al componente que se encarga de reproducir los sonidos
			MSoundEffect *rc2_message = new MSoundEffect();
			rc2_message->setSoundEffect("media/sounds/empuje.mp3");
			_entity->emitInstantMessage(rc2_message,this);

			for(int i = 0; i < numColisiones; ++i)
			{
				//Entidad que es empujada
				CEntity * entidad = entidadesColision[i];

				//Activamos el componente de empujar
				MActivarComponente *mActivar = new MActivarComponente();
				mActivar->setActivar(true);
				mActivar->setNombreComponente("CEmpujable");
				entidad->emitInstantMessage(mActivar, this); //Tiene que ser instantaneo, sino no se empujara ya q no esta activo

				//Calculamos la direccion a la que tenemos que empujar
				Vector3 pos1 = entidad->getPosition();
				Vector3 pos2 = _entity->getPosition();
				Vector3 direccion = Vector3(pos1.x-pos2.x,pos1.y-pos2.y,pos1.z-pos2.z);
				direccion.normalise();
				//----
				MSetEmpujarPropiedades *m = new MSetEmpujarPropiedades();
				m->setDirection(direccion.x,direccion.y,direccion.z);
				m->setTime(_timeEmpujar);
				m->setDistanciaPorSegundo(_distEmpujarSeg);

				entidad->emitMessage(m, this);
			}
		}

	} // process

} // namespace Logic

