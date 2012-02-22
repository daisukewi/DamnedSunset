#ifndef __Logic_BillboardIndicacionMover_H
#define __Logic_BillboardIndicacionMover_H

#include "Logic/Entity/Component.h"

namespace Graphics 
{
	class CBillboard;
}

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CBillboardIndicacionMover: public IComponent
	{
		DEC_FACTORY(CBillboardIndicacionMover);
	public:

		/**
		Constructor por defecto.
		*/
		CBillboardIndicacionMover();
		~CBillboardIndicacionMover();
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de actualizar el billboard de movimiento.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);

	protected:
		/*
		Billboard que muestra que esta seleccionado
		*/
		Graphics::CBillboard * _billboard;
		/*
		Tiempo que permanecera el billboard visible
		*/
		float _time;
		bool _billboardVisible;
		
		float _startDimension;
		float _startTime;
	};

	REG_FACTORY(CBillboardIndicacionMover);

}

#endif
