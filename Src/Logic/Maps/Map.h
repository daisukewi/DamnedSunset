/**
@file Map.h

Contiene la declaraci�n de la clase CMap, Un mapa l�gico.

@see Logic::Map

@author David Llans�
@date Agosto, 2010
*/
#ifndef __Logic_Map_H
#define __Logic_Map_H

#include <map>
#include "EntityID.h"
#include "Map/MapParser.h"
#include "Logic/Entity/Entity.h"
#include "GridMap.h"
#include "GridTile.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CEntity;
	class CTerrainTile;
}

namespace Graphics 
{
	class CScene;
	class CTerrain;
}

// Declaraci�n de la clase
namespace Logic
{

	/**
	Clase que representa un mapa l�gico.
	<p>
	Esta clase se encarga de almacenar todas las entidades del mapa, tanto 
	aquellas que tienen representaci�n gr�fica y se ven como entidades
	puramente l�gicas. Gestiona la activaci�n y desactivaci�n de �stas y
	tiene tambi�n m�todos para buscar entidades, tanto por su nombre como 
	por su tipo y por su identificador.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CMap
	{
	public:


		/**
		Tipo tabla de entidades de mapa.
		*/
		typedef std::map<TEntityID,CEntity*> TEntityMap;


		/**
		M�todo factor�a que carga un mapa de fichero. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param mapFilename Nombre del archivo de mapa a cargar.
		@param archFilename Nombre del archivo de arquetipos de las entidades a cargar.
		@return Mapa generado.
		*/
		static CMap *createMapFromFile(const std::string &mapFilename, const std::string &archFilename);

		/**
		Constructor.

		@param name Nombre que se le da a este mapa.
		*/
		CMap (const std::string &name);

		/**
		Destructor.
		*/
		~CMap();
		
		/**
		Activa el mapa. Invocar� al m�todo activate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		 
		@return Devuelve true al invocador si todas las entidades se
		activaron sin problemas.
		*/
		bool activate();

		/**
		Desactiva el mapa. Invocar� al m�todo deactivate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		*/
		void deactivate();

		/**
		Funci�n llamada en cada frame para que se realicen las funciones
		de actualizaci�n adecuadas.
		<p>
		Llamar� a los m�todos tick() de todas las entidades.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		void tick(unsigned int msecs);

		/**
		A�ade una nueva entidad al mapa. Si la entidad ya estaba incluida
		no se hace nada.

		@param entity Entidad a a�adir.
		*/
		void addEntity(CEntity *entity);

		/**
		Elimina una entidad del mapa. Si la entidad no estaba incluida
		no se hace nada. La funci�n desactiva previamente la entidad si
		�sta se encontraba activa.

		@note El mapa no se hace responsable de eliminar (con delete) la
		entidad.

		@param entity Entidad a eliminar.
		*/
		void removeEntity(CEntity *entity);

		/**
		Elimina y destruye todas las entidades del mapa dejando la lista 
		de entidades vac�a.
		*/
		void destroyAllEntities();

		/**
		Recupera una entidad del mapa a partir de su ID.

		@param entityID ID de la entidad a recuperar.
		@return Entidad con el ID pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByID(TEntityID entityID);

		/**
		Recupera una entidad del mapa a partir de su nombre.

		@param name nombre de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. �til si se tienen varias entidades con el mismo
		nombre y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByName(const std::string &name, CEntity *start = 0);

		/**
		Recupera una entidad del mapa a partir de su tipo.

		@param type nombre del tipo de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. �til si se tienen varias entidades del mismo tipo
		y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByType(const std::string &type, CEntity *start = 0);
		
		/*
		Recupera una entidad del mapa a partir de su tag

		@param tag tag de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. �til si se tienen varias entidades del mismo tipo
		y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByTag(const std::string &tag, CEntity *start = 0);

		/**
		Crea un nuevo terreno en el mapa con las dimensiones pasadas
		como par�metro.

		@param mapSize tama�o del mapa donde se generar� el terreno (M x N)
		*/
		void createTerrain(int mapSize);

		/**
		A�ade un nuevo tipo de terreno a la lista de tiles de terreno del mapa.

		@param terrain_tile nuevo tipo de terrenopara a�adir a la lista.
		*/
		void addTerrainTile (CTerrainTile* terrain_tile);

		/**
		Devuelve la escena gr�fica correspondiente a este mapa.

		@return Escena con las entidades gr�ficas.
		*/
		Graphics::CScene *getScene() { return _scene; }

		/**
		Devuelve la escena gr�fica correspondiente a este mapa.

		@return Escena con las entidades gr�ficas.
		*/
		CGridMap *getGridMap() { return _gridMap; }

	
		/**
		Envia un mensaje a todas las entidades excepto a la que se pase por par�metro

		@param mensaje a enviar
		@param entidad a la que no se quiere que se env�e el mensaje. Normalmente la misma que lo env�a.
		*/
		void sendMessageAll(IMessage *message, Logic::CEntity *entity);


		/**
		Devuelve el map de las entidades

		@return entityMap
		*/
		TEntityMap* getEntityMap(){ return &_entityMap; }

	private:

		/**
		tabla con las entidades del mapa localizadas por su ID.
		*/
		TEntityMap _entityMap;

		/**
		Nombre del mapa.
		*/
		std::string _name;

		/**
		Escena gr�fica donde se encontrar�n las representaciones gr�ficas de
		las entidades.
		*/
		Graphics::CScene* _scene;

		/**
		Grid de tiles donde se almacena el mapa l�gico del escenario.
		*/
		CGridMap* _gridMap;

		/**
		Lista con los diferentes terrenos que contiene el mapa.
		*/
		std::list<CTerrainTile*>* _terrainList;

	}; // class CMap

} // namespace Logic

#endif // __Logic_Map_H
