/**
@file Attack.h

Contiene la declaraci�n del componente de ataque de una entidad.

@see Logic::CAttack
@see Logic::IComponent

@author Luis Mendoza
@date Marzo, 2012
*/
#ifndef __Logic_Attack_H
#define __Logic_Attack_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/DeathListener.h"

//declaraci�n de la clase
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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se mover� el jugador.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		*/
		virtual void deactivate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		M�todo virtual que elige que mensajes son aceptados.
		Son v�lidos MAttackEntity.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

		/**
		M�todo heredado de la interfaz IDeathListener que ser� llamado
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
