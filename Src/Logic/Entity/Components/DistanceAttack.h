/**
@file DistanceAtack.h

Contiene la declaración del componente que controla el ataque a distancia de los personajes.

@see Logic::CDistnaceAtack
@see Logic::IComponent

@author Alberto Ortega
@date Abril, 2012
*/
#ifndef __Logic_DistanceAttack_H
#define __Logic_DistanceAttack_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"
#include "Logic/Entity/DeathListener.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente es el encargado de controlar el ataque a distancia de los personajes
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Abril, 2012
*/
	class CDistanceAttack : public IComponent
	{
		DEC_FACTORY(CDistanceAttack);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CDistanceAttack():IComponent(){}
		
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
		Daño de la entidad.
		*/
		int _damage;

		/**
		Atributo que indica la puntería de la torreta.
		*/
		float _precision;


		/**
		Entidad a la que se está atacando cuando es necesario atacar de modo contínuo 
		*/
		CEntity *_attackEntity;

		/**
		Indica si se está atacando continuamente
		*/
		bool _continue;


	}; // class CDistanceAtack

	REG_FACTORY(CDistanceAttack);

} // namespace Logic

#endif // __Logic_DistanceAttack_H
