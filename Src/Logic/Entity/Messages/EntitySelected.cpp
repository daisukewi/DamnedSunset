/**
@file EntitySelected.cpp

Contiene la implementación del mensaje ue se encargará de avisar
que se ha seleccionado una entidad.

@author Daniel Flamenco
@date Enero, 2012
*/

#include "EntitySelected.h"

namespace Logic
{

	MEntitySelected::MEntitySelected()
	{
		IMessage();

		_type = "MEntitySelected";
		_interface = false;
		_selectedType = SelectedType::PRIMARY;

	} // MEntitySelected

	//---------------------------------------------------------

	void MEntitySelected::setSelectedEntity(CEntity *entity)
	{
		_selectedEntity = entity;

	} // setSelectedEntity

	//---------------------------------------------------------

	CEntity* MEntitySelected::getSelectedEntity()
	{
		return _selectedEntity;

	} // getSelectedEntity

	Vector3 MEntitySelected::getPoint(){
		return _point;
	}

	void MEntitySelected::setPoint(Vector3 point){
		_point = point;
	}

	bool MEntitySelected::getInterface(){
		return _interface;
	}

	void MEntitySelected::setInterface(bool interface){
		_interface = interface;
	}

	void MEntitySelected::setSelectedType(SelectedType selectedType){
		_selectedType = selectedType;
	} //setSelectedType

	SelectedType MEntitySelected::getSelectedType(){
		return _selectedType;
	}

} // namespace Logic