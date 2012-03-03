/**
@file ControlRaycast.cpp

Contiene la implementación del mensaje para controlar el lanzamiento de raycasts.

@author Daniel Flamenco
@date Enero, 2012
*/

#include "ControlRaycast.h"
#include "Physics/Server.h"

namespace Logic
{

	MControlRaycast::MControlRaycast()
	{
		IMessage(); 
		
		_type = "MControlRaycast";
		_collisionGroups = Physics::TPhysicGroup::PG_ALL;

	} // MControlRaycast

	//---------------------------------------------------------

	void MControlRaycast::setAction(TRaycastAction action)
	{
		_action = action;

	} // setAction

	//---------------------------------------------------------

	TRaycastAction MControlRaycast::getAction()
	{
		return _action;

	} // getAction

	//---------------------------------------------------------

	void MControlRaycast::setCollisionPoint(Vector3 point)
	{
		_collisionPoint = point;

	} // setCollisionPoint

	//---------------------------------------------------------

	Vector3 MControlRaycast::getCollisionPoint()
	{
		return _collisionPoint;

	} // getCollisionPoint

	//---------------------------------------------------------

	void MControlRaycast::setCollisionEntity(CEntity *entity)
	{
		_collisionEntity = entity;

	} // setCollisionEntity

	//---------------------------------------------------------

	CEntity* MControlRaycast::getCollisionEntity()
	{
		return _collisionEntity;

	} // getCollisionEntity

	//---------------------------------------------------------

	void MControlRaycast::setCollisionGroups(unsigned int groups)
	{
		_collisionGroups = groups;

	} // setCollisionGroups

	//---------------------------------------------------------

	unsigned int MControlRaycast::getCollisionGroups()
	{
		return _collisionGroups;

	} // getCollisionGroups

} // namespace Logic