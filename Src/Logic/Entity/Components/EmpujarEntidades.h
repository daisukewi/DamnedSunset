/**
@file EmpujarEntidades.h

Contiene la declaración del componente que controla la habilidad de golpe de rabia,
empujar a las entidades que estén dentro del círculo de acción del personaje que lanza la habilidad.

@see Logic::CEmpujarEntidades
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/
#ifndef __Logic_EmpujarEntidades_H
#define __Logic_EmpujarEntidades_H

#include "Logic/Entity/Component.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{
/**
	Este componente es el encargado de empujar a las entidades cercanas.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Agosto, 2012
*/
	class CEmpujarEntidades: public IComponent
	{
		DEC_FACTORY(CEmpujarEntidades);
	public:

		/**
		Constructor por defecto.
		*/
		CEmpujarEntidades();
		~CEmpujarEntidades();
		
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();
		virtual void deactivate();

	protected:

		/**
		Entidades que están dentro del círculo de acción de la habilidad de empuje.
		*/
		std::list<CEntity*> _entidades;

		float _timeEmpujar;
		float _distEmpujarSeg;
	};

	REG_FACTORY(CEmpujarEntidades);

} // namespace Logic

#endif // __Logic_EmpujarEntidades_H
