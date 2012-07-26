/**
@file BuilderController.cpp

Contiene la implementación del componente que controla el movimiento 
de los edificios sobre el escenario, cuando se van a construir.
 
@see Logic::CBuilderController
@see Logic::IComponent

@author Daniel Flamenco
@date Enero, 2012
*/

#include "BuilderController.h"

#include "Logic/Maps/EntityFactory.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/Material.h"
#include "Graphics/BasicShapeEntity.h"
#include "Graphics/Prefabs/SimpleModel.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/EmplaceBuilding.h"
#include "Logic/Entity/Messages/MouseMove.h"
#include "Logic/Entity/Messages/MouseEvent.h"

#include "ScriptManager/Server.h"

#include "Graphics/ModelFactory.h"


namespace Logic 
{
	IMP_FACTORY(CBuilderController);

	//---------------------------------------------------------

	bool CBuilderController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_gridMap = map->getGridMap();
		_gridSize = _gridMap->getGridSize();

		_OkBuildMaterial = new Graphics::CMaterial("BuildingCanEmplace");
		_NokBuildMaterial = new Graphics::CMaterial("BuildingCannotEmplace");


		std::stringstream script;
		script	<< "buildings[" << _entity->getEntityID() << "] = {}";
		script << "buildings[" << _entity->getEntityID()  << "].attackEnemy = -1 ";
		script << "buildings[" << _entity->getEntityID()  << "].activate = true ";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		
		std::stringstream script2;
		script2	<< "buildings[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
				<< "buildings[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
				<< "buildings[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z;
		ScriptManager::CServer::getSingletonPtr()->executeScript(script2.str().c_str());


		return true;

	} // spawna
	
	//---------------------------------------------------------

	bool CBuilderController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CBuilderController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CBuilderController::accept(IMessage *message)
	{
		return !message->getType().compare("MEmplaceBuilding")
			|| !message->getType().compare("MMouseMove")
			|| !message->getType().compare("MMouseEvent");

	} // accept
	
	//---------------------------------------------------------

	void CBuilderController::process(IMessage *message)
	{
		if (!message->getType().compare("MEmplaceBuilding"))
		{
			MEmplaceBuilding *m_building = static_cast <MEmplaceBuilding*> (message);
			switch (m_building->getAction())
			{
				case BuildingMessage::START_BUILDING:
					startBuilding(m_building->getBuildingType());
					break;
				case BuildingMessage::EMPLACE_BUILDING:
					if (!_building) return;
					emplaceBuilding();
					break;
				case BuildingMessage::CANCEL_BUILDING:
					cancelBuilding();
					break;

			}

		} else if (!message->getType().compare("MMouseMove"))
		{
			MMouseMove *m_mouse = static_cast <MMouseMove*> (message);

			if (!_building) return;
			Vector3 collPoint;
			if (Logic::CServer::getSingletonPtr()->raycastFromViewport(&collPoint, Physics::PG_WORLD) != NULL)
				moveBuilding(Vector2(collPoint.x, collPoint.z));

		}

	} // process
	
	//---------------------------------------------------------

	void CBuilderController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
	} // tick

	//---------------------------------------------------------

	void CBuilderController::startBuilding( std::string buildingType )
	{
		if (_building)
		{
			// Borrar la entidad que se estaba construyendo antes
			Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);
		}

		_building = true;

		// Creamos una nueva entidad sacada de los arquetipos
		Map::CEntity * buildInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("PhantomTurret");
		buildInfo->setName("PhantomBuilding");

		// Obtenemos el tamaño que ocupa el edificio a construir de los arquetipos.
		Vector2 size = buildInfo->getVector2Attribute("dimension");
		_buildingWidth = size.x;
		_buildingHeight = size.y;

		_buildingEntity = Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());
		if (!_buildingEntity)
		{
			_building = false;
			return;
		}

		// Calculamos el vector que tenemos que sumar al cursor para pintar bien el edificio.
		Vector2 lastCornerPos = _gridMap->getRelativeMapPos(_buildingHeight - 1, _buildingWidth - 1);
		_halfDiagonal = ( lastCornerPos - _gridMap->getRelativeMapPos(0, 0) ) / 2;

		// Pintamos un plano bajo el cursor que indicará si se puede construir o no.
		_plane = Graphics::CModelFactory::getSingletonPtr()->CreatePlane(_entity->getMap()->getScene(),"","",Vector2(_buildingWidth * _gridSize, _buildingHeight * _gridSize),Vector3(0,0,0));

	} //startBuilding

	//---------------------------------------------------------

	void CBuilderController::FreeResources()
	{
		// Borrar la entidad que se estaba construyendo antes
		Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);
		_entity->getMap()->getScene()->removeEntity(_plane);
		delete(_plane);

	} // FreeResources

	//---------------------------------------------------------

	void CBuilderController::cancelBuilding()
	{
		if (!_building) return;

		FreeResources();

		_building = false;

	} // cancelBuilding

	//---------------------------------------------------------

	void CBuilderController::emplaceBuilding()
	{
		if (!_building || _buildingEntity == NULL) return;
		if (!CheckBuildingCanEmplace())
		{
			return;
		}

		Vector3 pos = _buildingEntity->getPosition();
		TGridTile cornerTile = _gridMap->getTileFromPosition(pos.x + _halfDiagonal.x, pos.z + _halfDiagonal.y);
		std::stringstream vecPos, gridPos, buildingName;
		std::string	buildingType;

		vecPos << pos.x << " 0.0 " << pos.z;
		gridPos << cornerTile->GetCol() << " " << cornerTile->GetRow();
		buildingName << _buildingEntity->getName() << ++_buildingNumber;
		buildingType = _buildingEntity->getType();

		// Liberamos los recursos utilizados para pintar el edificio fantasma
		// y el plano que indica si se puede construir o no
		FreeResources();

		// Creamos una nueva entidad con su entidad trigger sacada de los arquetipos
		Map::CEntity * buildInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Turret");

		// Le ponemos un nuevo nombre para poder hacer spawn y la posición del edificio fantasma
		buildInfo->setName(buildingName.str());
		buildInfo->setAttribute("position", vecPos.str());
		buildInfo->setAttribute("grid_position", gridPos.str());

		Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());

		MEmplaceBuilding *b_message = new MEmplaceBuilding();
		b_message->setAction(BuildingAction::FINISH_BUILDING);
		_entity->emitMessage(b_message, this);

		ScriptManager::CServer::getSingletonPtr()->executeScript("finishBuildingState()");

		_building = false;

	} // emplaceBuilding

	//---------------------------------------------------------

	void CBuilderController::moveBuilding( Vector2 pos )
	{
		if (_buildingEntity == NULL) return;

		// Ponemos la nueva posición del edificio en el centro de la casilla que le corresponda.
		Vector2 cornerPos = _gridMap->getRelativeMapPos(pos + _halfDiagonal);
		Vector2 newPos = cornerPos - _halfDiagonal;
		_buildingEntity->setPosition(Vector3(newPos.x, 1.0f, newPos.y));
		
		_plane->setPosition(Vector3(newPos.x, 1.0f, newPos.y));

		CheckBuildingCanEmplace();

	} // moveBuilding

	//---------------------------------------------------------

	bool CBuilderController::CheckBuildingCanEmplace()
	{
		Vector3 pos = _buildingEntity->getPosition();
		TGridTile cornerTile = _gridMap->getTileFromPosition(pos.x + _halfDiagonal.x, pos.z + _halfDiagonal.y);

		int _startRow = cornerTile->GetRow();
		int _startCol = cornerTile->GetCol();

		int _endRow = _startRow + _buildingHeight;
		int _endCol = _startCol + _buildingWidth;

		bool canEmplace = true;

		_plane->SetMaterial(*_OkBuildMaterial);

		for (int row = _startRow; row < _endRow; ++row)
			for (int col = _startCol; col < _endCol; ++col)
			{
				//TODO: Comprobar cada casilla y mandar al pixel shader un color para mostrar
				// el edificio en rojo, amarillo o verde.
				canEmplace &= !_gridMap->getTileFromCoord(row, col)->IsPopulated();
			}
		if (!canEmplace)
		{
			_plane->SetMaterial(*_NokBuildMaterial);
		}

		return canEmplace;

	} // CheckBuildingCanEmplace

} // namespace Logic

