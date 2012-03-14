/**
@file MapParser.h

Contiene la declaración de la clase que encapsula el parseo de mapas.

@see Map::CMapParser

@author David Llansó García
@date Agosto, 2010
*/


#ifndef __MapParser_H
#define __MapParser_H

#include <string>
#include <list>

// Predeclaración de clases.
namespace Map
{
	class CEntity;
}


/**
Namespace relacionado con el parseo de mapas.

@author Alberto Plaza
@date Marzo, 2012
*/
namespace Map {

	/**
	Clase encargada de llamar al script que realiza el parseo y de
	almacenar de forma permanente la información de las entidades 
	leídas del fichero del mapa. Como el parseo se hace a través de un
	script de lua, esta clase será simplemente llamada para ir añadiendo
	las entidades.

	@author Alberto Plaza
	@date Marzo, 2012
	*/
	class CMapParser
	{
	public:

		/**
		Devuelve la única instancia de la clase CMapParser.
		
		@return Única instancia de la clase CMapParser.
		*/
		static CMapParser* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la factoría. Debe llamarse al finalizar la aplicación.
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
		Empieza el parseo de una nueva entidad con el nombre proporcionado. Lo
		que hace es crear una nueva entidad en progreso y dejarla preparada
		para meterle atributos.

		@param name Nombre de la entidad nueva.
		*/
		void beginEntity(std::string &name);

		/**
		Establece el tipo de la entidad que se está parseando actualmente.

		@param type Tipo de la entidad.
		*/
		void newAttribType(std::string &type);

		/**
		Establece el nombre de la entidad que se está parseando actualmente.

		@param name Nombre de la entidad.
		*/
		void newAttribName(std::string &name);

		/**
		Establece un nuevo atributo en la entidad que se está parseando actualmente.

		@param name Nombre del nuevo atributo.
		@param value Valor del nuevo atributo.
		*/
		void newAttrib(std::string &name, std::string &value);

		/**
		Termina el parseo de una nueva entidad. Añade la entidad en progreso a la
		lista de entidades parseadas.
		*/
		void endEntity();

		static void CMapParser::releaseEntityList(TEntityList list);

		/**
		Obtiene la información de una entidad parseada al cargar el mapa, ya
		esté en el mapa o en los arquetipos.

		@param name Nombre de la entidad de la que hay que recuperar la información.

		@return La información de la entidad recuperada.
		*/
		Map::CEntity *getEntityInfo(std::string name);

	private:

		/**
		Única instancia de la clase.
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
		Entidad que se está parseando actualmente.
		Este atributo será usado tanto para parsear los arquetipos
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

	};

} // namespace Map

#endif // __MapParser_H
