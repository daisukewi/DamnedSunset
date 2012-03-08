#ifndef __Logic_UbicarCamara_H
#define __Logic_UbicarCamara_H

#include "Logic/Entity/Message.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{

	class MUbicarCamara : public IMessage
	{
	public:
		MUbicarCamara();

		void setEntity(CEntity* entity) {_center = entity;}
		CEntity *getEntity() {return _center;}
	protected:

		/**
		Entidad a la que tiene que seguir la camara.
		*/
		CEntity* _center;
	};
}
#endif