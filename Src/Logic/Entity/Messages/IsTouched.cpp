/**
@file IsTouched.cpp

Contiene la implementación del mensaje que indica si una entidad ha entrado en contacto con otra o si han dejado
de estar en contacto.

@author Alberto Plaza
@date Enero, 2012
*/

#include "IsTouched.h"

namespace Logic
{

	MIsTouched::MIsTouched()
	{
		IMessage();

		_type = "MIsTouched";

	} // MIsTouched

	//---------------------------------------------------------

	void MIsTouched::setTouched(bool touched)
	{
		_touched = touched;

	} // setTouched

	//---------------------------------------------------------

	bool MIsTouched::getTouched()
	{
		return _touched;

	} // getTouched

	//---------------------------------------------------------

	void MIsTouched::setEntity(CEntity *entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	CEntity* MIsTouched::getEntity()
	{
		return _entity;
	
	} // getEntity

	//---------------------------------------------------------

} // namespace Logic