//---------------------------------------------------------------------------
// EntityDebug.cpp
//---------------------------------------------------------------------------

/**
@file EntityDebug.cpp

Contiene la implementación de la clase que representa una entidad gráfica de debug, necesaria para el pintado de la física

@see Graphics::CEntity

@author Alberto Ortega
@date Febrero, 2011
*/

#include "EntityDebug.h"
#include "Scene.h"

#include "BaseSubsystems/Server.h"
#include "BaseSubsystems/Math.h"

#include <assert.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

#include <OgreMaterial.h>

#include "Billboard.h"


namespace Graphics 
{
	CEntityDebug::CEntityDebug(const std::string &name, const Graphics::TOgrePrefab &prefab, const Vector3 &dimensions, const std::string &material)
		: _entity(0), _entityNode(0), _scene(0), _loaded(false)
	{
		_name = name;
		_prefab = prefab;
		_dimensions = dimensions;
		_height = 0.0;
		_radius = 0.0;
		
        
		//_material = new Ogre::Material(String& group, bool isManual = false, ManualResourceLoader* loader = 0);
		_material = material;

		_useRadiusHeight = false;
		
		
	} // CEntity

	CEntityDebug::CEntityDebug(const std::string &name, const Graphics::TOgrePrefab &prefab, const float &height, const float &radius, const std::string &material)
		: _entity(0), _entityNode(0), _scene(0), _loaded(false)
	{
		_name = name;
		_prefab = prefab;
		_height = height;
		_radius = radius;
		_material = material;

		_useRadiusHeight = true;
	} // CEntity

	//--------------------------------------------------------

	CEntityDebug::~CEntityDebug() 
	{
		assert(!_scene && "¡¡Para destruir una entidad esta no puede pertenecer a una escena!!");
		
	} // ~CEntity
	
	//--------------------------------------------------------
		
	bool CEntityDebug::attachToScene(CScene *scene)
	{
		assert(scene && "¡¡La entidad debe asociarse a una escena!!");
		// Si la entidad está cargada por otro gestor de escena.
		if(_loaded && (_scene != scene))
			return false;

		// Si no está cargada forzamos su carga.
		if (!_loaded)
		{
			_scene = scene;
			return load();
		}

		// Si ya estaba cargada en la escena se devuelve cierto.
		return true;
	} // attachToScene
	
	//--------------------------------------------------------
		
	bool CEntityDebug::deattachFromScene()
	{
		// Si la entidad no está cargada no se puede quitar de
		// una escena. Ya que no pertenecerá a ninguna.
		if(!_loaded)
			return false;
		// Si la entidad está cargada forzamos su descarga.
		else
		{
			assert(_scene && "¡¡La entidad debe estar asociada a una escena!!");
			unload();
			_scene = 0;
		}

		return true;

	} // deattachFromScene
	
	//--------------------------------------------------------
		
	bool CEntityDebug::load()
	{
		Ogre::SceneManager::PrefabType auxPrefab;
		Ogre::AxisAlignedBox auxBBox;
		try
		{
			//Creación de los prefabs
			
			
			if (_useRadiusHeight){
					

					auxPrefab = Ogre::SceneManager::PrefabType::PT_SPHERE;
	

			}else{

					auxPrefab = Ogre::SceneManager::PrefabType::PT_CUBE;
			}
			_entity = _scene->getSceneMgr()->createEntity(_name,auxPrefab);
			auxBBox = _entity->getBoundingBox();
			
			
		}
		catch(std::exception e)
		{
			return false;
		}


		_entityNode = _scene->getSceneMgr()->getRootSceneNode()->
								createChildSceneNode(_name + "_node");

		_entityNode->attachObject(_entity);
		_loaded = true;


		//Añadir el material
		_entity->setMaterialName(_material);

		//Reescalar el prefab 
		Ogre::Node *node = _entity->getParentNode();

		Vector3 vector = auxBBox.getSize();
		
		if (_useRadiusHeight){

			node->scale(_radius / vector.x * 2,
			_height / vector.y * 2,
			_radius / vector.z * 2);

		}else{

		node->scale(_dimensions.x / vector.x * 2,
			_dimensions.y / vector.y * 2,
			_dimensions.z / vector.z * 2);
		
		}
		
		return true;

	} // load
	
	//--------------------------------------------------------
		
	void CEntityDebug::unload()
	{
		if(_entityNode)
		{
			// desacoplamos la entidad de su nodo
			_entityNode->detachAllObjects();
			_scene->getSceneMgr()->destroySceneNode(_entityNode);
			_entityNode = 0;
		}
		if(_entity)
		{
			_scene->getSceneMgr()->destroyEntity(_entity);
			_entity = 0;
		}

	} // load

	//--------------------------------------------------------
		
	void CEntityDebug::tick(float secs)
	{
	} // tick
	
	//--------------------------------------------------------
		
	void CEntityDebug::setTransform(const Matrix4 &transform)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
		{
			_entityNode->setPosition(transform.getTrans());

			_entityNode->setOrientation(transform.extractQuaternion());

			//Hay que mover el dibujado de los prefabs para que encaje con la física
			if (_useRadiusHeight){
				_entityNode->setPosition(_entityNode->getPosition().x,
				_entityNode->getPosition().y + _height,
				_entityNode->getPosition().z);

			}else{
				/*Vector3 auxVector = _entityNode->convertWorldToLocalPosition(_entityNode->getPosition());
				auxVector.y +100;

				_entityNode->setPosition(_entityNode->convertLocalToWorldPosition(auxVector));*/
					_entityNode->setPosition(_entityNode->getPosition().x,
				_entityNode->getPosition().y +  _dimensions.y,
				_entityNode->getPosition().z);
			}
		}

	} // setTransform
	
	//--------------------------------------------------------
		
	void CEntityDebug::setOrientation(const Matrix3 &orientation)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setOrientation(orientation);

	} // setOrientation
	
	//--------------------------------------------------------
		
	void CEntityDebug::setVisible(bool visible)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setVisible(visible);

	} // setVisible
	
	//--------------------------------------------------------
		
	const bool CEntityDebug::getVisible()
	{
		if(_entityNode)
			return _entity->isVisible();

		throw new std::exception("La entidad no ha sido cargada");

	} // getPosition
	
	//--------------------------------------------------------
		
	void CEntityDebug::setPosition(const Vector3 &position)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode){
			_entityNode->setPosition(position);
			//Hay que mover el dibujado de los prefabs para que encaje con la física
			if (_useRadiusHeight){
				_entityNode->setPosition(_entityNode->getPosition().x,
				_entityNode->getPosition().y + _height,
				_entityNode->getPosition().z);

			}else{
				/*Vector3 auxVector = _entityNode->convertWorldToLocalPosition(_entityNode->getPosition());
				auxVector.y += _dimensions.y;

				_entityNode->setPosition(_entityNode->convertLocalToWorldPosition(auxVector));*/
					_entityNode->setPosition(_entityNode->getPosition().x,
				_entityNode->getPosition().y +  _dimensions.y,
				_entityNode->getPosition().z);
			}
		}
			

	} // setPosition
	
	//--------------------------------------------------------
		
	void CEntityDebug::setScale(const Vector3 &scale)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setScale(scale);

	} // setScale
	
	//--------------------------------------------------------
		
	void CEntityDebug::setScale(const float scale)
	{


	} // setScale

	void CEntityDebug::attachBillboardSet(CBillboard* b) 
	{
		_entityNode->attachObject(b->getBillboarset());

	}

	

} // namespace Graphics
