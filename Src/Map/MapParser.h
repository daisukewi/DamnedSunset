/**
@file MapParser.h

Contiene la declaraci�n de la clase que encapsula el parseo de mapas.

@see Map::CMapParser

@author David Llans� Garc�a
@date Agosto, 2010
*/


#ifndef __MapParser_H
#define __MapParser_H

#include <string>
#include <list>

// Predeclaraci�n de clases.
namespace Map
{
	class CEntity;
	class CTile;
}


/**
Namespace relacionado con el parseo de mapas.

@author Alberto Plaza
@date Marzo, 2012
*/
namespace Map {

	/**
	Clase encargada de llamar al script que realiza el parseo y de
	almacenar de forma permanente la informaci�n de las entidades 
	le�das del fichero del mapa. Como el parseo se hace a trav�s de un
	script de lua, esta clase ser� simplemente llamada para ir a�adiendo
	las entidades.

	@author Alberto Plaza
	@date Marzo, 2012
	*/
	class CMapParser
	{
	public:

		/**
		Devuelve la �nica instancia de la clase CMapParser.
		
		@return �nica instancia de la clase CMapParser.
		*/
		static CMapParser* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la factor�a. Debe llamarse al finalizar la aplicaci�n.
		*/
		static void Release();

		/** 
		Parsea un fichero de mapa con un script de lua.
		
		@param mapFilename nombre del fichero con los datos del mapa.
		@param archFilename nombre del fichero con los datos de los arquetipos de las entidades.
		@return true si el parseo fue satisfactorio.
		*/
		bool parseFile(const std::string& mapFilename, const std::string& archFilename);

		/**
		Tipo lista de entidades de mapa.
		*/
		typedef std::list<Map::CEntity*> TEntityList;

		/**
		Tipo casilla del mapa.
		*/
		typedef Map::CTile* TTile;

		/**
		Tipo matriz de tiles del mapa.
		*/
		typedef TTile** TTileMatrix;

		/**
		Devuelve el listado de las entidades leidas del mapa.

		@return Entidades parseadas.
		*/
		const TEntityList getEntityList() {return _entityList;}

		/**
		Elimina todas las entidades que contenga la lista de entidades 
		parseadas.
		*/
		void releaseEntityList();

		/**
		Devuelve una entidad por nombre de la lista ya parseada de entidades.

		@param name Nombre de la entidad que queremos obtener.

		@return La entidad o null si no existe.
		*/
		CEntity *getEntity(const std::string &name);

		/**
		Inicializa el mapa de celdas y empieza el parseo del mismo.

		@param height Altura del mapa.
		@param width Anchura del mapa.
		*/
		void beginGrid(int height, int width);

		/**
		Establece una nueva celda cogiendo los atributos anteriormente
		parseados.

		@param name Nombre de la celda.
		@param y Coordenada y de la celda.
		@param x Coordenada x de la celda.
		*/
		void newTile(std::string &name, int y, int x);

		/**
		Empieza el parseo de una nueva entidad con el nombre proporcionado. Lo
		que hace es crear una nueva entidad en progreso y dejarla preparada
		para meterle atributos.

		@param name Nombre de la entidad nueva.
		*/
		void beginEntity(std::string &name);

		/**
		Establece el tipo de la entidad que se est� parseando actualmente.

		@param type Tipo de la entidad.
		*/
		void newAttribType(std::string &type);

		/**
		Establece el nombre de la entidad que se est� parseando actualmente.

		@param name Nombre de la entidad.
		*/
		void newAttribName(std::string &name);

		/**
		Establece un nuevo atributo en la entidad que se est� parseando actualmente.

		@param name Nombre del nuevo atributo.
		@param value Valor del nuevo atributo.
		*/
		void newAttrib(std::string &name, std::string &value);

		/**
		Termina el parseo de una nueva entidad. A�ade la entidad en progreso a la
		lista de entidades parseadas.
		*/
		void endEntity();

		/**
		Obtiene la informaci�n de una entidad parseada al cargar el mapa, ya
		est� en el mapa o en los arquetipos.

		@param name Nombre de la entidad de la que hay que recuperar la informaci�n.

		@return La informaci�n de la entidad recuperada.
		*/
		Map::CEntity *getEntityInfo(std::string name);

	private:

		/**
		�nica instancia de la clase.
		*/
		static CMapParser* _instance;

		/**
		Constructor.
		*/
		CMapParser();

		/**
		Destructor.
		*/
		~CMapParser();

		/**
		Flag que indica si estoy cargando los arquetipos o las entidaes.
		*/
		bool _archetypes;

		/**
		Entidad que se est� parseando actualmente.
		Este atributo ser� usado tanto para parsear los arquetipos
		como las entidades.
		*/
		CEntity *_entityInProgress;

		/**
		Lista de entidades parseada.
		*/
		TEntityList _entityList;

		/**
		Lista de los arquetipos de las entidades parseada.
		*/
		TEntityList _entityArchetypesList;

		/**
		Matriz de celdas del mapa parseado.
		*/
		TTileMatrix _tileMatrix;

	};

} // namespace Map

#endif // __MapParser_H
