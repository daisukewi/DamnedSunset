/**
@file LUA_AStarRoute.cpp

LUA

Contiene la implementación del mensaje para calcular una ruta con A*
entre dos puntos del mapa y luego seguirlos con Steering Behaviours.

@author Alberto Ortega
@date Abril, 2012
*/

#include "LUA_AStarRoute.h"

#include "Logic/Entity/Messages/AStarRoute.h"
#include <cassert>

#include "BaseSubsystems/Math.h"

#include "Logic/Maps/Map.h"

#include "Logic/Server.h"

namespace ScriptManager
{

	LUA_MAStarRoute::LUA_MAStarRoute()
	{
		LUA_IMessage();

		_type = "LUA_MAStarRoute";
		_failed = false;
		_start = true;

	} // MAStarRoute

	//---------------------------------------------------------

	void LUA_MAStarRoute::setAction(RouteAction action)
	{
		_action = action;

	} // setAction

	//---------------------------------------------------------

	RouteAction LUA_MAStarRoute::getAction()
	{
		return _action;

	} // getAction

	//---------------------------------------------------------

	void LUA_MAStarRoute::setDestPointX(float destPointX)
	{
		_destPointX = destPointX;

	} //setDestPointX

	//---------------------------------------------------------

	float LUA_MAStarRoute::getDestPointX()
	{
		return _destPointX;

	} //getDestPointX

	//---------------------------------------------------------

	void LUA_MAStarRoute::setDestPointY(float destPointY)
	{
		_destPointY = destPointY;

	} //setDestPointY

	//---------------------------------------------------------

	float LUA_MAStarRoute::getDestPointY()
	{
		return _destPointY;

	} //getDestPointY

	//---------------------------------------------------------

	void LUA_MAStarRoute::setDestPointZ(float destPintZ)
	{
		_destPointZ = destPintZ;

	} //setDestPointZ

	//---------------------------------------------------------

	float LUA_MAStarRoute::getDestPointZ()
	{
		return _destPointZ;

	} //getDestPointZ

	//---------------------------------------------------------

	bool LUA_MAStarRoute::hasRouteFailed()
	{
		return _failed;

	} // hasRouteFailed

	//---------------------------------------------------------

	void LUA_MAStarRoute::setRouteFailed(bool failed)
	{
		_failed = failed;

	} // setRouteFailed

	//---------------------------------------------------------
	void LUA_MAStarRoute::setStart(bool start){
	
		_start = start;
	}// setStart

	//---------------------------------------------------------

	bool LUA_MAStarRoute::getStart(){
		return _start;
	}// getStart

	//---------------------------------------------------------
	void LUA_MAStarRoute::send()
	{
		//assert(!_entityTo == Logic::EntityID::UNASSIGNED && "No se ha indicado a que entidad se envía el mensaje");

		Logic::MAStarRoute *message = new Logic::MAStarRoute();
		if (_start){
			message->setAction(Logic::RouteAction::START_ROUTE);
			message->setRouteDestination(Vector3(_destPointX,_destPointY,_destPointZ));
		}else{
			message->setAction(Logic::RouteAction::STOP_ROUTE);
		}
		
	
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entityTo)->emitMessage(message);

		//delete(this);

	} // send

	//---------------------------------------------------------

} // namespace ScriptManager