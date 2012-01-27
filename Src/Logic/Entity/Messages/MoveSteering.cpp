/**
@file MoveSteering.cpp

Contiene la implementación del mensaje de un steering movement.

@author Luis Mendoza
@date Enero, 2012
*/

#include "MoveSteering.h"

namespace Logic
{

	CMoveSteering::CMoveSteering()
	{
		IMessage();

		_type = "CMoveSteering";

	} // CMoveSteering

	//---------------------------------------------------------

	void CMoveSteering::setMovementType(int movementType)
	{
		_movType = movementType;

	} // setMovementType

	//---------------------------------------------------------

	int CMoveSteering::getMovementType()
	{
		return _movType;

	} // getMovementType

	//---------------------------------------------------------

	void CMoveSteering::setTarget(Vector3 target)
	{
		_target = target;

	} // setTarget

	//---------------------------------------------------------

	Vector3 CMoveSteering::getTarget()
	{
		return _target;

	} // getTarget

	//---------------------------------------------------------

} // namespace Logic