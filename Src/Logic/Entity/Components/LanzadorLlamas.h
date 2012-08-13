/**
@file LanzadorLlamas.h

Contiene la declaraci�n del componente que controla el lanzallamas.

@see Logic::CLanzadorLlamas
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/
#ifndef __Logic_LanzadorLlamas_H
#define __Logic_LanzadorLlamas_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/Math.h"

namespace Graphics 
{
	class CBillboard;
}

// Los componentes pertenecen al namespace Logic
namespace Logic 
{
/**
	Este componente es el encargado de controlar el lanzallamas.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Agosto, 2012
*/
	class CLanzadorLlamas: public IComponent
	{
		DEC_FACTORY(CLanzadorLlamas);
	public:

		/**
		Constructor por defecto.
		*/
		CLanzadorLlamas();
		~CLanzadorLlamas();
		
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);

		virtual bool activate();
		virtual void deactivate();

	protected:

		/**
		Entidades que est�n dentro del c�rculo de acci�n del lanzallamas.
		*/
		std::list<CEntity*> _entidades;
		/*
		Billboard que muestra el radio de acci�n del lanzallamas.
		*/
		Graphics::CBillboard * _billboard;

		float _angleAction;
		float _radioAction;
		/*
		Tiempo de acci�n del lanzallamas.
		*/
		float _timeAction;
		float _damageSecs;
		/*
		Tiempo transcurrido de acci�n del lanzallamas.
		*/
		float _timeAcc;
		/*
		Vector que nos indica la direcci�n del lanzallamas.
		*/
		Vector3 * _flamesDirection;
		/*
		Booleano que nos indica si el lanzallamas est� encendido o no.
		*/
		bool _flamesOn;
	};

	REG_FACTORY(CLanzadorLlamas);

} // namespace Logic

#endif // __Logic_LanzadorLlamas_H