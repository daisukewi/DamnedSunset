#ifndef __Logic_Empujable_H
#define __Logic_Empujable_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CEmpujable: public IComponent
	{
		DEC_FACTORY(CEmpujable);
	public:
		
		/**
		Constructor por defecto.
		*/
		CEmpujable();
		~CEmpujable();

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();
		virtual void tick(unsigned int msecs);
	protected:
		float _distPerSecond;
		Vector3 _direccion;
		float _time;
		int _afectaEmpujar;
	};

	REG_FACTORY(CEmpujable);

}

#endif
