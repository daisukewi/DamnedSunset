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

#include "Graphics/Server.h"
#include "Graphics/Scene.h"


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

		_currentColor = Vector3( 0.20f, 0.20f, 0.38f );
		_lastColorChanged = 0;

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

	bool CSunController::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CSunController::process(IMessage *message)
	{
	} // process
	
	//---------------------------------------------------------

	void CSunController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		Vector3 sunPos;
		Vector3 nextColor;

		// Nuevo ángulo de altura del sol.
		_phi -= Math::fromDegreesToRadians(_speed * msecs * 0.001f);
		_phi = (_phi < 0.0f) ? Math::PI * 2.0f : _phi;

		// Calcular la nueva posición del sol con coordenadas esféricas.
		sunPos.x = _sphereRad * Math::Cos(_phi) * Math::Sin(_theta);
		sunPos.y = _sphereRad * Math::Sin(_phi) * Math::Sin(_theta);
		sunPos.z = _sphereRad * Math::Cos(_theta);
		_entity->setPosition(sunPos);

		Vector3 shadowDir = sunPos * -1.0f;
		//Graphics::CScene* _sm = _entity->getMap()->getScene();
		Graphics::CScene* sm = Graphics::CServer::getSingletonPtr()->getActiveScene();
		sm->setLightDirection(shadowDir.x, shadowDir.y, shadowDir.z);

		// Calculamos el nuevo color ambiental que debe generar el sol.
		if (_phi > Math::fromDegreesToRadians(0.0f))
			nextColor = Vector3( 0.86f, 0.26f, 0.20f );
		if (_phi > Math::fromDegreesToRadians(30.0f))
			nextColor = Vector3( 0.75f, 0.75f, 0.96f );
		if (_phi > Math::fromDegreesToRadians(150.0f))
			nextColor = Vector3( 0.65f, 0.63f, 0.60f );
		if (_phi > Math::fromDegreesToRadians(180.0f))
			nextColor = Vector3( 0.20f, 0.20f, 0.38f );

		// Si ha cambiado, mediante interpolación lineal lo ponemos
		if (nextColor != _currentColor)
		{
			_lastColorChanged += msecs;
			_lastColorChanged = (_lastColorChanged < 5000) ? _lastColorChanged : 5000;
			float amount = (float)_lastColorChanged / 5000.0f;

			_currentColor = Math::Lerp(_currentColor, nextColor, amount);
			sm->setAmbientLight(_currentColor.x, _currentColor.y, _currentColor.z);
		}
		else
			_lastColorChanged = 0;
		
	} // tick

} // namespace Logic

