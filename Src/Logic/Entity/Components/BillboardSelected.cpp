#include "BillboardSelected.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Messages/SendBillboard.h"
#include "Logic/Entity/Messages/CreateBillboard.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{
	IMP_FACTORY(CBillboardSelected);
	
	//---------------------------------------------------------

	CBillboardSelected::CBillboardSelected() : IComponent() {
		_billboardSet = NULL;
		peticionCrearBillboardEnviada = false;
	}

	CBillboardSelected::~CBillboardSelected() {
		if (_billboardSet)
			Graphics::CServer::getSingletonPtr()->getActiveScene()->removeBillboardset(_billboardSet);
	}

	bool CBillboardSelected::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		return true;

	} // spawn

	//---------------------------------------------------------

	bool CBillboardSelected::accept(IMessage *message)
	{
		return !message->getType().compare("MIsSelectable") || !message->getType().compare("MSendBillboard");
	} // accept
	
	//---------------------------------------------------------

	void crearBillboardSelected(Ogre::BillboardSet* b) {
		b->setMaterialName("circuloSeleccion");
		//Tendria q haber 1 billboard creados, si no estan los creamos
		Ogre::Billboard* billboard;
		billboard = b->createBillboard(0.0f,0.0f,0.0f);

		billboard->setDimensions(10,10);
		b->setBillboardType(Ogre::BBT_ORIENTED_COMMON);
		b->setCommonDirection(Vector3::UNIT_Z);
	}

	void CBillboardSelected::process(IMessage *message)
	{
		if (!message->getType().compare("MIsSelectable"))
		{
			//Peticion al grafics para crear el billboardset
			if (!_billboardSet) {
				//Solo lo creamos si no esta ya creado
				if (!peticionCrearBillboardEnviada) //Y si no se ha pedido ya que se cree
				{ 
					MCreateBillboard * m = new Logic::MCreateBillboard();
					m->setTipoBillboard("CBillboardSelected");
					_entity->emitMessage(m);
					peticionCrearBillboardEnviada = true;
				}

			} else {
				//El billboard ya esta creado, lo hacemos visible
				_billboardSet->setVisible(true);
			}

		} else if (!message->getType().compare("MSendBillboard"))
		{
			//Recibe el billboardset
			MSendBillboard *m = static_cast <MSendBillboard*> (message);
			if (m->getTipoBillboard() == "CBillboardSelected") {
				assert(!_billboardSet); //El billboardset no deberia de estar creado
				_billboardSet = m->getBillboarSet();
				crearBillboardSelected(_billboardSet);
			}

		}

	} // process


} // namespace Logic

