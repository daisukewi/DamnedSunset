/**
@file Attack.h

Contiene la declaración del componente de ataque de una entidad.

@see Logic::CAttack
@see Logic::IComponent

@author Luis Mendoza
@date Marzo, 2012
*/
#ifndef __Logic_Attack_H
#define __Logic_Attack_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente es el encargado de controlar el ataque de una entidad.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Marzo, 2012
*/
	class CAttack : public IComponent, public IDeathListener
	{
		DEC_FACTORY(CAttack);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CAttack() : IComponent(), IDeathListener(), _attack(false), _damage(0) {}
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se moverá el jugador.

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

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		Método virtual que elige que mensajes son aceptados.
		Son válidos MAttackEntity.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

		/**
		Método heredado de la interfaz IDeathListener que será llamado
		cuando la entidad muera.
		*/
		virtual void entityDeath(CEntity* entity);

	protected:

		/**
		Atributo que indica cuantos puntos de vida quita la entidad.
		*/
		float _damage;

		/**
		Atributo para saber si la entidad tiene que atacar.
		*/
		bool _attack;

		/**
		Atributo para saber a la entidad que hay que atacar.
		*/
		CEntity* _targetEntity;

	}; // class CAttack

	REG_FACTORY(CAttack);

} // namespace Logic

#endif // __Logic_Attack_H
