/**
@file SetTransform.cpp

Contiene la implementación del mensaje de aplicar una transformación a una entidad.

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