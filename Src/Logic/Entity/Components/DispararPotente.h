/**
@file DispararPotente.h

Contiene la declaración del componente que controla la habilidad disparos potentes, que consiste
en quitar vida a las entidades contenidas en el sector circular del que lanza los disparos.

@see Logic::CDispararPotente
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/
#ifndef __Logic_DispararPotente_H
#define __Logic_DispararPotente_H

#include "Logic/Entity/Component.h"

namespace Graphics 
{
	class CBillboard;
}

// Los componentes pertenecen al namespace Logic
namespace Logic 
{
/**
	Este componente es el encargado de controlar la habilidad disparos potentes.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Agosto, 2012
*/
	class CDispararPotente: public IComponent
	{
		DEC_FACTORY(CDispararPotente);
	public:

		/**
		Constructor por defecto.
		*/
		CDispararPotente();
		~CDispararPotente();
		
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();
		virtual void deactivate();

	protected:

		/**
		Entidades que están dentro del círculo de acción de la habilidad disparos potentes.
		*/
		std::list<CEntity*> _entidades;
		/*
		Billboard que muestra el radio de acción del disparo.
		*/
		Graphics::CBillboard * _billboard;

		float _angleAction;
		float _radioAction;
		float _damagePowerShoot;

		std::string _dispararPotenteEffect;
		std::string _dispararPotenteSound;
	};

	REG_FACTORY(CDispararPotente);

} // namespace Logic

#endif // __Logic_DispararPotente_H
