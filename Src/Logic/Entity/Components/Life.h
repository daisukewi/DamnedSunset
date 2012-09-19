/**
@file Life.h

Contiene la declaración del componente que controla la vida de una entidad.

@see Logic::CLife
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/
#ifndef __Logic_Life_H
#define __Logic_Life_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"
#include "BaseSubsystems/ClockListener.h"

namespace Graphics 
{
	class CEntity;
	class CScene;
	class CBillboard;
}

//declaración de la clase
namespace Logic 
{
/**
	Este componente controla la vida de una entidad. Procesa mensajes MDamaged
	(indican que la entidad ha sido herida) y resta el daño a la vida de la
	entidad.
	<p>
	La vida de la entidad se especifica en el mapa con el atributo "life".

	@todo  Si la vida pasa a ser 0 que la entidad muera (poner animación de muerte?)
	y si es el jugador habrá que terminar el juego. Si la vida sigue siendo mayor 
	que 0 trás un golpe ¿poner la animación de herido?.
	
    @ingroup logicGroup

	@author David Llansó García
	@date Octubre, 2010
*/
	class CLife : public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CLife);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CLife();

		~CLife();
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Este componente sólo acepta mensajes MDamaged.
		*/
		virtual bool accept(IMessage *message);


		/**
		Al recibir un mensaje MDamaged la vida de la entidad disminuye.
		*/
		virtual void process(IMessage *message);

		void actualizarVidaInterfaz();
		void actualizarVidaBillboard();

	protected:

		/**
		Añade un nuevo listener para escuchar la muerte de la entidad a la que pertenece
		este componente.

		@param listener listener a añadir.
		*/
		void addListener(IDeathListener* listener);

		/**
		Borra el listener de la lista de listeners.

		@param listener listener a borrar.
		*/
		void removeListener(IDeathListener* listener);

		/**
		Notifica a todos los listeners de la muerte de la entidad y
		vacia la lista de listeners.
		*/
		void notifyDeathListeners();

		/**
		Vida de la entidad
		*/
		float _life;

		/**
		Vida maxima de la entidad
		*/
		float _maxLife;

		/**
		Booleano que indica si la entidad está muerta.
		*/
		float _death;

		/*
		Billboard que indica si se tiene protección cuando es atacado
		*/
		Graphics::CBillboard * _billboardReduceDamage;

		/*
		Billboard que muestra la vida
		*/
		Graphics::CBillboard * _billboard;

		/*
		Billboard que indica si está confundido
		*/
		Graphics::CBillboard * _billboardConfusion;

		/**
		Tipo Lista de oyentes de la muerte de la entidad.
		*/
		typedef std::list<IDeathListener*> TListenersList;

		/**
		Lista de todos los oyentes de la muerte de la entidad.
		*/
		TListenersList _listeners;
	private:
		/**
		Método heredado de la interfaz IClockListener que será llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed();

		/**
		Indica si hay que llamar a una función de lua cuando esta entidad muera.
		*/
		bool _deathFunction;

		/**
		Nombre de la función de lua que se llamará cuando esta entidad muera.
		*/
		const char *_luaDeathFunction;

		/**
		Indica si hay que llamar a una función de lua cuando esta entidad esté siendo atacada.
		*/
		bool _underAttackFunction;

		/**
		Nombre de la función de lua que se llamará cuando esta entidad esté siendo atacada.
		*/
		const char *_luaUnderAttackFunction;

		/**
		Modificación de daño
		*/
		float _damageModification;

		//Efectos de sonido y particulas
		std::string _lifeDamageSound;
		std::string _lifeDamageEffect;
		std::string _lifeCureSound;
		std::string _lifeCureEffect;



	}; // class CLife

	REG_FACTORY(CLife);

} // namespace Logic

#endif // __Logic_Life_H
