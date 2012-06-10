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

		_selectedEntity = "";
		_selectedEntityID = 0;
		_selectedType = "PRIMARY";

		_type = "LUA_MEntitySelected";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void LUA_MEntitySelected::setSelectedEntity(std::string entity)
	{
		_selectedEntity = entity;

	} // setSelectedEntity

	//---------------------------------------------------------

	void LUA_MEntitySelected::setSelectedEntity(unsigned int entityID)
	{
		_selectedEntityID = entityID;

	} // setSelectedEntity

	//---------------------------------------------------------

	void LUA_MEntitySelected::setSelectedType(std::string selectedType)
	{
		_selectedType = selectedType;

	} // setSelectedEntity

	//---------------------------------------------------------
	void LUA_MEntitySelected::send()
	{
		Logic::CEntity *selectedEntity = NULL;
		Logic::MEntitySelected *m = new Logic::MEntitySelected();

		if (_selectedEntityID != 0)
			selectedEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_selectedEntityID);
		else
			selectedEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName(_selectedEntity);

		m->setSelectedEntity(selectedEntity);

		if (!_selectedType.compare("PRIMARY")){
			m->setSelectedType(Logic::EntitySelectedMessage::SelectedType::PRIMARY);
		}else{
			m->setSelectedType(Logic::EntitySelectedMessage::SelectedType::SECONDARY);
		}
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(this->getEntityTo())->emitMessage(m);

	} // send

	//---------------------------------------------------------

} // namespace Logic