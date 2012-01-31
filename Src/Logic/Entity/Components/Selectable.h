/**
@file Selectable.h

Contiene la declaración del componente que indica si el personaje es seleccioanble o no

@see Logic::CRaycastController
@see Logic::IComponent

@author Alberto Ortega
@date Eneor, 2012
*/
#ifndef __Logic_Selectable_H
#define __Logic_Selectable_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{
/**

	Este componente es el encargado de gestionar los raycast producidos al hacer click en el ratón.
	Para ello se apoya en el servidor de física y una vez obtenido la entidad con la que ha chocado el raycast y el punto,
	le informa al servidor de lógica de este evento.
	
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
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando está andando o desplazándose lateralmente).

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		Método virtual que elige que mensajes son aceptados.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

	protected:
		

	}; // class CAvatarController

	REG_FACTORY(CSelectable);

} // namespace Logic

#endif // __Logic_Selectable_H
