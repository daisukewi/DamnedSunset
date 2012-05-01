/**
@file AnimatedGraphics.cpp

Contiene la implementaci�n del componente que controla la representaci�n
gr�fica de una entidad est�tica.
 
@see Logic::CAnimatedGraphics
@see Logic::IComponent

@author David Llans�
@date Agosto, 2010
*/

#include "AnimatedGraphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/StopAnimation.h"
#include "Logic/Entity/Messages/SetRealTime.h"

namespace Logic 
{
	IMP_FACTORY(CAnimatedGraphics);
	
	//---------------------------------------------------------

	Graphics::CEntity* CAnimatedGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		_animatedGraphicsEntity = new Graphics::CAnimatedEntity(_entity->getName(),_model);

		if(!_scene->addEntity(_animatedGraphicsEntity))
			return 0;

		_animatedGraphicsEntity->setTransform(_entity->getTransform());
		
		if(entityInfo->hasAttribute("defaultAnimation"))
		{
			_defaultAnimation = entityInfo->getStringAttribute("defaultAnimation");
			_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
			_animatedGraphicsEntity->setObserver(this);
		}

		float scale = 1.0;
		if (entityInfo->hasAttribute("scale"))
			scale = entityInfo->getFloatAttribute("scale");
		_animatedGraphicsEntity->setScale(scale);

		_animatedGraphicsEntity->setRealTime(_entity->getRealTime());

		return _animatedGraphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CAnimatedGraphics::accept(IMessage *message)
	{
		//bool dady_accepted = CGraphics::accept(message);
		//bool accepted = dady_accepted
		//	|| (message->getType().compare("MSetAnimation") == 0)
		//	|| (message->getType().compare("MStopAnimation") == 0);

		//if (!dady_accepted && accepted) message->addPtr();
		//if (accepted) message->addPtr();
		//return accepted;
		return CGraphics::accept(message) || !message->getType().compare("MSetAnimation") || !message->getType().compare("MStopAnimation") || !message->getType().compare("MSetRealTime");
	} // accept
	
	//---------------------------------------------------------

	void CAnimatedGraphics::process(IMessage *message)
	{
		CGraphics::process(message);

		if (!message->getType().compare("MSetAnimation"))
		{
			MSetAnimation *m = static_cast <MSetAnimation*> (message);

			// Paramos todas las animaciones antes de poner una nueva.
			// Un control m�s sofisticado deber�a permitir interpolaci�n
			// de animaciones. Galeon no lo plantea.
			_animatedGraphicsEntity->stopAllAnimations();
			_animatedGraphicsEntity->setAnimation(m->getAnimationName(),m->getLoop());
		}
		else if (!message->getType().compare("MStopAnimation"))
		{
			MStopAnimation *m = static_cast <MStopAnimation*> (message);

			_animatedGraphicsEntity->stopAnimation(m->getAnimationName());
		} else if (!message->getType().compare("MSetRealTime"))
		{
			MSetRealTime *m = static_cast <MSetRealTime*> (message);
			_animatedGraphicsEntity->setRealTime(m->getRealTime());
		}
	} // process
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation)
	{
		// Si acaba una animaci�n y tenemos una por defecto la ponemos
		_animatedGraphicsEntity->stopAllAnimations();
		_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
	}

} // namespace Logic

