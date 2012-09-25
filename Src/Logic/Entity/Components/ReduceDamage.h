#ifndef __Logic_ReduceDamage_H
#define __Logic_ReduceDamage_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/Math.h"

#include "BaseSubsystems/ClockListener.h"

// Predeclaraci�n de clases.
namespace Logic
{
	class CEntity;
}

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CReduceDamage: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CReduceDamage);
	public:

		/**
		Constructor por defecto.
		*/
		CReduceDamage();
		~CReduceDamage();
		
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();

		/**
		M�todo heredado de la interfaz IClockListener que ser� llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed();
	protected:


		/**
		Entidades que estan en el rango de la reducci�n de da�o
		*/
		Logic::CEntity* *_entidades;
		int _numEnt;

		float _reduceTime;
		float _reduceDistance;
		float _reduceDamage;
		float _auxReduceTime;

		std::string _reduceDamageEffect;
		std::string _reduceDamageSound;
	};

	REG_FACTORY(CReduceDamage);

}

#endif
