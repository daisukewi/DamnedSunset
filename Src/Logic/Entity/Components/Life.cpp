/**
@file Life.cpp

Contiene la implementación del componente que controla la vida de una entidad.
 
@see Logic::CLife
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/

#include "Life.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Application/BaseApplication.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"

#include "assert.h"

//Mensajes
#include "Logic/Entity/Messages/SetBillboard.h"


#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::CLife() : IComponent(), _life(100.f) {

	}


	void generarBillboard(Ogre::BillboardSet* b, float porcentajeVida) {
		b->setMaterialName("barraVida");
		Ogre::Billboard* billboard = b->createBillboard(0,15,0);
		billboard->setDimensions(8,1);
		billboard->setTexcoordRect((1-porcentajeVida)/2.0f/*inicioX*/, 0.0f, 0.5f+(1.0f-porcentajeVida)/2.0f/*finX*/, 1.0f);
		
	}

	void actualizarBillboard(Ogre::BillboardSet* b, float porcentajeVida) {
		Ogre::Billboard* billboard = b->getBillboard(0);
		billboard->setTexcoordRect((1-porcentajeVida)/2.0f/*inicioX*/, 0.0f, 0.5f+(1.0f-porcentajeVida)/2.0f/*finX*/, 1.0f);
	}

	bool CLife::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("life"))
			_life = entityInfo->getFloatAttribute("life");
		if(entityInfo->hasAttribute("maxLife"))
			_maxLife = entityInfo->getFloatAttribute("maxLife");

		Logic::CSetBillboard *m = new Logic::CSetBillboard();
		m->_funcion = generarBillboard;
		m->setPorcetajeVida(_life/_maxLife);
		_entity->emitMessage(m);

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CLife::accept(const TMessage &message)
	{
		return message._type == Message::DAMAGED;

	} // accept
	
	//---------------------------------------------------------

	void CLife::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::DAMAGED:
			{
				// Disminuir la vida de la entidad
				_life -= message._float;
				printf("Herido\n");

				// Si han matado al jugador salir de la partida
				if ((_life <= 0) && (_entity->isPlayer())) {
					Application::CBaseApplication::getSingletonPtr()->setState("gameOver");
				}
				// @todo Poner la animación de herido.
				// @todo Si la vida es menor que 0 poner animación de morir.

				Logic::CSetBillboard *m = new Logic::CSetBillboard();
				m->_funcion = actualizarBillboard;
				m->setPorcetajeVida(_life/_maxLife);
				_entity->emitMessage(m);
			}
			break;
		}

	} // process


} // namespace Logic

