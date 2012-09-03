/**
@file SelectionCapsule.h

Contiene la declaración del componente encargado de la representación de la capsula de selección

@see Logic::CSelectionCapsule
@see Logic::IComponent
@see Logic::CPhysicEntity

@author Luis Mendoza
@date Febrero, 2012
*/
#ifndef __Logic_SelectionCapsule_H
#define __Logic_SelectionCapsule_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/Components/TriggerEntity.h"

#include "Physics/Server.h"

// Predeclaración de clases para ahorrar tiempo de compilación
class IPhysicModel;
class CPhysicModelSimple;
class IPhysicObj;

// Los componentes pertenecen al namespace Logic
namespace Logic 
{	
	/**
	Componente encargardo de la representación de los triggers.
	<p>
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Febrero, 2012
	*/
	class CSelectionCapsule : public CTriggerEntity
	{
		DEC_FACTORY(CSelectionCapsule);
	public:
	
		/**
		Constructor por defecto.
		*/
		CSelectionCapsule();
		
		/**
		Inicializa el componente usando los atributos definidos en el fichero de
		mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);


	private:


		/**
		Este método indica el tipo de trigger que debemos crear (estática, dinámica o 
		kinemática) a partir de la descripción de la entidad en el fichero de mapa.

		@param entityInfo Descripción de la entidad en el fichero de mapa.
		@return Tipo de entidad física: estática, dinámica o kinemática.
		*/
		virtual Physics::TPhysicMode getTriggerMode(const Map::CEntity *entityInfo);

		/**
		Este método construye y devuelve un modelo que describe un tipo de entidad física simple.
		Las entidades físicas simples pueden estar formadas por varios volúmenes de colisión.

		@param entityInfo Descripción de la entidad en el fichero de mapa.
		@return Modelo que describe una entidad física simple.
		*/
		virtual CPhysicModelSimple* createTriggerModel(const Map::CEntity *entityInfo);

		/**
		Este método añade un volumen de colisión (shape) a un modelo físco simple. El tipo de volumen
		que se debe crear (caja, cilindro, plano, etc) se obtiene a partir de la descripción de la
		entidad en el fichero de mapa.

		@param entityInfo Descripción de la entidad en el fichero de mapa.
		@param model Modelo físico que describe un tipo de entidad física simple.
		@param scale Factor que permite escalar el tamaño del volumen de colision creado.
		*/
		virtual void createTriggerShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale);


	}; // class CSelectionCapsule

	REG_FACTORY(CSelectionCapsule);

} // namespace Logic

#endif // __Logic_CSelectionCapsule_H
