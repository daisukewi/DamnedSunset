/**
@file DistanceAtack.h

Contiene la declaraci�n del componente que controla el ataque a distancia de los personajes.

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

//declaraci�n de la clase
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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity).

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
		<p>

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		<p>
		*/
		virtual void deactivate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		M�todo virtual que elige que mensajes son aceptados.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

	protected:

		/**
		Da�o de la entidad.
		*/
		int _damage;

		/**
		Atributo que indica la punter�a de la torreta.
		*/
		float _precision;


		/**
		Entidad a la que se est� atacando cuando es necesario atacar de modo cont�nuo 
		*/
		CEntity *_attackEntity;

		/**
		Indica si se est� atacando continuamente
		*/
		bool _continue;


	}; // class CDistanceAtack

	REG_FACTORY(CDistanceAttack);

} // namespace Logic

#endif // __Logic_DistanceAttack_H
