/**
@file IsSelectable.cpp

Contiene la implementación del mensaje enviado para preguntar a una entidad si es seleccionable

@author Alberto Ortega
@date Enero, 2012
*/

#include "IsSelectable.h"

namespace Logic
{
	MIsSelectable::MIsSelectable()
	{
		IMessage();

		_type = "MIsSelectable";
	
	} // MIsSelectable

	Vector3 MIsSelectable::getPoint()
	{
		return _point;
	}

	void MIsSelectable::setPoint(Vector3 point)
	{
		_point = point;
	}


} // namespace Logic