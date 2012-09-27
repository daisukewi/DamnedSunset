#ifndef __Logic_DetonadorGranadaAturdir_H
#define __Logic_DetonadorGranadaAturdir_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CDetonadorGranadaAturdir: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CDetonadorGranadaAturdir);
	public:

		/**
		Constructor por defecto.
		*/
		CDetonadorGranadaAturdir();
		~CDetonadorGranadaAturdir();
		
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();
		/**
		M�todo llamado en cada frame que actualiza el estado del componente.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);
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

		int _time;

		std::string _detonadorGranadaAturdirEffect;
		std::string _detonadorGranadaAturdirSound;

		bool _exploited;

	};

	REG_FACTORY(CDetonadorGranadaAturdir);

}

#endif
