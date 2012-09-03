/**
@file SelectionCapsule.h

Contiene la declaraci�n del componente encargado de la representaci�n de la capsula de selecci�n

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

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
class IPhysicModel;
class CPhysicModelSimple;
class IPhysicObj;

// Los componentes pertenecen al namespace Logic
namespace Logic 
{	
	/**
	Componente encargardo de la representaci�n de los triggers.
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
		Este m�todo indica el tipo de trigger que debemos crear (est�tica, din�mica o 
		kinem�tica) a partir de la descripci�n de la entidad en el fichero de mapa.

		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Tipo de entidad f�sica: est�tica, din�mica o kinem�tica.
		*/
		virtual Physics::TPhysicMode getTriggerMode(const Map::CEntity *entityInfo);

		/**
		Este m�todo construye y devuelve un modelo que describe un tipo de entidad f�sica simple.
		Las entidades f�sicas simples pueden estar formadas por varios vol�menes de colisi�n.

		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Modelo que describe una entidad f�sica simple.
		*/
		virtual CPhysicModelSimple* createTriggerModel(const Map::CEntity *entityInfo);

		/**
		Este m�todo a�ade un volumen de colisi�n (shape) a un modelo f�sco simple. El tipo de volumen
		que se debe crear (caja, cilindro, plano, etc) se obtiene a partir de la descripci�n de la
		entidad en el fichero de mapa.

		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@param model Modelo f�sico que describe un tipo de entidad f�sica simple.
		@param scale Factor que permite escalar el tama�o del volumen de colision creado.
		*/
		virtual void createTriggerShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale);


	}; // class CSelectionCapsule

	REG_FACTORY(CSelectionCapsule);

} // namespace Logic

#endif // __Logic_CSelectionCapsule_H
