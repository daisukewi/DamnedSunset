/**
@file Selectable.h

Contiene la declaraci�n del componente que indica si el personaje es seleccioanble o no

@see Logic::CRaycastController
@see Logic::IComponent

@author Alberto Ortega
@date Eneor, 2012
*/
#ifndef __Logic_Selectable_H
#define __Logic_Selectable_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**

	Este componente es el encargado de gestionar los raycast producidos al hacer click en el rat�n.
	Para ello se apoya en el servidor de f�sica y una vez obtenido la entidad con la que ha chocado el raycast y el punto,
	le informa al servidor de l�gica de este evento.
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Eneor, 2012
*/
	class CSelectable : public IComponent
	{
		DEC_FACTORY(CSelectable);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSelectable() : IComponent() {}
		
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
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando est� andando o desplaz�ndose lateralmente).

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		M�todo virtual que elige que mensajes son aceptados.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

	protected:
		

	}; // class CAvatarController

	REG_FACTORY(CSelectable);

} // namespace Logic

#endif // __Logic_Selectable_H
