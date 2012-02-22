
#ifndef __Logic_LanzarGranada_H
#define __Logic_LanzarGranada_H

#include "Logic/Entity/Message.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{

	class MLanzarGranada : public IMessage
	{
	public:
		MLanzarGranada();
		~MLanzarGranada();
		void setPosition(Ogre::Vector2 v) {_position = new Ogre::Vector2(v.x,v.y);}
		Ogre::Vector2* getPosition() {return _position;}
	protected:
		Ogre::Vector2 * _position;
	};

} // namespace Logic

#endif