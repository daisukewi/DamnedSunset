/**
@file PhysicDebug.h

Contiene la declaraci�n del componente que controla la representaci�n
gr�fica de la entida f�sica

@see Logic::CGraphics
@see Logic::IComponent

@author �lberto Ortega
@date Febrero, 2012
*/
#ifndef __Logic_PhysicDebug_H
#define __Logic_PhysicDebug_H

#include "Logic/Entity/Component.h"
#include <list>
// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Graphics 
{
	class CScene;
	class CSimpleModel;
}

//declaraci�n de la clase
namespace Logic 
{
/**
	Componente que se encarga de la representaci�n gr�fica de una entidad f�sica.
	Acepta mensajes de cambio de posici�n y orientaci�n (matriz de 
	transformaci�n) mediante el mensaje MSetTransform.
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2012
*/
	class CPhysicDebug : public IComponent
	{
		DEC_FACTORY(CPhysicDebug);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/				
		CPhysicDebug() : IComponent(), _graphicsEntity(0) , _triggerEntity(0), _redMaterial("physic_debug_red50"), _blueMaterial("physic_debug_blue50"), _greenMaterial("physic_debug_green50") {}

		/**
		Destructor (virtual); Quita de la escena y destruye la entidad gr�fica.
		*/
		virtual ~CPhysicDebug();
		
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa los atributos
		relacionados con el modelo f�sico e invoca al m�todo virtual
		createGraphicsEntity() para generar la entidad gr�fica.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo virtual que elige que mensajes son aceptados. Son v�lidos
		MSetTransform.

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
		M�todo virtual que construye la entidad gr�fica de la entidad. Otros
		componentes pueden sobreescribirlo para inicializar otro tipo de
		entidades gr�ficas (animadas, etc.).
		
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Entidad gr�fica creada, NULL si hubo alg�n problema.
		*/
		virtual Graphics::CSimpleModel* createGraphicsEntity(const Map::CEntity *entityInfo);

		/**
		Atributo con el nombre del modelo gr�fico de la entidad. (prefab)
		*/
		std::string _model;
		
		/**
		Entidad gr�fica del prefab
		*/
		Graphics::CSimpleModel *_graphicsEntity;

		/**
		Entidad gr�fica del trigger
		*/
		Graphics::CSimpleModel *_triggerEntity;

		/**
		Escena gr�fica donde se encontrar�n las representaciones gr�ficas de
		las entidades. La guardamos para la destrucci�n de la entidad gr�fica.
		*/
		Graphics::CScene* _scene;

		/**
		Materiales que va a tener el componente dependiendo del prefab y del tipo de entidad
		**/
		std::string _redMaterial;
		std::string _blueMaterial;
		std::string _greenMaterial;




	}; // class CGraphics

	REG_FACTORY(CPhysicDebug);

} // namespace Logic

#endif // __Logic_PhysicDebug_H
