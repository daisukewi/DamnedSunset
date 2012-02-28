/**
@file SelectionController.h

Contiene la declaraci�n del componente que se encarga de gestionar la entidad seleccionada

@see Logic::CRaycastController
@see Logic::IComponent

@author Alberto Ortega
@date Enero, 2012
*/
#ifndef __Logic_SelectionController_H
#define __Logic_SelectionController_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	class IGodState;
}
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
	class CSelectionController : public IComponent
	{
		DEC_FACTORY(CSelectionController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSelectionController() : IComponent(), _canSelect(true),
			_isSelecting(false), _isWaitingForAction(false), _numStates(6), _raycastStart(false) {}
		
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
		M�todo virtual que elige que mensajes son aceptados..

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
		M�todo usado para poder cambiar de estado tanto llam�ndose desde la misma clase, como de las clases de los estados
		
		@param state stado nuevo al que se quiere cambiar
		*/
		void changeState(int state);


		/**
		M�todo usado para obtener la entidada que est� seleccionada

		@return entidad  seleccionada
		*/
		CEntity* getSelectedEntity();

		/**
		M�todo usado para cambiar la entidada que est� seleccionada

		@param entity  entidad nueva seleccionada
		*/
		void changeSelectedEntity(CEntity* entity);

		/**
		M�todo usado para cambiar la vida de la entidad sobre la que recae la acci�n o para dejar de cambiarla

		@param entity  entidad a la que se le modifica la vida
		@param change  booleano que nos indica si modificar la vida o parar de modificarla
		*/
		void changeLife(CEntity* entity, bool change);

		/**
		M�todo usado para mover la entidad sobre la que recae la acci�n

		@param entity  entidad a la que se mueve
		@param point   punto al que se mueve
		*/
		void moveAStar(CEntity* entity, Vector3 point);

	protected:

		void processEntity( Vector3 colPoint, CEntity* colEntity );

		void startSelection();

		void startAction();
		void saveSelectedEntity( CEntity* selectedEntity );
		/**
		Entidad que se encuentra actualmente seleccionada
		*/
		CEntity *_selectedEntity;

		bool _canSelect;

		bool _isSelecting;

		bool _isWaitingForAction;

		bool _raycastStart;


		int _skill;


		/**
		Variable que contiene el n�mero de estados que va a haber
		*/
		int _numStates;

		/**
		Variables para almacenar los estados en los que se puede encontrar el selectionController
		*/
		IGodState** _godStates;


		/**
		Estado activo actualmente
		*/
		IGodState *_activeState;

		/**
		Varibale temporal que se va a usar para saber el bot�n con el que se ha dado click
		*/
		int _button;
		
	}; // class CSelectedController

	REG_FACTORY(CSelectionController);

} // namespace Logic

#endif // __Logic_SelectionController_H
