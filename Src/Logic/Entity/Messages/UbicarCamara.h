#ifndef __Logic_UbicarCamara_H
#define __Logic_UbicarCamara_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{

	class MUbicarCamara : public IMessage
	{
	public:
		MUbicarCamara();

		void setPosition(Vector3 pos) {_position = pos;}
		Vector3 getPosition() {return _position;}
	protected:

		/**
		Posicion que indicara a donde se tiene que mover la camara.
		*/
		Vector3 _position;
	};
}
#endif