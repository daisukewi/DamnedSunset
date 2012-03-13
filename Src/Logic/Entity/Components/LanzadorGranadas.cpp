#include "LanzadorGranadas.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Logic/Entity/Messages/LanzarGranada.h"
#include "Logic/Entity/Messages/AplicarFuerza.h"

#include "Logic/Maps/EntityFactory.h"

namespace Logic 
{
	IMP_FACTORY(CLanzadorGranadas);
	//---------------------------------------------------------

	CLanzadorGranadas::CLanzadorGranadas() : IComponent() {
	}

	CLanzadorGranadas::~CLanzadorGranadas() {
		if (_billboard)
			delete _billboard;
	}

	bool CLanzadorGranadas::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_billboard = new Graphics::CBillboard(entity);
		if(entityInfo->hasAttribute("billboardLanzamientoMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardLanzamientoMaterial"));
		if(entityInfo->hasAttribute("billboardLanzamientoWith") && entityInfo->hasAttribute("billboardLanzamientoHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardLanzamientoWith"),entityInfo->getFloatAttribute("billboardLanzamientoHeight"));
		if(entityInfo->hasAttribute("billboardLanzamientoPosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardLanzamientoPosition");
			_billboard->setPosition(v.x,v.y,v.z);
		}
		_billboard->setPerpendicular();
		_billboard->setVisible(false);

		_estadoGranada = inactivo;

		return true;
	} // spawn


	bool CLanzadorGranadas::activate()
	{
		return true;
	} // activate
	//---------------------------------------------------------

	bool CLanzadorGranadas::accept(IMessage *message)
	{
		return IComponent::accept(message) || !message->getType().compare("MLanzarGranada");
	} // accept
	
	//---------------------------------------------------------

	void CLanzadorGranadas::process(IMessage *message)
	{
		IComponent::process(message);
		if (!message->getType().compare("MLanzarGranada"))
		{
			MLanzarGranada *m = static_cast <MLanzarGranada*> (message);

			if (m->getOrden() == mostrar)
			{
				_billboard->setVisible(true);
			} else if (m->getOrden() == ocultar)
			{
				_billboard->setVisible(false);
			}
			else if (m->getOrden() == lanzar)
			{
				//LANZAMOS LA GRANADA

				//Ocultamos el billboard del alcance de la granada
				_billboard->setVisible(false);

				//Posicion destino solo con X, Y.
				Vector2 posDestino = *m->getPosition();
				//Posicion destino solo con X, Y, Z.
				Vector3 posDestino3 = Vector3(posDestino.x,4,posDestino.y);

				//Lanzamos la granada a dicha posicion
				Map::CEntity * entityInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Granada");
				entityInfo->setName("granada" + rand() );

				//Ponemos la posicion de la granada en el mismo sitio que la entidad
				std::stringstream pos;
				pos << _entity->getPosition().x << ' ' << _entity->getPosition().y + 10 << ' ' << (_entity->getPosition().z);
				entityInfo->setAttribute("position", pos.str());

				////Ponemos la posicion de la granada en el destino
				//std::stringstream pos;
				//pos << posDestino3.x << ' ' << posDestino3.y << ' ' << posDestino3.z;
				//entityInfo->setAttribute("position", pos.str());

				Logic::CEntity *entityGranada = CEntityFactory::getSingletonPtr()->createEntity(entityInfo,Logic::CServer::getSingletonPtr()->getMap());


				//Calculamos el vector de direccion a la que tiene que ir la granada
				Vector3 v = Vector3(posDestino3.x - _entity->getPosition().x,0,posDestino3.z - _entity->getPosition().z);
				v.normalise();

				//Aplicamos la fuerza para lanzar la granada
				MAplicarFuerza * mf = new MAplicarFuerza();
				mf->setForce(v.x * 1000, 300, v.z*1000);
				mf->setPos(0,0,0);
				entityGranada->emitMessage(mf);

				entityGranada->setPosition(posDestino3);
			}
		}
	} // process


} // namespace Logic

