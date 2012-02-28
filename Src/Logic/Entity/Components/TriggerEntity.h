/**
@file TriggerEntity.h

Contiene la declaración del componente encargado de la representación de los triggers.

@see Logic::CTriggerEntity
@see Logic::IComponent
@see Logic::CPhysicEntity

@author Luis Mendoza
@date Febrero, 2012
*/
#ifndef __Logic_TriggerEntity_H
#define __Logic_TriggerEntity_H

#include "Logic/Entity/Component.h"
#include "Physics/Server.h"

// Predeclaración de clases para ahorrar tiempo de compilación
class IPhysicModel;
class CPhysicModelSimple;
class IPhysicObj;

// Los componentes pertenecen al namespace Logic
namespace Logic 
{	
	// Constantes para las cadenas que se usan para definir las entidades en el
	// fichero de mapa.
	const std::string STR_TRIGGER_SHAPE = "trigger_shape";
	const std::string STR_TRIGGER_TYPE = "trigger_type";
	const std::string STR_TRIGGER_CAPSULE = "trigger_capsule";
	const std::string STR_TRIGGER_RADIUS = "trigger_radius";
	const std::string STR_TRIGGER_HEIGHT = "trigger_height";
	const std::string STR_TRIGGER_PLANE = "trigger_plane";
	const std::string STR_TRIGGER_NORMAL = "trigger_normal";
	const std::string STR_TRIGGER_BOX = "trigger_box";
	const std::string STR_TRIGGER_DIMENSIONS = "trigger_dimensions";
	const std::string STR_TRIGGER = "trigger";
	const std::string STR_TRIGGER_COLLISION_GROUP = "trigger_collision_group";

	/**
	Componente encargardo de la representación de los triggers.
	<p>
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class CTriggerEntity : public IComponent
	{
		DEC_FACTORY(CTriggerEntity);
	public:
	
		/**
		Constructor por defecto.
		*/
		CTriggerEntity();

		/**
		Destructor (virtual). Elimina el trigger de la escena y lo destruye. 
		*/
		virtual ~CTriggerEntity();
		
		/**
		Inicializa el componente usando los atributos definidos en el fichero de
		mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);


		/**
		Este componente sólo acepta mensajes de tipo  */
		virtual bool accept(IMessage *message);

		/**
		Si se recibe un mensaje de tipo 
		*/
		virtual void process(IMessage *message);

		/**
		Este método se invoca en cada ciclo de la simulación.
		*/
		virtual void tick(unsigned int msecs);

		/**
		Este método se invoca cada vez que la entidad física asociada a este 
		componente interactúa con otra, siendo alguna de ellas un trigger. Debemos 
		tener en cuenta que las dos entidades involucradas serán notificadas a 
		través de este método. Por tanto, el parámetro "otherEntity" puede representar
		tanto una entidad asociada a un trigger (cuando se notifica a la otra entidad)
		como una entidad física de cualquier tipo (cuando se notifica al trigger).

		@param otherEntity La otra entidad involucrada.
		@param enter Indica si una entidad física ha entrado en el trigger.
		@param leave Indica si una entidad física ha salido del trigger.
		@param stay Indica si una entidad física permanece dentro del trigger.
		*/
		virtual void onEntityTrigger(const CEntity *otherEntity, bool enter, bool leave, bool stay);

	protected:

		/**
		Este método construye y devuelve el trigger asociado a este componente, 
		en base a la información del mapa.
		
		@param entityInfo Descripción de la entidad en el fichero de mapa.
		@return Entidad física creada, NULL si hubo algún problema.
		*/
		virtual IPhysicObj* createTriggerEntity(const Map::CEntity *entityInfo);

		/**
		Servidor de física.
		*/
		Physics::CServer *_physicServer;
		
		/**
		Entidad física asociada a este componente.
		*/
		IPhysicObj *_physicObj;

	private:

		/**
		Este método construye y devuelve un modelo que describe un tipo de entidad física simple.
		Las entidades físicas simples pueden estar formadas por varios volúmenes de colisión.

		@param entityInfo Descripción de la entidad en el fichero de mapa.
		@return Modelo que describe una entidad física simple.
		*/
		CPhysicModelSimple* createTriggerModel(const Map::CEntity *entityInfo);

		/**
		Este método añade un volumen de colisión (shape) a un modelo físco simple. El tipo de volumen
		que se debe crear (caja, cilindro, plano, etc) se obtiene a partir de la descripción de la
		entidad en el fichero de mapa.

		@param entityInfo Descripción de la entidad en el fichero de mapa.
		@param model Modelo físico que describe un tipo de entidad física simple.
		@param scale Factor que permite escalar el tamaño del volumen de colision creado.
		*/
		void createTriggerShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale);

	}; // class CTriggerEntity

	REG_FACTORY(CTriggerEntity);

} // namespace Logic

#endif // __Logic_CTriggerEntity_H
