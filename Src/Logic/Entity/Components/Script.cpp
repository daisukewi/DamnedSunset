/**
@file Script.cpp

Contiene la implementación del componente que contiene el control y la ejecución de los
scripts asociados a una entidad.

@see Logic::IComponent

@author Alberto Plaza
@date Enero, 2012
*/

#include "Script.h"

namespace Logic
{
	IMP_FACTORY(CScript);

	//---------------------------------------------------------

	bool CScript::spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		return true;

	} // spawn

	//---------------------------------------------------------

	bool CScript::activate()
	{
		return true;

	} // activate

	//---------------------------------------------------------

	void CScript::deactivate()
	{

	} // deactivate

	//---------------------------------------------------------

	bool CScript::accept(IMessage *message)
	{
		return false;

	} // accept

	//---------------------------------------------------------

	void CScript::process(IMessage *message)
	{

	} // process

	//---------------------------------------------------------

	void CScript::tick(unsigned int msecs)
	{
		
	} // tick

	//---------------------------------------------------------

} // namespace Logic