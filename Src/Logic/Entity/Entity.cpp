/**
@file Entity.cpp

Contiene la implementación de la clase Entity, que representa una entidad
de juego. Es una colección de componentes.

@see Logic::CEntity
@see Logic::IComponent

@author David Llansó
@date Julio, 2010
*/

#include "Entity.h"

// Componentes
#include "Component.h"

#include "Logic/Server.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/CameraController.h"

#include "Logic/Entity/Messages/SetTransform.h"
#include "Logic/Entity/Messages/EntityDeathListener.h"
#include "Messages/ActivarComponente.h"

#include <vector>
#include <string>
#include <sstream>

#include "ScriptManager/Server.h"

namespace Logic 
{
	CEntity::CEntity(TEntityID entityID) : _entityID(entityID), 
				_map(0), _type(""), _name(""), _transform(Matrix4::IDENTITY),
				_isPlayer(false), _activated(false), _isTargetCamera(false)
	{

	} // CEntity
	
	//---------------------------------------------------------

	CEntity::~CEntity()
	{
		assert(!_map && "¡¡Antes de destruir la entidad debe desacoplarse del mapa!!");

		destroyAllComponents();

	} // ~CEntity
	
	//---------------------------------------------------------

	bool CEntity::spawn(CMap *map, const Map::CEntity *entityInfo) 
	{
		// Leemos las propiedades comunes
		_map = map;
		_type = entityInfo->getType();

		Vector3 position = Vector3::ZERO;

		if(entityInfo->hasAttribute("name"))
			_name = entityInfo->getStringAttribute("name");

		if(entityInfo->hasAttribute("position"))
		{
			position = entityInfo->getVector3Attribute("position");
			// Ponemos a la entidad en el centro de la casilla que le corresponda.
			Vector2 newPos = map->getGridMap()->getRelativeMapPos(Vector2 (position.x, position.z));
			position.x = newPos.x;
			position.z = newPos.y;
		}

		if(entityInfo->hasAttribute("grid_position"))
		{
			Vector2 currentTilePos = entityInfo->getVector2Attribute("grid_position");
			Vector2 relativePosition = map->getGridMap()->getRelativeMapPos(currentTilePos.y, currentTilePos.x);

			position.x = relativePosition.x;
			position.z = relativePosition.y;
		}

		if(entityInfo->hasAttribute("building_size"))
		{
			Vector2 size = entityInfo->getVector2Attribute("building_size");
			//Width = size.x;
			//Height = size.y;

			TGridTile cornerTile = map->getGridMap()->getTileFromPosition(position.x, position.z);

			unsigned int endRow = cornerTile->GetRow() + size.y - 1;
			unsigned int endCol = cornerTile->GetCol() + size.x - 1;

			Vector2 currentPos = Vector2(position.x, position.z);
			Vector2 diagonalVector = currentPos - map->getGridMap()->getRelativeMapPos(endRow, endCol);
			currentPos += diagonalVector / 2;
			
			position.x = currentPos.x;
			position.z = currentPos.y;
		}

		_transform.setTrans(position);

		// Por comodidad en el mapa escribimos los ángulos en grados.
		if(entityInfo->hasAttribute("orientation"))
		{
			float yaw = Math::fromDegreesToRadians(entityInfo->getFloatAttribute("orientation"));
			Math::yaw(yaw,_transform);
		}

		if(entityInfo->hasAttribute("isPlayer"))
			_isPlayer = entityInfo->getBoolAttribute("isPlayer");
		
		if(entityInfo->hasAttribute("isTargetCamera"))
			_isTargetCamera = entityInfo->getBoolAttribute("isTargetCamera");

		// Inicializamos los componentes
		TComponentList::const_iterator it;

		bool correct = true;

		for( it = _components.begin(); it != _components.end() && correct; ++it )
		{
			correct = (*it)->spawn(this,map,entityInfo) && correct;
		}

		//Atributo para desactivar componentes
		if(entityInfo->hasAttribute("disableComponent"))
		{
			std::string s = entityInfo->getStringAttribute("disableComponent");

			std::string buf; // Have a buffer string
			std::stringstream ss(s); // Insert the string into a stream

			while (ss >> buf) {
				MActivarComponente * m = new MActivarComponente();
				m->setNombreComponente(buf);
				m->setActivar(false);
				this->emitMessage(m);
			}
			//Hacemos que los componentes procesen los mensajes para que se desactiven directamente
			for( it = _components.begin(); it != _components.end(); ++it )
			{
				(*it)->processMessages();
			}
		}


		return correct;

	} // spawn

	//---------------------------------------------------------

	bool CEntity::activate() 
	{
		// Si somos jugador, se lo decimos al servidor
		// y nos registramos para que nos informen
		// de los movimientos que debemos realizar
		if (isPlayer())
		{
			CServer::getSingletonPtr()->setPlayer(this);
			GUI::CServer::getSingletonPtr()->getPlayerController()->setControlledAvatar(this);
		}

		// Si somos el objetivo al que apunta la cámara
		// nos registramos para que nos informen de los
		// movimientos que debemos realizar.
		if (isTargetCamera())
		{
			GUI::CServer::getSingletonPtr()->getCameraController()->setControlledTarget(this);
		}

		// Activamos los componentes
		TComponentList::const_iterator it;

		// Solo si se activan todos los componentes correctamente nos
		// consideraremos activados.
		_activated = true;

		for( it = _components.begin(); it != _components.end(); ++it )
		{
			//Solo activamos los componentes que esten esten inicialmente activados
			if ((*it)->isActive())
				_activated = (*it)->activate() && _activated;
		}
	
		//Inicializar las tablas en LUA en las que se encontrará toda la información de las entidadades enemigo y jugador para 
		//su consulta
		if (!_type.compare("Player") || !_type.compare("Enemy"))
		{
			//Crear la tabla
			std::string auxScript;
			std::stringstream auxID;
			auxID << this->getEntityID();
			auxScript = "table" + auxID.str()+ "={ life=0, posx=0, posy=0, posz=0}";
			ScriptManager::CServer::getSingletonPtr()->executeScript(auxScript.c_str());
		}


		return _activated;

	} // activaet

	//---------------------------------------------------------

	void CEntity::deactivate() 
	{
		// Si éramos el jugador, le decimos al servidor que ya no hay.
		// y evitamos que se nos siga informando de los movimientos que 
		// debemos realizar
		if (isPlayer())
		{
			GUI::CServer::getSingletonPtr()->getPlayerController()->setControlledAvatar(0);
			CServer::getSingletonPtr()->setPlayer(0);
		}


		TComponentList::const_iterator it;

		// Desactivamos los componentes
		for( it = _components.begin(); it != _components.end(); ++it )
			(*it)->deactivate();

		_activated = false;

	} // deactivate

	//---------------------------------------------------------

	void CEntity::tick(unsigned int msecs) 
	{
		TComponentList::const_iterator it;

		for( it = _components.begin(); it != _components.end(); ++it )
		{
			if ((*it)->isActive())
				(*it)->tick(msecs); //Tambien se procesan los mensajes dentro del tick
			else
				(*it)->processMessages();
		}
	} // tick

	//---------------------------------------------------------

	void CEntity::addComponent(IComponent* component)
	{
		_components.push_back(component);
		component->setEntity(this);
		
	} // addComponent

	//---------------------------------------------------------

	bool CEntity::removeComponent(IComponent* component)
	{
		TComponentList::const_iterator it = _components.begin();

		bool removed = false;
		// Buscamos el componente hasta el final, por si aparecía
		// más de una vez... (no tendría mucho sentido, pero por si
		// acaso).
		while (it != _components.end()) 
		{
			if (*it == component)
			{
				it = _components.erase(it);
				removed = true;
			}
			else
				++it;
		}
		if (removed)
			component->setEntity(0);
		return removed;

	} // removeComponent

	//---------------------------------------------------------

	void CEntity::destroyAllComponents()
	{
		IComponent* c;
		while(!_components.empty())
		{
			c = _components.back();
			_components.pop_back();
			delete c;
		}

	} // destroyAllComponents

	//---------------------------------------------------------

	bool CEntity::emitMessage(IMessage *message, IComponent* emitter)
	{
		// Interceptamos los mensajes que además de al resto de los
		// componentes, interesan a la propia entidad.
		if (!message->getType().compare("MSetTransform"))
		{
			MSetTransform *m = static_cast <MSetTransform*> (message);
			_transform = m->getTransform();
		}

		message->addPtr();

		TComponentList::const_iterator it;
		// Para saber si alguien quiso el mensaje.
		bool anyReceiver = false;
		for( it = _components.begin(); it != _components.end(); ++it )
		{
			// Al emisor no se le envia el mensaje.
			if( emitter != (*it) )
				anyReceiver = (*it)->set(message) || anyReceiver;
		}

		message->removePtr();

		return anyReceiver;

	} // emitMessage


	bool CEntity::emitInstantMessage(IMessage *message, IComponent* emitter)
	{
		// Interceptamos los mensajes que además de al resto de los
		// componentes, interesan a la propia entidad.
		message->addPtr();

		TComponentList::const_iterator it;
		// Para saber si alguien quiso el mensaje.
		bool anyReceiver = false;
		for( it = _components.begin(); it != _components.end(); ++it )
		{
			// Al emisor no se le envia el mensaje.
			if( emitter != (*it) ) {
				bool aceptado = (*it)->acceptPadre(message);
				anyReceiver = aceptado || anyReceiver;
				if (aceptado)
					(*it)->processPadre(message);
			}
		}
		message->removePtr();
		return anyReceiver;
	} // emitMessage

	//---------------------------------------------------------

	void CEntity::setTransform(const Matrix4& transform) 
	{
		_transform = transform;

		// Avisamos a los componentes del cambio.
		MSetTransform *m = new MSetTransform();

		m->setTransform(_transform);

		emitMessage(m);

	} // setTransform

	//---------------------------------------------------------

	void CEntity::setPosition(const Vector3 &position, const bool force) 
	{
		_transform.setTrans(position);

		// Avisamos a los componentes del cambio.
		MSetTransform *m = new MSetTransform();

		m->setTransform(_transform);
		m->setForce(force);

		emitMessage(m);

	} // setPosition

	//---------------------------------------------------------

	void CEntity::setOrientation(const Matrix3& orientation) 
	{
		_transform = orientation;

		// Avisamos a los componentes del cambio.
		MSetTransform *m = new MSetTransform();

		m->setTransform(_transform);

		emitMessage(m);

	} // setOrientation

	//---------------------------------------------------------

	Matrix3 CEntity::getOrientation() const
	{
		Matrix3 orientation;
		_transform.extract3x3Matrix(orientation);
		return orientation;

	} // getOrientation

	//---------------------------------------------------------

	void CEntity::setYaw(float yaw) 
	{
		Math::setYaw(yaw,_transform);

		// Avisamos a los componentes del cambio.
		MSetTransform *m = new MSetTransform();

		m->setTransform(_transform);

		emitMessage(m);

	} // setYaw

	//---------------------------------------------------------

	void CEntity::yaw(float yaw) 
	{
		Math::yaw(yaw,_transform);

		// Avisamos a los componentes del cambio.
		MSetTransform *m = new MSetTransform();

		m->setTransform(_transform);

		emitMessage(m);

	} // yaw

	//---------------------------------------------------------

	bool CEntity::addDeathListener(IDeathListener* listener)
	{
		MEntityDeathListener *m = new MEntityDeathListener();
		m->setAdd(true);
		m->setListener(listener);

		return emitMessage(m);
		
	} // addDeathListener

	//---------------------------------------------------------

	bool CEntity::removeDeathListener(IDeathListener* listener)
	{
		MEntityDeathListener *m = new MEntityDeathListener();
		m->setAdd(false);
		m->setListener(listener);

		return emitMessage(m);
		
	} // removeDeathListener

	//---------------------------------------------------------

} // namespace Logic
