/**
@file SetTransform.cpp

Contiene la implementaci�n del mensaje de aplicar una transformaci�n a una entidad.

@author Alberto Plaza
@date Enero, 2012
*/

#include "SetTransform.h"

namespace Logic
{

	MSetTransform::MSetTransform()
	{
		IMessage();

		_type = "MSetTransform";

	} // MSetTransform

	//---------------------------------------------------------

	void MSetTransform::setTransform(Matrix4 transform)
	{
		_transform = transform;

	} // setTransform

	//---------------------------------------------------------

	Matrix4 MSetTransform::getTransform()
	{
		return _transform;

	} // getTransform

	//---------------------------------------------------------

} // namespace Logic