/**
@file CollisionManager.cpp

Contiene la implementaci�n del gestor de colisiones que usaremos en la aplicaci�n. Se encarga
de notificar las colisiones a las entidades l�gicas que lo requieran.

@see ICollisionManager
@see Physics::CCollisionManager

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/

#include "CollisionMng.h"
#include "Logic/Entity/Components/PhysicEntity.h"

#include <NxActor.h>

using namespace Physics;
using namespace Logic;

//--------------------------------------------------

CCollisionMng::CCollisionMng()
{

}

//--------------------------------------------------

CCollisionMng::~CCollisionMng()
{

}

//--------------------------------------------------

NxControllerAction  CCollisionMng::onCharacterObjHit (const CharacterObjHit &hit)
{
	// Obtenemos el objeto f�sico contra el que hemos colisionado. Si es din�mico
	// lo empujamos en la direcci�n del golpe
	IPhysicObj *obj = hit.pObjInfo->pPhysicObj;
	if (obj->IsDynamic() && !obj->IsKinematic()) {
		int nPartIdx = hit.pObjInfo->nPartIdx;
		float coeff = hit.length * 2.0f;
		NxVec3 position = obj->GetWorldPosition(nPartIdx);
		obj->ApplyForceAtPart(hit.dir*coeff, position, nPartIdx, NX_IMPULSE);
	}

	// Indicamos a PhysX que no debe aplicar m�s fuerzas
	return NX_ACTION_NONE;
}

//--------------------------------------------------
   
NxControllerAction  CCollisionMng::onCharactersHit (const CharactersHit &hit)
{
	return NX_ACTION_NONE;
}

//--------------------------------------------------

void  CCollisionMng::onTrigger (const TActorInfo &triggerInfo, const TActorInfo &otherInfo, NxTriggerFlag status)
{
	assert(triggerInfo.pPhysicObj->userData);
	assert(otherInfo.pPhysicObj->userData);
	
	bool enter = (status & NX_TRIGGER_ON_ENTER) > 0; // Un cuerpo entra en el trigger  
	bool leave = (status & NX_TRIGGER_ON_LEAVE) > 0; // Un cuerpo sale del trigger
	bool stay =  (status & NX_TRIGGER_ON_STAY) > 0;  // Un cuerpo permanece en el trigger
	
	// Obtener el componente y la entidad asociados al trigger
	CPhysicEntity *triggerComponent = reinterpret_cast<CPhysicEntity*> (triggerInfo.pPhysicObj->userData);
	CEntity *triggerEntity = triggerComponent->getEntity();

	// Obtener el componente y la entidad asociados al otro actor
	CPhysicEntity *otherComponent = reinterpret_cast<CPhysicEntity*> (otherInfo.pPhysicObj->userData);
	CEntity *otherEntity = otherComponent->getEntity();

	// Notificar a ambos componentes la colision
	triggerComponent->onEntityTrigger(otherEntity, enter, leave, stay);
	otherComponent->onEntityTrigger(triggerEntity, enter, leave, stay);
}

//--------------------------------------------------
  
void  CCollisionMng::onContactNotify (ContactPair &pair, NxU32 events)
{

}

//--------------------------------------------------