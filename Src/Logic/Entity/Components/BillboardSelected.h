#ifndef __Logic_BillboardSelected_H
#define __Logic_BillboardSelected_H

#include "Logic/Entity/Component.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CBillboardSelected: public IComponent
	{
		DEC_FACTORY(CBillboardSelected);
	public:

		/**
		Constructor por defecto.
		*/
		CBillboardSelected() : IComponent() {}
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);

	protected:

	};

	REG_FACTORY(CBillboardSelected);

}

#endif
