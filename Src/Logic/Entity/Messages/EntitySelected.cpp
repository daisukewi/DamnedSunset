/**
@file EntitySelected.cpp

Contiene la implementaci�n del mensaje ue se encargar� de avisar
que se ha seleccionado una entidad.

@author Daniel Flamenco
@date Enero, 2012
*/

#include "EntitySelected.h"

namespace Logic
{

	void MEntitySelected::setSelectedEntity(CEntity *entity)
	{
		_selectedEntity = entity;

	} // setSelectedEntity

	//---------------------------------------------------------

	CEntity* MEntitySelected::getSelectedEntity()
	{
		return _selectedEntity;

	} // getSelectedEntity

} // namespace Logic