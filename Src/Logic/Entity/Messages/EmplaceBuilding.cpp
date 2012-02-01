/**
@file EmplaceBuilding.cpp

Contiene la implementación del mensaje de construir un edificio.

@author Daniel Flamenco
@date Enero, 2012
*/

#include "EmplaceBuilding.h"

namespace Logic
{

	MEmplaceBuilding::MEmplaceBuilding()
	{
		IMessage();

		_type = "MEmplaceBuilding";

	} // MEmplaceBuilding

	//---------------------------------------------------------

	void MEmplaceBuilding::setAction(BuildingAction action)
	{
		_action = action;

	} // setAction

	//---------------------------------------------------------

	BuildingAction MEmplaceBuilding::getAction()
	{
		return _action;

	} // getAction

	//---------------------------------------------------------

	void MEmplaceBuilding::setBuildingType(std::string buildingType)
	{
		_buildingType = buildingType;

	} // setBuildingType

	//---------------------------------------------------------

	std::string MEmplaceBuilding::getBuildingType()
	{
		return _buildingType;

	} // getBuildingType

	//---------------------------------------------------------

} // namespace Logic