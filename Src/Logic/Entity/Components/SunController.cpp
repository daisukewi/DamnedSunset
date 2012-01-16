/**
@file SunController.cpp

Contiene la implementación del componente que controla el movimiento 
del sol y el control del la luz ambiental.
 
@see Logic::CSunController
@see Logic::IComponent

@author Daniel Flamenco
@date Enero, 2012
*/

#include "SunController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/StaticEntity.h"

#include <assert.h>

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreStaticGeometry.h>
#include <OgreColourValue.h>


namespace Logic 
{
	IMP_FACTORY(CSunController);
	
	//---------------------------------------------------------

	bool CSunController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if(entityInfo->hasAttribute("inclination"))
			_theta = Math::fromDegreesToRadians(entityInfo->getFloatAttribute("inclination"));

		_sphereRad = entity->getPosition().length();
		_phi = _entity->getPosition().angleBetween(Vector3(0, 0, _sphereRad)).valueRadians();

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSunController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSunController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSunController::accept(const TMessage &message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CSunController::process(const TMessage &message)
	{

	} // process
	
	//---------------------------------------------------------

	void CSunController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		Vector3 sunPos;
		_phi -= Math::fromDegreesToRadians(_speed * msecs * 0.001f);
		_phi = (_phi < 0.0f) ? Math::PI * 2.0f : _phi;

		sunPos.x = _sphereRad * Ogre::Math::Cos(_phi) * Ogre::Math::Sin(_theta);
		sunPos.y = _sphereRad * Ogre::Math::Sin(_phi) * Ogre::Math::Sin(_theta);
		sunPos.z = _sphereRad * Ogre::Math::Cos(_theta);

		_entity->setPosition(sunPos);

		Vector3 shadowDir = sunPos * -1.0f;
		Graphics::CScene* _sm = _entity->getMap()->getScene();
		_sm->setLightDirection(shadowDir.x, shadowDir.y, shadowDir.z);

		if (_phi > Math::fromDegreesToRadians(0.0f))
			_sm->getSceneMgr()->setAmbientLight(Ogre::ColourValue(.7f,.2f,.25f));
		if (_phi > Math::fromDegreesToRadians(20.0f))
			_sm->getSceneMgr()->setAmbientLight(Ogre::ColourValue(.9f,.9f,.9f));
		if (_phi > Math::fromDegreesToRadians(160.0f))
			_sm->getSceneMgr()->setAmbientLight(Ogre::ColourValue(.7f,.2f,.25f));
		if (_phi > Math::fromDegreesToRadians(180.0f))
			_sm->getSceneMgr()->setAmbientLight(Ogre::ColourValue(.1f,.1f,.1f));

	} // tick

} // namespace Logic

