#ifndef __Logic_TiempoBala_H
#define __Logic_TiempoBala_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CTiempoBala: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CTiempoBala);
	public:
		/**
		Constructor por defecto.
		*/
		CTiempoBala();
		~CTiempoBala();
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();

		/**
		Método heredado de la interfaz IClockListener que será llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed();
	protected:

		//Entidades y numero de entidades a las que no les afecta el tiempo bala
		unsigned int * _entitiesID;
		unsigned int _numEntities;
	};

	REG_FACTORY(CTiempoBala);
}

#endif
