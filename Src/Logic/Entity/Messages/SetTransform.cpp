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
		_force = false;

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

	void MSetTransform::setForce(bool force)
	{
		_force = force;

	} // setForce

	//---------------------------------------------------------

	bool MSetTransform::getForce()
	{
		return _force;

	} // getForce

} // namespace Logic