#ifndef __Logic_LanzadorGranadas_H
#define __Logic_LanzadorGranadas_H

#include "Logic/Entity/Component.h"
#include <OgreBillboard.h>

namespace Graphics 
{
	class CBillboard;
}

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CLanzadorGranadas: public IComponent
	{
		DEC_FACTORY(CLanzadorGranadas);
	public:

		/**
		Constructor por defecto.
		*/
		CLanzadorGranadas();
		~CLanzadorGranadas();
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();
	protected:
		/*
		Billboard que muestra que esta seleccionado
		*/
		Graphics::CBillboard * _billboard;
	};

	REG_FACTORY(CLanzadorGranadas);

}

#endif
