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
		_altura = 0;
		//Crear el nodo de escena que contendrá la partícula
		std::stringstream auxString;
		auxString << name <<"_node";
		_sceneNode = Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr()->getRootSceneNode()->createChildSceneNode(auxString.str());
		_sceneNode->setPosition(point);
		_sceneNode->attachObject(_particleSystem);

	}

	CParticleEffect::CParticleEffect(std::string &name,std::string &effect, Vector3 &point,float altura)
	{
		_particleSystem = Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr()->createParticleSystem(name, effect);
		_altura = altura;
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
		if (_altura > 0)
			_sceneNode->setPosition(position.x, position.y + _altura,position.z);
		else
			_sceneNode->setPosition(position.x, position.y,position.z);
	}

	void CParticleEffect::setOrientation(Vector4 &orientation)
	{
		/*_orientation = orientation;

		_sceneNode->setOrientation(orientation.w,orientation.x,orientation.y,orientation.z);
		*/

		_sceneNode->yaw(Ogre::Radian(orientation.w));
	}

	void CParticleEffect::setStatic(bool statc){
		_static = statc;
	}

	bool CParticleEffect::getStatic(){
		return _static;
	}


}