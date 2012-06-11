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

		void setHeight(float height) {_height = height;}
		float getHeight() {return _height;}
	protected:

		/**
		Entidad a la que tiene que seguir la camara.
		*/
		CEntity* _center;

		/**
		Cantidad de altura que se quiere aumentar o disminuir
		*/
		float _height;
	};
}
#endif