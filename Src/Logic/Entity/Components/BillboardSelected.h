#ifndef __Logic_BillboardSelected_H
#define __Logic_BillboardSelected_H

#include "Logic/Entity/Component.h"

namespace Graphics 
{
	class CBillboard;
}

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
		Graphics::CBillboard * _billboard;

		/**
		Material del billboard cuando el personaje está selecionado 
		*/
		std::string _material;

		/**
		Material del billboard cuando el personajes está seleccionado en una multiple selección
		*/
		std::string _materialMultiple;

		bool billboardVisible;
	};

	REG_FACTORY(CBillboardSelected);

}

#endif
