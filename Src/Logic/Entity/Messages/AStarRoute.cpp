/**
@file AStarRoute.cpp

Contiene la implementación del mensaje para calcular una ruta con A*
entre dos puntos del mapa y luego seguirlos con Steering Behaviours.

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "AStarRoute.h"
#include "BaseSubsystems/Math.h"

namespace Logic
{

	MAStarRoute::MAStarRoute()
	{
		IMessage();

		_type = "MAStarRoute";
		_failed = false;

	} // MAStarRoute

	//---------------------------------------------------------

	void MAStarRoute::setAction(RouteAction action)
	{
		_action = action;

	} // setAction

	//---------------------------------------------------------

	RouteAction MAStarRoute::getAction()
	{
		return _action;

	} // getAction

	//---------------------------------------------------------

	Vector3 MAStarRoute::getRouteDestination()
	{
		return _destPoint;

	} // getRouteDestination

	//---------------------------------------------------------

	void MAStarRoute::setRouteDestination(Vector3 dest)
	{
		_destPoint = dest;

	} // setRouteDestination

	//---------------------------------------------------------

	bool MAStarRoute::hasRouteFailed()
	{
		return _failed;

	} // hasRouteFailed

	//---------------------------------------------------------

	void MAStarRoute::setRouteFailed(bool failed)
	{
		_failed = failed;

	} // setRouteFailed

} // namespace Logic