#ifndef __Logic_BillboardSelected_H
#define __Logic_BillboardSelected_H

#include "Logic/Entity/Component.h"
#include <OgreBillboard.h>
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
		CBillboardSelected();
		~CBillboardSelected();
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);

	protected:

		/*
		Billboard que muestra que esta seleccionado
		*/
		Ogre::BillboardSet* _billboardSet;

		bool peticionCrearBillboardEnviada;
	};

	REG_FACTORY(CBillboardSelected);

}

#endif
