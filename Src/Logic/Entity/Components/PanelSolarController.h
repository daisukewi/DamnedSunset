/**
@file PanelSolarController.h

Contiene la declaraci�n del componente que controla el comportamiento de los paneles solares.

@see Logic::CPanelSolarController
@see Logic::IComponent

@author Luis Mendoza
@date Julio, 2012
*/
#ifndef __Logic_PanelSolarController_H
#define __Logic_PanelSolarController_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente es el encargado de controlar el comportamiento de los paneles solares.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Julio, 2012
*/
	class CPanelSolarController : public IComponent
	{
		DEC_FACTORY(CPanelSolarController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CPanelSolarController() : IComponent(), _radioEnergy(50.0f) {}
		
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
		M�todo virtual que elige qu� mensajes son aceptados.
		Son aceptados los del tipo MDayNight.

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
		Atributo que indica el radio de acci�n del panel solar.
		*/
		float _radioEnergy;

	}; // class CPanelSolarController

	REG_FACTORY(CPanelSolarController);

} // namespace Logic

#endif // __Logic_PanelSolarController_H