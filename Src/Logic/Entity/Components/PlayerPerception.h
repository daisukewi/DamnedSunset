/**
@file PlayerPerception.h

Contiene la declaración del componente que controla la percepción de los personajes.

@author Alberto Ortega
@date Mayo, 2012
*/
#ifndef __Logic_PlayerPerception_H
#define __Logic_PlayerPerception_H

#include "Logic/Entity/Component.h"

// Predeclaración de clases.
namespace Logic
{
	class CEntity;
}

//declaración de la clase
namespace Logic 
{
/**
	Componente encargado de percibir el mundo y notificar a la IA
	cualquier cosa percibida para la toma de decisiones.
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Mayo, 2012
*/
	class CPlayerPerception : public IComponent
	{
		DEC_FACTORY(CPlayerPerception);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CPlayerPerception() : IComponent(), _distanceOfView(0), _perceptionCountTime(0), _minDistance (100000), _minDistanceEntity(-1) {}
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity).

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.
		<p>

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		<p>

		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de crear un enemigo según ciertas condiciones.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		Método virtual que elige que mensajes son aceptados.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

	protected:

		/**
		Distancia de visión de la entidad.
		*/
		int _distanceOfView;

		/**
		Tipo lista de enemigos.
		*/
		typedef std::list<unsigned int> TEnemyList;

		/**
		Lista de los id enemigos que estoy viendo.
		*/
		TEnemyList _enemyEntities;

		/**
		Lista de los id de los enemigos que han salido del trigger
		*/
		TEnemyList _enemyTriggerOut;


		/**
		Distancia a la que se encuentra el enemigo más cercano
		*/
		int _minDistance;

		/**
		Enemigo más cercano
		*/
		int _minDistanceEntity;

		/**
		Cada cuánto tiempo se ejecuta la percepcion.
		*/
		int _perceptionTime;

		/**
		Cuenta de cuántos tiempo se lleva sin realizarse la percepción.
		*/
		int _perceptionCountTime;



	}; // class CPlayerPerception

	REG_FACTORY(CPlayerPerception);

} // namespace Logic

#endif // __Logic_PlayerPerception_H
