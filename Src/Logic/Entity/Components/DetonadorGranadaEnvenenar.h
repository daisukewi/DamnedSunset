#ifndef __Logic_DetonadorGranadaEnvenenar_H
#define __Logic_DetonadorGranadaEnvenenar_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CDetonadorGranadaEnvenenar: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CDetonadorGranadaEnvenenar);
	public:

		/**
		Constructor por defecto.
		*/
		CDetonadorGranadaEnvenenar();
		~CDetonadorGranadaEnvenenar();
		
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

		/**
		Da�o del veneno
		*/
		int _venomDamage; //Da�o del veneno

		/**
		Tiempo envenenado
		*/
		int _venomTime;

		/**
		En cuantas veces se reparte el da�o del veneno
		*/
		int _venomCount;

		std::string _detonadorGranadaEnvenenarEffect;
		std::string _detonadorGranadaEnvenenarSound;

		bool _exploited;
	};

	REG_FACTORY(CDetonadorGranadaEnvenenar);

}

#endif
