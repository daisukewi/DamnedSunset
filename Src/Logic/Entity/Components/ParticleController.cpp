#include "ParticleController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Graphics\ParticleEffect.h"

#include "Physics\Server.h"

#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/ParticleEffect.h"

#include "Logic/Entity/Messages/SetTransform.h"

#include "BaseSubsystems/Server.h"

namespace Logic 
{
	IMP_FACTORY(CParticleController);
	
	//---------------------------------------------------------
	CParticleController::CParticleController()  : IComponent() {
	}
	bool CParticleController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_countParticles = 0;
		return true;

	} // spawn
	
	CParticleController::~CParticleController(){

		
		
	}
	//---------------------------------------------------------

	bool CParticleController::activate()
	{	
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CParticleController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CParticleController::accept(IMessage *message)
	{
		return (!message->getType().compare("MSetTransform")
			 || !message->getType().compare("MParticleEffect")
		);

	} // accept

	//---------------------------------------------------------

	void CParticleController::process(IMessage *message)
	{
		if (!message->getType().compare("MParticleEffect")){

			//MParticleEffect *m = static_cast <MParticleEffect*> (message);
			//Graphics::CServer::getSingletonPtr()->createParticleEffect(m->getEffect(),m->getPoint());

			MParticleEffect *m = static_cast <MParticleEffect*> (message);
			
			
			std::stringstream aux;
			aux << m->getEffect() << "_" << _entity->getEntityID() << _countParticles;
			Graphics::CParticleEffect *particle = new Graphics::CParticleEffect(aux.str(),m->getEffect(),m->getPoint(),m->getAltura());

			if (!((m->getOrientation().x != 0) && (m->getOrientation().x != 0) && (m->getOrientation().x != 0)))
				particle->setOrientation(m->getOrientation());
			particle->setStatic(m->getStatic());
			_particleList.push_back(particle);

			_countParticles++;
	
			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(5000, this);

		}else if (!message->getType().compare("MSetTransform")){

			MSetTransform *m = static_cast <MSetTransform*> (message);
			TParticleList::const_iterator it = _particleList.begin();
			TParticleList::const_iterator end = _particleList.end();

			for(; it != end; it++)
				if (!(*it)->getStatic())
				(*it)->setPosition(m->getTransform().getTrans());
		}
	} // process

	//---------------------------------------------------------

	void CParticleController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);	

	} // tick

	void CParticleController::timeElapsed(){

		Graphics::CParticleEffect *aux = _particleList.front();
		_particleList.pop_front();
		delete aux;
	}

	//---------------------------------------------------------

	unsigned int CParticleController::getThaId()
	{
		return _entity->getEntityID();
	}

} // namespace Logic
