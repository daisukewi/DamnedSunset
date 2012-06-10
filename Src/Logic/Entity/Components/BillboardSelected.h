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
		Material del billboard cuando el personaje est� selecionado 
		*/
		std::string _material;

		/**
		Material del billboard cuando el personajes est� seleccionado en una multiple selecci�n
		*/
		std::string _materialMultiple;

		bool billboardVisible;
	};

	REG_FACTORY(CBillboardSelected);

}

#endif
