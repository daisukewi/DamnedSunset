/**
@file AnimatedGraphics.cpp

Contiene la implementación del componente que controla la representación
gráfica de una entidad estática.
 
@see Logic::CAnimatedGraphics
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "AnimatedGraphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/StopAnimation.h"

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

		return _animatedGraphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CAnimatedGraphics::accept(IMessage *message)
	{
		return CGraphics::accept(message) ||
			  (message->getType().compare("MSetAnimation") == 0) ||
			   (message->getType().compare("CStopTransform") == 0);

	} // accept
	
	//---------------------------------------------------------

	void CAnimatedGraphics::process(IMessage *message)
	{
		CGraphics::process(message);

		if (!message->getType().compare("MSetAnimation"))
		{
			MSetAnimation *m = static_cast <MSetAnimation*> (message);

			// Paramos todas las animaciones antes de poner una nueva.
			// Un control más sofisticado debería permitir interpolación
			// de animaciones. Galeon no lo plantea.
			_animatedGraphicsEntity->stopAllAnimations();
			_animatedGraphicsEntity->setAnimation(m->getAnimationName(),m->getLoop());
		}
		else if (!message->getType().compare("MStopAnimation"))
		{
			MStopAnimation *m = static_cast <MStopAnimation*> (message);

			_animatedGraphicsEntity->stopAnimation(m->getAnimationName());
		}

	} // process
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation)
	{
		// Si acaba una animación y tenemos una por defecto la ponemos
		_animatedGraphicsEntity->stopAllAnimations();
		_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
	}

} // namespace Logic

