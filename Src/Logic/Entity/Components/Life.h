/**
@file Life.h

Contiene la declaraci�n del componente que controla la vida de una entidad.

@see Logic::CLife
@see Logic::IComponent

@author David Llans�
@date Octubre, 2010
*/
#ifndef __Logic_Life_H
#define __Logic_Life_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

namespace Graphics 
{
	class CEntity;
	class CScene;
	class CBillboard;
}

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente controla la vida de una entidad. Procesa mensajes MDamaged
	(indican que la entidad ha sido herida) y resta el da�o a la vida de la
	entidad.
	<p>
	La vida de la entidad se especifica en el mapa con el atributo "life".

	@todo  Si la vida pasa a ser 0 que la entidad muera (poner animaci�n de muerte?)
	y si es el jugador habr� que terminar el juego. Si la vida sigue siendo mayor 
	que 0 tr�s un golpe �poner la animaci�n de herido?.
	
    @ingroup logicGroup

	@author David Llans� Garc�a
	@date Octubre, 2010
*/
	class CLife : public IComponent
	{
		DEC_FACTORY(CLife);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CLife();

		~CLife();
		
		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Este componente s�lo acepta mensajes MDamaged.
		*/
		virtual bool accept(IMessage *message);

		/**
		Al recibir un mensaje MDamaged la vida de la entidad disminuye.
		*/
		virtual void process(IMessage *message);

		/**
		A�ade un nuevo listener para escuchar la muerte de la entidad a la que pertenece
		este componente.
		*/
		void addListener(IDeathListener* listener);

		/**
		Borra el listener de la lista de listeners.
		*/
		void removeListener(IDeathListener* listener);

	protected:

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

		/*
		Billboard que muestra la vida
		*/
		Graphics::CBillboard * _billboard;

		/**
		Tipo Lista de oyentes de la muerte de la entidad.
		*/
		typedef std::list<IDeathListener*> TListenersList;

		/**
		Lista de todos los oyentes de la muerte de la entidad.
		*/
		TListenersList _listeners;

	}; // class CLife

	REG_FACTORY(CLife);

} // namespace Logic

#endif // __Logic_Life_H
