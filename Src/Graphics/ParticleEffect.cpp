/**
@file ParticleEffect.cpp


@author Alberto
@date Septiembre, 2012
*/

#include "ParticleEffect.h"

#include "Scene.h"
#include "Server.h"

#include "Logic/Server.h"
#include "Logic/Maps/Map.h"
#include "Logic/Entity/Entity.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "OgreSceneNode.h"

#include "BaseSubsystems/Math.h"

#include "OgreParticleSystem.h"

#include <cassert>

namespace Graphics 
{
	CParticleEffect::CParticleEffect(std::string &name,std::string &effect, Vector3 &point)
	{
		_particleSystem = Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr()->createParticleSystem(name, effect);
		
		//Crear el nodo de escena que contendrá la partícula
		std::stringstream auxString;
		auxString << name <<"_node";
		_sceneNode = Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr()->getRootSceneNode()->createChildSceneNode(auxString.str());
		_sceneNode->setPosition(point);
		_sceneNode->attachObject(_particleSystem);

	}


	//--------------------------------------------------------

	CParticleEffect::~CParticleEffect() 
	{
		_sceneNode->detachAllObjects();
		Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr()->destroySceneNode(_sceneNode);
		_sceneNode = 0;

		Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr()->destroyParticleSystem(_particleSystem);
		_particleSystem = 0;
	}


	void CParticleEffect::setPosition(Vector3 &position)
	{
		_sceneNode->setPosition(position);
	}

}