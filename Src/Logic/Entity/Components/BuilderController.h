/**
@file BuilderController.h

Contiene la declaraci�n del componente que controla la construcci�n
de los edificios.

@see Logic::CBuilderController
@see Logic::IComponent

@author Daniel Flamenco
@date Enero, 2012
*/
#ifndef __Logic_BuilderController_H
#define __Logic_BuilderController_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Graphics
{
	class CMaterial;
	class CBasicShapeEntity;
}
namespace Logic 
{
	class CEntity;
}

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente es el encargado de mover a una entidad animada. Tiene
	diferentes m�todos que permiten avances o giros. El uso de este componente
	es un poco at�pico ya que se puede registrar en otro controlador externo
	(i.e. GUI::CPlayerController) que sea el que de las �rdenes que se deben
	llevar a cabo mediante llamadas a m�todos p�blicos del componente. Puede
	no obstante ampliarse este componente para aceptar mensajes tradicionales
	con las �rdenes, sin embargo de momento as� es suficiente.
	
    @ingroup logicGroup

	@author Daniel Flamenco
	@date Enero, 2012
*/
	class CBuilderController : public IComponent
	{
		DEC_FACTORY(CBuilderController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CBuilderController() : IComponent(), _building(false), _buildingNumber(0) {}
		
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
		Si el componente pertenece a la entidad del jugador, el componente
		se registra as� mismo en el controlador del GUI para que las ordenes 
		se reciban a partir de los eventos de teclado y rat�n.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se deregistra as� mismo en el controlador del GUI para dejar de
		recibir las ordenes dadas a partir de los eventos de teclado y rat�n.
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
		virtual bool accept(IMessage *message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

	protected:

		/**
		M�todo que se llama para comenzar a construir un edificio.
		Crea una entidad fantasma (sin f�sica) del tipo de edificio que se quiere construir.

		@param buildingType Tipo de edificio que se quiere construir.
		*/
		void startBuilding( std::string buildingType );

		/**
		Cancela la construcci�n que se est� realizando en ese momento.
		*/
		void cancelBuilding();

		/**
		M�todo que se llama para aceptar una construcci�n.
		Elimina la entidad fantasma que sigue al cursor y lo sustituye por una entidad f�sica
		con nombre propio, en la misma posici�n que estaba la fantasma.
		*/
		void emplaceBuilding();

		/**
		M�todo que se llama para mover el edificio fantasma a la posici�n
		donde se encuentra el cursor.

		@param pos Posici�n del plano 2D donde hay que posicionar la entidad.
		*/
		void moveBuilding( Vector2 pos );

		/**
		M�todo que se encarga de comprobar si el edificio en construcci�n
		puede construirse en la posici�n en que se encuentra.

		@return true si se puede construir.
		*/
		bool CheckBuildingCanEmplace();

		/**
		Atributo que controla que est� construyendo un edificio.
		*/
		bool _building;

		/**
		Atributo que contiene a la entidad "fantasma"
		del edificio que se est� construyendo.
		*/
		CEntity *_buildingEntity;

		/**
		Atributo que lleva la cuenta del identificador del edificio
		que se tiene que construir.
		*/
		int _buildingNumber;

		/**
		Atributos que almacenan el tama�o en casillas que ocupa el
		edificio en el mapa l�gico.
		*/
		unsigned int _buildingHeight, _buildingWidth;

		/**
		Almacena el tama�o de las casillas del mapa.
		*/
		unsigned int _gridSize;

		/**
		Guarda los materiales que se asignan al construir,
		para indicar si se puede construir en esa posici�n o no.
		*/
		Graphics::CMaterial* _OkBuildMaterial;
		Graphics::CMaterial* _NokBuildMaterial;

		/**
		Plano que se crea al construir, y contiene los materiales
		que indican si se puede construir en esa posici�n o no.
		*/
		Graphics::CBasicShapeEntity* _plane;

	}; // class CBuilderController

	REG_FACTORY(CBuilderController);

} // namespace Logic

#endif // __Logic_BuilderController_H
