/**
@file Heal.h

Contiene la declaraci�n del componente que controla la curaci�n.

@see Logic::CHeal
@see Logic::IComponent

@author Luis Mendoza
@date Marzo, 2012
*/
#ifndef __Logic_Heal_H
#define __Logic_Heal_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente es el encargado de curar a una entidad animada.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Marzo, 2012
*/
	class CHeal : public IComponent
	{
		DEC_FACTORY(CHeal);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CHeal() : IComponent(), _cure(false), _lifeToHeal(50.0f) {}
		
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
		Son v�lidos MCureEntity.

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
		Atributo para saber si la entidad tiene que curar.
		*/
		bool _cure;

		/**
		Puntos de vida a curar.
		*/
		float _lifeToHeal;

		/**
		Atributo para saber la entidad que hay que curar.
		*/
		CEntity* _targetEntity;

		/**
		Sonido y efecto particulas
		*/
		std::string _healSound;
		std::string _healEffect;


	}; // class CHeal

	REG_FACTORY(CHeal);

} // namespace Logic

#endif // __Logic_Heal_H