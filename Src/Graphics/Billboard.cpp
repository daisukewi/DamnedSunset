/**
@file Billboard.cpp


@see Graphics::CCamera

@author Isaac
@date Febrero, 2012
*/

#include "Billboard.h"

#include "Scene.h"
#include "Server.h"

#include "Logic/Server.h"
#include "Logic/Maps/Map.h"
#include "Logic/Entity/Entity.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

#include "Logic/Entity/Messages/AttachBillboard.h"
#include <cassert>

namespace Graphics 
{
	CBillboard::CBillboard(Logic::CEntity * entity)
	{
		assert(entity);
		CScene * scene = entity->getMap()->getScene();
		_billboardset = scene->getSceneMgr()->createBillboardSet();

		Logic::MAttachBillboard * m = new Logic::MAttachBillboard();
		m->setBillboardset(this);
		entity->emitMessage(m);

		Ogre::Billboard* billboard;
		billboard = _billboardset->createBillboard(0.0f,0.0f,0.0f);
	}

	CBillboard::CBillboard(CScene * scene)
	{
		assert(scene);
		_billboardset = scene->getSceneMgr()->createBillboardSet();

		Ogre::Billboard* billboard;
		billboard = _billboardset->createBillboard(0.0f,0.0f,0.0f);
	}

	//--------------------------------------------------------

	CBillboard::~CBillboard() 
	{
		Graphics::CServer::getSingletonPtr()->getActiveScene()->removeBillboardset(_billboardset);
	}

	void CBillboard::attachEntity(Logic::CEntity * entity)
	{
		Logic::MAttachBillboard * m = new Logic::MAttachBillboard();
		m->setBillboardset(this);
		entity->emitMessage(m);
	}

	void CBillboard::setMaterial(std::string s)
	{
		_billboardset->setMaterialName(s);
	}

	void CBillboard::setDimensions(float x, float y)
	{
		_billboardset->getBillboard(0)->setDimensions(x,y);
	}
	void CBillboard::setPosition(float x, float y, float z)
	{
		_billboardset->getBillboard(0)->setPosition(x,y,z);
	}
	void CBillboard::setPosicionImagen(float x, float x2, float y, float y2)
	{
		_billboardset->getBillboard(0)->setTexcoordRect(x,x2,y,y2);
	}
	void CBillboard::setPerpendicular()
	{
		_billboardset->setBillboardType(Ogre::BBT_PERPENDICULAR_COMMON);
		_billboardset->setCommonDirection (Vector3::UNIT_Y);
		_billboardset->setCommonUpVector(Vector3::UNIT_Z);
	}
	void CBillboard::setVisible(bool b)
	{
		_billboardset->setVisible(b);
	}
}