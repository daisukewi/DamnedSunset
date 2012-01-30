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
#include "Logic/Entity/Messages/Damaged.h"

#include "GUI/Server.h"
#include "GUI/InterfazController.h"


#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::CLife() : IComponent(), _life(100.f) {

	}


	void generarBillboard(Ogre::BillboardSet* b, float porcentajeVida) {
		//Tendria q haber 1 billboard creados, si no estan los creamos
		Ogre::Billboard* billboard;
		while (b->getNumBillboards() < 1 ) {
			billboard = b->createBillboard(0,13,0);
			billboard->setDimensions(0,0);
		}
		//El ultimo billboard es el q nos interesa: El '1'
		billboard = b->getBillboard(0);
		billboard->setDimensions(8,1);
		billboard->setTexcoordRect((0.2f-porcentajeVida*0.2)/2.0f/*inicioX*/, 0.0f, 0.1f+(0.2f-porcentajeVida*0.2f)/2.0f/*finX*/, 0.2f);
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

		Logic::CSetBillboard *m = new Logic::CSetBillboard();
		m->_funcion = generarBillboard;
		m->setPorcetajeVida(_life/_maxLife);
		_entity->emitMessage(m);

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CLife::accept(IMessage *message)
	{
		return (message->getType().compare("CDamaged") == 0);

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
				// @todo Poner la animación de herido.
				// @todo Si la vida es menor que 0 poner animación de morir.

				Logic::CSetBillboard *m = new Logic::CSetBillboard();
				m->_funcion = generarBillboard;
				m->setPorcetajeVida(_life/_maxLife);
				_entity->emitMessage(m);

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

	} // process


} // namespace Logic

