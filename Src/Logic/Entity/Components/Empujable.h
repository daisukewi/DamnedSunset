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
		CEmpujable() ;
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
		/*Porcentaje que le afectara a la hora de que se empuje esta entidad, si el valor es 200, la entidad se empujara el doble de lo normal*/
		int _afectaEmpujar;
	};

	REG_FACTORY(CEmpujable);

}

#endif
