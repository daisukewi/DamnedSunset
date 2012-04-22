#ifndef __Logic_DetonadorBolaTeltr_H
#define __Logic_DetonadorBolaTeltr_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CDetonadorBolaTeltr: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CDetonadorBolaTeltr);
	public:

		/**
		Constructor por defecto.
		*/
		CDetonadorBolaTeltr();
		~CDetonadorBolaTeltr();
		

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

		/**
		Entidades que estan en el rango de la granada
		*/
		std::list<CEntity*> _entidades;
	};

	REG_FACTORY(CDetonadorBolaTeltr);

}

#endif
