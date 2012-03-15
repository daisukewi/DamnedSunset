/**
@file PhysicDebug.h

Contiene la declaración del componente que controla la representación
gráfica de la entida física

@see Logic::CGraphics
@see Logic::IComponent

@author Álberto Ortega
@date Febrero, 2012
*/
#ifndef __Logic_PhysicDebug_H
#define __Logic_PhysicDebug_H

#include "Logic/Entity/Component.h"
#include <list>
// Predeclaración de clases para ahorrar tiempo de compilación
namespace Graphics 
{
	class CScene;
	class CSimpleModel;
}

//declaración de la clase
namespace Logic 
{
/**
	Componente que se encarga de la representación gráfica de una entidad física.
	Acepta mensajes de cambio de posición y orientación (matriz de 
	transformación) mediante el mensaje MSetTransform.
	
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
		Destructor (virtual); Quita de la escena y destruye la entidad gráfica.
		*/
		virtual ~CPhysicDebug();
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Toma del mapa los atributos
		relacionados con el modelo físico e invoca al método virtual
		createGraphicsEntity() para generar la entidad gráfica.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método virtual que elige que mensajes son aceptados. Son válidos
		MSetTransform.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

	protected:

		/**
		Método virtual que construye la entidad gráfica de la entidad. Otros
		componentes pueden sobreescribirlo para inicializar otro tipo de
		entidades gráficas (animadas, etc.).
		
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Entidad gráfica creada, NULL si hubo algún problema.
		*/
		virtual Graphics::CSimpleModel* createGraphicsEntity(const Map::CEntity *entityInfo);

		/**
		Atributo con el nombre del modelo gráfico de la entidad. (prefab)
		*/
		std::string _model;
		
		/**
		Entidad gráfica del prefab
		*/
		Graphics::CSimpleModel *_graphicsEntity;

		/**
		Entidad gráfica del trigger
		*/
		Graphics::CSimpleModel *_triggerEntity;

		/**
		Escena gráfica donde se encontrarán las representaciones gráficas de
		las entidades. La guardamos para la destrucción de la entidad gráfica.
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
