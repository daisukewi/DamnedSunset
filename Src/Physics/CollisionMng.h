/**
@file CollisionManager.h

Contiene la declaraci�n del gestor de colisiones que usaremos en la aplicaci�n. Se encarga
de notificar las colisiones a las entidades l�gicas que lo requieran.

@see ICollisionManager
@see Physics::CCollisionManager

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/

#ifndef __PHYSICS_COLLISION_MNG_H_
#define __PHYSICS_COLLISION_MNG_H_

#include "IPhysicCollisionMng.h"

#include <map>

namespace Logic {
	class CPhysicEntity;
};

// Las clases f�sica nuevas est�n dentro del namespace Physics
namespace Physics {

	/**
	Clase que gestiona las colisiones entre las entidades f�sicas. Se encarga dichas colisiones
	a las entidades l�gicas que lo requieran.

	@see ICollisionManager

	@ingroup physicsGroup

	@author Antonio S�nchez Ruiz-Granados
	@date Octubre, 2010
	*/
	class CCollisionMng : public IPhysicCollisionMng
	{
	public:
		/**
		Constructor por defecto.
		*/
		CCollisionMng();

		/**
		Destructor.
		*/
		virtual ~CCollisionMng();

		// Called when current controller hits a shape.
		virtual NxControllerAction  onCharacterObjHit (const CharacterObjHit &hit);
	   
		// Called when current controller hits another controller. 
		virtual NxControllerAction  onCharactersHit (const CharactersHit &hit); 

		// Called when a trigger shape reports a trigger event. 
		virtual void  onTrigger (const TActorInfo &triggerInfo, const TActorInfo &otherInfo, NxTriggerFlag status);
	  
		// Called when 2 actors come into contact 
		virtual void  onContactNotify (ContactPair &pair, NxU32 events);
   
	}; // CCollisionMng

}; // namespace Physics

#endif