/**
@file SetTransform.cpp

Contiene la implementación del mensaje de aplicar una transformación a una entidad.

@author Alberto Plaza
@date Enero, 2012
*/

#include "SetTransform.h"

namespace Logic
{

	CSetTransform::CSetTransform()
	{
		IMessage();

		_type = "CSetTransform";

	} // CSetTransform

	//---------------------------------------------------------

	void CSetTransform::setTransform(Matrix4 transform)
	{
		_transform = transform;

	} // setTransform

	//---------------------------------------------------------

	Matrix4 CSetTransform::getTransform()
	{
		return _transform;

	} // getTransform

	//---------------------------------------------------------

} // namespace Logic