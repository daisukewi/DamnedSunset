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

	CIsTouched::CIsTouched()
	{
		IMessage();

		_type = "CIsTouched";

	} // CIsTouched

	//---------------------------------------------------------

	void CIsTouched::setTouched(bool touched)
	{
		_touched = touched;

	} // setTouched

	//---------------------------------------------------------

	bool CIsTouched::getTouched()
	{
		return _touched;

	} // getTouched

	//---------------------------------------------------------

	void CIsTouched::setEntity(CEntity *entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	CEntity* CIsTouched::getEntity()
	{
		return _entity;
	
	} // getEntity

	//---------------------------------------------------------

} // namespace Logic