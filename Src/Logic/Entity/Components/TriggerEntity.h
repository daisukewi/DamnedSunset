/**
@file TriggerEntity.h

Contiene la declaraci�n del componente encargado de la representaci�n de los triggers.

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

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
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
	Componente encargardo de la representaci�n de los triggers.
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
		Este componente s�lo acepta mensajes de tipo  */
		virtual bool accept(IMessage *message);

		/**
		Si se recibe un mensaje de tipo 
		*/
		virtual void process(IMessage *message);

		/**
		Este m�todo se invoca en cada ciclo de la simulaci�n.
		*/
		virtual void tick(unsigned int msecs);

		/**
		Este m�todo se invoca cada vez que la entidad f�sica asociada a este 
		componente interact�a con otra, siendo alguna de ellas un trigger. Debemos 
		tener en cuenta que las dos entidades involucradas ser�n notificadas a 
		trav�s de este m�todo. Por tanto, el par�metro "otherEntity" puede representar
		tanto una entidad asociada a un trigger (cuando se notifica a la otra entidad)
		como una entidad f�sica de cualquier tipo (cuando se notifica al trigger).

		@param otherEntity La otra entidad involucrada.
		@param enter Indica si una entidad f�sica ha entrado en el trigger.
		@param leave Indica si una entidad f�sica ha salido del trigger.
		@param stay Indica si una entidad f�sica permanece dentro del trigger.
		*/
		virtual void onEntityTrigger(const CEntity *otherEntity, bool enter, bool leave, bool stay);

	protected:

		/**
		Este m�todo construye y devuelve el trigger asociado a este componente, 
		en base a la informaci�n del mapa.
		
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Entidad f�sica creada, NULL si hubo alg�n problema.
		*/
		virtual IPhysicObj* createTriggerEntity(const Map::CEntity *entityInfo);

		/**
		Servidor de f�sica.
		*/
		Physics::CServer *_physicServer;
		
		/**
		Entidad f�sica asociada a este componente.
		*/
		IPhysicObj *_physicObj;

	private:

		/**
		Este m�todo construye y devuelve un modelo que describe un tipo de entidad f�sica simple.
		Las entidades f�sicas simples pueden estar formadas por varios vol�menes de colisi�n.

		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Modelo que describe una entidad f�sica simple.
		*/
		CPhysicModelSimple* createTriggerModel(const Map::CEntity *entityInfo);

		/**
		Este m�todo a�ade un volumen de colisi�n (shape) a un modelo f�sco simple. El tipo de volumen
		que se debe crear (caja, cilindro, plano, etc) se obtiene a partir de la descripci�n de la
		entidad en el fichero de mapa.

		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@param model Modelo f�sico que describe un tipo de entidad f�sica simple.
		@param scale Factor que permite escalar el tama�o del volumen de colision creado.
		*/
		void createTriggerShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale);

	}; // class CTriggerEntity

	REG_FACTORY(CTriggerEntity);

} // namespace Logic

#endif // __Logic_CTriggerEntity_H
