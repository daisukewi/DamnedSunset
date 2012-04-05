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
#include "Logic/Entity/Messages/AplicarVelocidad.h"

#include "Logic/Maps/EntityFactory.h"

namespace Logic 
{
	IMP_FACTORY(CLanzadorGranadas);
	//---------------------------------------------------------
	static int numGranada = 0;

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

		if(entityInfo->hasAttribute("alcanceGranada"))
		{
			_maxAlcance = entityInfo->getFloatAttribute("alcanceGranada");
		}
		return true;
	} // spawn


	bool CLanzadorGranadas::activate()
	{
		return true;
	} // activate
	//---------------------------------------------------------

	bool CLanzadorGranadas::accept(IMessage *message)
	{
		return !message->getType().compare("MLanzarGranada");
	} // accept
	
	//---------------------------------------------------------

	void CLanzadorGranadas::process(IMessage *message)
	{
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

				std::stringstream sstm;
				sstm << "granada" << numGranada;

				entityInfo->setName(sstm.str());
				++numGranada;

				//Ponemos la posicion de la granada en el mismo sitio que la entidad
				std::stringstream pos;
				pos << _entity->getPosition().x << ' ' << _entity->getPosition().y + 15 << ' ' << (_entity->getPosition().z);
				entityInfo->setAttribute("position", pos.str());

				////Ponemos la posicion de la granada en el destino
				//std::stringstream pos;
				//pos << posDestino3.x << ' ' << posDestino3.y << ' ' << posDestino3.z;
				//entityInfo->setAttribute("position", pos.str());

				Logic::CEntity *entityGranada = CEntityFactory::getSingletonPtr()->createEntity(entityInfo,Logic::CServer::getSingletonPtr()->getMap());


				//Calculamos el vector de direccion a la que tiene que ir la granada
				Vector3 v = Vector3(posDestino3.x - _entity->getPosition().x,0,posDestino3.z - _entity->getPosition().z);
				v.normalise();


				float x = (_entity->getPosition().x - posDestino3.x);
				x = x * x;
				float z = (_entity->getPosition().z - posDestino3.z);
				z = z * z;
				//Distancia entre el punto en el que clickeamos y el jugador
				float distance = sqrt( x + z);

				if (distance > _maxAlcance)
					distance = _maxAlcance;
				//Volvemos a hacer la raiz cuadrada, para que se ajuste mejor la velocidad (no aplica tanta velocidad lejos, y no reduce tanto de cerca)
				distance = sqrt(distance) * 6;

				//Aplicamos la fuerza para lanzar la granada
				MAplicarVelocidad * mv = new MAplicarVelocidad();
				mv->setVelocity(v.x * distance, distance, v.z*distance);
				entityGranada->emitMessage(mv);

				entityGranada->setPosition(posDestino3);
			}
		}
	} // process


} // namespace Logic

