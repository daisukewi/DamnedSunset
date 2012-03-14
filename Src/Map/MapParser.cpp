/**
@file MapParser.cpp

Contiene la implementación de la clase que encapsula el parseo de mapas.

@see Map::CMapParser

@author Alberto Plaza
@date Marzo, 2012
*/

#include <cassert>

#include "MapEntity.h"
#include "MapParser.h"

#include "ScriptManager\Server.h"
#include "ScriptManager\Parser.h"

namespace Map {

	CMapParser* CMapParser::_instance = 0;

	//--------------------------------------------------------

	CMapParser::CMapParser() : _entityInProgress(0), _archetypes(false)
	{
		_instance = this;

	} // CMapParser

	//--------------------------------------------------------

	CMapParser::~CMapParser()
	{
		releaseEntityList();
		_instance = 0;

	} // ~CMapParser
	
	//--------------------------------------------------------

	bool CMapParser::Init()
	{
		assert(!_instance && "Segunda inicialización de Map::CMapParser no permitida!");

		new CMapParser();
		return true;

	} // Init

	//--------------------------------------------------------

	void CMapParser::Release()
	{
		assert(_instance && "Map::CMapParser no está inicializado!");
		if(_instance)
		{
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CMapParser::parseFile(const std::string& mapFilename, const std::string& archFilename)
	{
		// Cargo el script que contiene el mapa, que me han pasado como parámetro.
		if (!ScriptManager::CServer::getSingletonPtr()->loadExeScript(mapFilename.c_str()))
			return false;

		// Cargo el script que contiene los arquetipos de las entidades pasado como parámetro.
		if (!ScriptManager::CServer::getSingletonPtr()->loadExeScript(archFilename.c_str()))
			return false;

		// Cargo el script del parseador.
		if (!ScriptManager::CServer::getSingletonPtr()->loadExeScript("mapParser"))
			return false;

		// Registro en el contexto de lua el objeto que me va a servir de comunicación entre el script y el código C++.
		ScriptManager::CParser::registerClass();

		// Ejecuto la función del parseador para parsear los arquetipos de las entidades.
		_archetypes = true;
		if (!ScriptManager::CServer::getSingletonPtr()->executeScript("processMap(Archetype)"))
			return false;
		_archetypes = false;

		// Ejecuto la función del parseador para parsear las entidades del mapa.
		if (!ScriptManager::CServer::getSingletonPtr()->executeScript("processMap(Map)"))
			return false;

		return true;
		
	} // parseFile

	//--------------------------------------------------------
		
	void CMapParser::releaseEntityList()
	{
		// Libero la lista de entidades del mapa.
		while(!_entityList.empty())
			_entityList.pop_back();

		// Libero la lista de entidades de los arquetipos.
		while(!_entityArchetypesList.empty())
			_entityArchetypesList.pop_back();

		// Borro la entidad en progreso por si acaso se ha quedado con algún valor.
		// En teoría la entidad en progreso en este punto debería ser nula.
		if (_entityInProgress)
			delete _entityInProgress;

	} // releaseEntityList

	//--------------------------------------------------------

	CEntity *CMapParser::getEntity(const std::string &name)
	{
		// Busco la entidad en la lista de entidades.
		bool find = false;
		TEntityList::iterator it = _entityList.begin();
		while ((!find) && (it != _entityList.end()))
		{
			find = !strcmp((*it)->getType().c_str(), name.c_str());
			if (!find)
				it++;
		}

		if (find)
			return (*it);
		else
			return 0;
		
	} // getEntity

	//--------------------------------------------------------

	void CMapParser::beginEntity(std::string &name)
	{
		_entityInProgress = new CEntity(name);
		
	} // beginEntity

	//--------------------------------------------------------

	void CMapParser::newAttribType(std::string &type)
	{
		if (_entityInProgress)
			_entityInProgress->setType(type);
		
	} // newAttribType

	//--------------------------------------------------------

	void CMapParser::newAttribName(std::string &name)
	{
		if (_entityInProgress)
			_entityInProgress->setName(name);
		
	} // newAttribName

	//--------------------------------------------------------

	void CMapParser::newAttrib(std::string &name, std::string &value)
	{
		if (_entityInProgress)
			_entityInProgress->setAttribute(name, value);
		
	} // newAttrib

	//--------------------------------------------------------

	void CMapParser::endEntity()
	{
		// Compruebo si la entidad que cierro es de los arquetipos o no.
		if (_archetypes)
			_entityArchetypesList.push_back(_entityInProgress);
		else
		{
			// Si no es de los arquetipos procedo a ponerle los atributos de los arquetipos previamente cargados.

			// Me creo una entidad auxiliar.
			CEntity *entityMixed;

			// Busco la entidad en los arquetipos.
			bool find = false;
			TEntityList::iterator it = _entityArchetypesList.begin();
			while ((!find) && (it != _entityArchetypesList.end()))
			{
				find = !strcmp((*it)->getType().c_str(), _entityInProgress->getType().c_str());
				if (!find)
					it++;
			}

			// Una vez encontrada la entidad, creo la nueva con el nombre y el tipo de la entidad que estoy parseando.
			entityMixed = new CEntity(_entityInProgress->getName());
			entityMixed->setType(_entityInProgress->getType());

			// Si la entidad existía en los arquetipos la relleno primero con los arquetipos.
			if (it != _entityArchetypesList.end())
			{

				// Obtengo la lista de los atributos de la entidad de los arquetipos.
				CEntity::TAttrList attrListArch = (*it)->getAttributes();

				// Primero relleno la nueva entidad con todos los atributos de los arquetipos.
				CEntity::TAttrList::iterator itArch = attrListArch.begin();
				for (; itArch != attrListArch.end(); itArch++)
				{
					entityMixed->setAttribute(itArch->first, itArch->second);
				}

			}

			// Obtengo la lista de los atributos de la entidad que estoy parseando.
			CEntity::TAttrList attrListEnt = _entityInProgress->getAttributes();

			// Finalemente sobreescribo los atributos de los arquetipos con los leídos del mapa.
			CEntity::TAttrList::iterator itEnt = attrListEnt.begin();
			for (; itEnt != attrListEnt.end(); itEnt++)
			{
				entityMixed->setAttribute(itEnt->first, itEnt->second);
			}

			// Meto la entidad construida en la lista final de entidades.
			_entityList.push_back(entityMixed);

			// Destruyo la entidad que estoy parseando porque no me la he guardado y no me interesa guardármela.
			delete _entityInProgress;
		}

		_entityInProgress = 0;
		
	} // endEntity

	//--------------------------------------------------------

	Map::CEntity *CMapParser::getEntityInfo(std::string name)
	{
		// Me declaro las variables auxiliares.
		bool find = false;
		TEntityList::iterator it;

		// Primero busco la entidad en la lista de entidades del mapa.
		find = false;
		it = _entityList.begin();
		while ((!find) && (it != _entityList.end()))
		{
			find = !strcmp((*it)->getType().c_str(), name.c_str());
			if (!find)
				it++;
		}

		// Si le he encontrado la devuelvo.
		if (find)
			return (*it);

		// Si no la he encontrado la busco en los arquetipos.
		find = false;
		it = _entityArchetypesList.begin();
		while ((!find) && (it != _entityArchetypesList.end()))
		{
			find = !strcmp((*it)->getType().c_str(), name.c_str());
			if (!find)
				it++;
		}

		// Si la he encontrado en los arquetipos la devuelvo, sino devuelvo 0.
		if (find)
			return (*it);
		else
			return 0;

	} // getEntityInfo

	//--------------------------------------------------------

} // namespace Map
