/**
@fileActivarTiempoBala.h

Contiene la declaración del mensaje para activar el tiempo bala

@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Mayo, 2012
*/

//#define MAX_ENTITIES 5

#ifndef __Logic_ActivarTiempoBala_H
#define __Logic_ActivarTiempoBala_H

#include "Logic/Entity/Message.h"

namespace Logic 
{

	/**
	Clase mensaje que avisa a la entidad fisica para que aplique una fuerza.
	*/
	class MActivarTiempoBala : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MActivarTiempoBala();
		~MActivarTiempoBala();
		void setTime(float time) {_time = time;}
		float getTime() {return _time; }

		void addEntity(unsigned int id);
		unsigned int getNumEntities() {return _numEntities;}
		unsigned int * getEntitiesID() {return _entitiesID;}

		//Pone a null el array de entidades, pero sin destruirlo, para que lo gestione el que haya recibido el mensaje
		void invalidateIDs();
	protected:
		float _time;
		unsigned int * _entitiesID;
		unsigned int _numEntities;

	};

}

#endif