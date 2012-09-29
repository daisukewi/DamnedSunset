#ifndef __Logic_HealZone_H
#define __Logic_HealZone_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CHealZone: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CHealZone);
	public:

		/**
		Constructor por defecto.
		*/
		CHealZone();
		~CHealZone();
		
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
		virtual unsigned int getThaId();

	protected:

		/**
		Entidades que estan en el rango de curación
		*/
		Logic::CEntity* *_entidades;
		
		int _numEnt;

		float _healTime;
		float _healDistance;
		float _healValue;

		std::string _healZoneEffect;
		std::string _healZoneSound;
	};

	REG_FACTORY(CHealZone);

}

#endif
