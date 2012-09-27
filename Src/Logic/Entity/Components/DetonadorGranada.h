#ifndef __Logic_DetonadorGranada_H
#define __Logic_DetonadorGranada_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CDetonadorGranada: public IComponent, public BaseSubsystems::IClockListener
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
		Método llamado en cada frame que actualiza el estado del componente.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);
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

		float _damage;
		float _timeEmpujar;
		float _distEmpujarSeg;

		//Controlar si ha explotado la granada
		bool _exploited;

		float _radius;

		std::string _detonadorGranadaEffect;
		std::string _detonadorGranadaSound;
	};

	REG_FACTORY(CDetonadorGranada);

}

#endif
