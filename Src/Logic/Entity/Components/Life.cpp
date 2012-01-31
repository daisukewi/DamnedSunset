/**
@file Life.cpp

Contiene la implementaci�n del componente que controla la vida de una entidad.
 
@see Logic::CLife
@see Logic::IComponent

@author David Llans�
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
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/SendBillboard.h"
#include "Logic/Entity/Messages/CreateBillboard.h"

#include "GUI/Server.h"
#include "GUI/InterfazController.h"


#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::CLife() : IComponent(), _life(100.f), _billboardSet(0) {

	}

	CLife::~CLife() {
		//delete _billboardSet;
		Graphics::CServer::getSingletonPtr()->getActiveScene()->removeBillboardset(_billboardSet);
	}


	void crearBillboard(Ogre::BillboardSet* b, float porcentajeVida) {
		//Tendria q haber 1 billboard creados, si no estan los creamos
		Ogre::Billboard* billboard;
		billboard = b->createBillboard(0.0f,13.0f,0.0f);
		billboard->setDimensions(8,1);
		billboard->setTexcoordRect((0.2f-porcentajeVida*0.2)/2.0f/*inicioX*/, 0.0f, 0.1f+(0.2f-porcentajeVida*0.2f)/2.0f/*finX*/, 0.2f);

		//billboard->setDimensions(10,10);
		//b->setTextureCoords(0,0,0);
		//b->setBillboardType(Ogre::BBT_ORIENTED_COMMON);
		//b->setCommonDirection(Vector3::UNIT_Z);
	}

	void updateBillboard(Ogre::BillboardSet* b, float porcentajeVida) {
		b->getBillboard(0)->setTexcoordRect((1.0f-porcentajeVida*1.0)/2.0f/*inicioX*/, 0.0f, 0.5f+(1.0f-porcentajeVida*0.5f)/2.0f/*finX*/, 1.0f);
	}

	//void actualizarBillboard(Ogre::BillboardSet* b, float porcentajeVida) {
	//	Ogre::Billboard* billboard = b->getBillboard(0);
	//	billboard->setTexcoordRect((1-porcentajeVida)/2.0f/*inicioX*/, 0.0f, 0.5f+(1.0f-porcentajeVida)/2.0f/*finX*/, 1.0f);
	//}

	bool CLife::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("life"))
			_life = entityInfo->getFloatAttribute("life");
		if(entityInfo->hasAttribute("maxLife"))
			_maxLife = entityInfo->getFloatAttribute("maxLife");

		_entity->emitMessage(new Logic::CCreateBillboard());

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CLife::accept(IMessage *message)
	{
		return (message->getType().compare("CDamaged") == 0) || !message->getType().compare("CSendBillboard");

	} // accept
	
	//---------------------------------------------------------

	void CLife::process(IMessage *message)
	{
		if (!message->getType().compare("CDamaged"))
		{
				CDamaged *md = static_cast <CDamaged*> (message);
				// Disminuir la vida de la entidad
				_life -= md->getHurt();
				
				if (_life <= 0) {
					_life = 0;
					// Si han matado al jugador salir de la partida
					if (_entity->isPlayer())
						Application::CBaseApplication::getSingletonPtr()->setState("gameOver");
				}
				// @todo Poner la animaci�n de herido.
				// @todo Si la vida es menor que 0 poner animaci�n de morir.

				updateBillboard(_billboardSet, _life/_maxLife);

				if (!_entity->getName().compare("Jack"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('1',_life/_maxLife);
				}
				if (!_entity->getName().compare("Erick"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('2',_life/_maxLife);
				}
				if (!_entity->getName().compare("Amor"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('3',_life/_maxLife);
				}
		}
		else if (!message->getType().compare("CSendBillboard"))
		{
			//Recibe el billboardset
			CSendBillboard *m = static_cast <CSendBillboard*> (message);
			_billboardSet = m->getBillboarSet();
			_billboardSet->setMaterialName("barraVida");
			crearBillboard(_billboardSet, _life/_maxLife);
		}

	} // process


} // namespace Logic

