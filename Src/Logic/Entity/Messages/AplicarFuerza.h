/**
@file AplicarFuerza.h

Contiene la declaración del mensaje para aplicar una fuerza sobre una entidad fisica

@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Marzo, 2012
*/

#ifndef __Logic_AplicarFuerza_H
#define __Logic_AplicarFuerza_H

#include "Logic/Entity/Message.h"

#include "Physics/PhysicModelSimple.h"

namespace Logic 
{

	/**
	Clase mensaje que avisa a la entidad fisica para que aplique una fuerza.
	*/
	class MAplicarFuerza : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MAplicarFuerza();

		void setForce(float x, float y, float z) {_force = NxVec3(x,y,z);}
		NxVec3 getForce() {return _force;}

		void setPos(float x, float y, float z) {_pos = NxVec3(x,y,z);}
		NxVec3 getPos() {return _pos;}

	protected:
		NxVec3 _force;
		NxVec3 _pos;
	};

}

#endif