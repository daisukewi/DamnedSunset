/**
@file SkillsController.h

Contiene la declaraci�n del componente que controla las habilidades de los personajes.

@author Alberto Plaza
@date Julio, 2012
*/
#ifndef __Logic_SkillsController_H
#define __Logic_SkillsController_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Componente encargado de controlar las habilidades de los personajes.
	
    @ingroup logicGroup

	@author Alberto Plaza
	@date Julio, 2012
*/
	class CSkillsController : public IComponent
	{
		DEC_FACTORY(CSkillsController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSkillsController() : IComponent() {}
		
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
		<p>
		Se encarga de crear un enemigo seg�n ciertas condiciones.

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
		Indica si hay que llamar a una funci�n de lua para activar las skills del personaje o no.
		*/
		bool _activateSkillsFunction;

		/**
		Nombre de la funci�n de lua que se llamar� para activar las skills del personaje.
		*/
		const char *_luaActivateSkillsFunction;

	}; // class CSkillsController

	REG_FACTORY(CSkillsController);

} // namespace Logic

#endif // __Logic_SkillsController_H
