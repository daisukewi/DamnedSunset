/**
@file LUA_EntitySelected.cpp

Contiene la implementación del mensaje de entidad seleccionada que sirve como intermediario entre lua y C++.

@author Luis Mendoza
@date Mayo, 2012
*/

#include "LUA_EntitySelected.h"

#include "Logic/Entity/Messages/EntitySelected.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include <cassert>

namespace ScriptManager
{

	LUA_MEntitySelected::LUA_MEntitySelected()
	{
		LUA_IMessage();

		_interface = false;
		_selectedEntity = "Jack";

		_type = "LUA_MEntitySelected";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void LUA_MEntitySelected::setSelectedEntity(std::string entity)
	{
		_selectedEntity = entity;

	} // setSelectedEntity

	//---------------------------------------------------------

	std::string LUA_MEntitySelected::getSelectedEntity()
	{
		return _selectedEntity;

	} // getSelectedEntity

	//---------------------------------------------------------

	void LUA_MEntitySelected::setInterface(bool interfaz)
	{
		_interface = interfaz;

	} // setInterface

	//---------------------------------------------------------

	bool LUA_MEntitySelected::getInterface()
	{
		return _interface;

	} // getInterface

	//---------------------------------------------------------

	void LUA_MEntitySelected::send()
	{
		Logic::MEntitySelected *m = new Logic::MEntitySelected();
		m->setSelectedEntity(Logic::CServer::getSingletonPtr()->getMap()->getEntityByName(_selectedEntity));
		m->setInterface(_interface);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod")->emitMessage(m);

	} // send

	//---------------------------------------------------------

} // namespace Logic