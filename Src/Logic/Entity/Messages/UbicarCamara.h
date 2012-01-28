#ifndef __Logic_UbicarCamara_H
#define __Logic_UbicarCamara_H

#include "Logic/Entity/Message.h"

namespace Logic 
{

	class CUbicarCamara : public IMessage
	{
	public:
		CUbicarCamara();

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