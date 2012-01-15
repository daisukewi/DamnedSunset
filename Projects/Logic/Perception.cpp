#include "Perception.h"

#include "Physics/Server.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	IMP_FACTORY(CPerception);

	void CPerception::tick(unsigned int msecs) {
		IComponent::tick(msecs);

		Vector3 direction = Math::getDirection(_entity->getTransform());
		Ogre::Ray *rayo = new Ray(_entity->getPosition(), direction);
		CEntity *entidad = Physics::CServer::getSingletonPtr()->raycastClosest(*rayo, 10.0);
		if (entidad)
			std::cout << "Veo un: " << entidad->getName() << std::endl;
	}

	//---------------------------------------------------------
}