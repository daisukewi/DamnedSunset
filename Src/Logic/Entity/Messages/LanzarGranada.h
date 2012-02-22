
#ifndef __Logic_LanzarGranada_H
#define __Logic_LanzarGranada_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{

	class MLanzarGranada : public IMessage
	{
	public:
		MLanzarGranada();
		~MLanzarGranada();
		void setPosition(Vector2 v) {_position = new Vector2(v.x,v.y);}
		Vector2* getPosition() {return _position;}
	protected:
		Vector2 * _position;
	};

} // namespace Logic

#endif