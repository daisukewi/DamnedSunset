#ifndef __Logic_DetonadorGranada_H
#define __Logic_DetonadorGranada_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CDetonadorGranada: public IComponent, public BaseSubsystems::IClockListener, public IDeathListener
	{
		DEC_FACTORY(CDetonadorGranada);
	public:

		/**
		Constructor por defecto.
		*/
		CDetonadorGranada();
		~CDetonadorGranada();
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();

		/**
		M�todo heredado de la interfaz IDeathListener que ser� llamado
		cuando una entidad muera.
		*/
		virtual void entityDeath(CEntity* entity);

		/**
		M�todo heredado de la interfaz IClockListener que ser� llamado
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

	REG_FACTORY(CDetonadorGranada);

}

#endif
