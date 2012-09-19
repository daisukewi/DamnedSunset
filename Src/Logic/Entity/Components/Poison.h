#ifndef __Logic_Poison_H
#define __Logic_Poison_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

namespace Graphics 
{
	class CBillboard;
}

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CPoison: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CPoison);
	public:
		
		/**
		Constructor por defecto.
		*/
		CPoison() ;
		~CPoison();

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();
		virtual void tick(unsigned int msecs);

		/**
		Método heredado de la interfaz IClockListener que será llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed();

	protected:
		float _damage;
		int _time;
		float _count;
	
		bool _poison;

		/*
		Billboard que muestra cuando está envenenado
		*/
		Graphics::CBillboard * _billboard;

		//sonido y efecto
		std::string _poisonSound;
		std::string _poisonEffect;
	};

	REG_FACTORY(CPoison);

}

#endif
