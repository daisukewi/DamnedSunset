/**
@file MoveSteering.cpp

Contiene la implementación del mensaje de un steering movement.

@author Luis Mendoza
@date Enero, 2012
*/

#include "MoveSteering.h"

namespace Logic
{

	MMoveSteering::MMoveSteering() : IMessage(), _firstMoveOfRoute(false)
	{
		_type = "MMoveSteering";

	} // MMoveSteering

	//---------------------------------------------------------

	void MMoveSteering::setMovementType(int movementType)
	{
		_movType = movementType;

	} // setMovementType

	//---------------------------------------------------------

	int MMoveSteering::getMovementType()
	{
		return _movType;

	} // getMovementType

	//---------------------------------------------------------

	void MMoveSteering::setTarget(Vector3 target)
	{
		_target = target;

	} // setTarget

	//---------------------------------------------------------

	Vector3 MMoveSteering::getTarget()
	{
		return _target;

	} // getTarget

	//---------------------------------------------------------

	void MMoveSteering::setFirstMoveOfRoute(bool firstMove)
	{
		_firstMoveOfRoute = firstMove;

	} // setFirstMoveOfRoute

	//---------------------------------------------------------

	bool MMoveSteering::isFirstMoveOfRoute()
	{
		return _firstMoveOfRoute;

	} // isFirstMoveOfRoute

	//---------------------------------------------------------

} // namespace Logic