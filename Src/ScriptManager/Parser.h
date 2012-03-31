/**
@file Parser.h

Contiene la declaraci�n de la clase CParser que ser� la encargada
de servir de interfaz de comunicaci�n entre el parser de lua
y C++.

@author Alberto Plaza
@date Marzo, 2012
*/

#ifndef __ScriptManager_Parser_H
#define __ScriptManager_Parser_H

namespace ScriptManager
{
	/**
	Clase encargada de servir de interfaz de comunicaci�n entre el parser
	del script de lua y el c�digo C++. Se registrar� en lua para que sea
	accesible desde el script y ser� llamado por �l para hacer el parseo
	de las entidades.
	En lo que al parseo se refiere esta clase ser� la encargada de crear
	las entidades nuevas y pas�rselas al MapParser para que �ste las
	almacene de forma permanente.

	@author Alberto Plaza
	@date Marzo, 2012
	*/
	class CParser
	{
	public:

		/**
		Constructor.
		*/
		CParser();

		/**
		Destructor.
		*/
		~CParser();

		/**
		M�todo que se encarga de registrar la clase en el contexto de lua.
		Ser� llamado en el constructor y deber� ser implementado por las
		clases que implementen esta interfaz.
		*/
		static void registerClass();

		/**
		Empieza el parseo de las casillas del mapa.

		@param height Altura del mapa.
		@param width Anchura del mapa.
		*/
		void beginGrid(int height, int width);

		/**
		Establece una nueva celda.

		@param name Nombre de la nueva celda.
		@param y Coordenada y de la celda.
		@param x Coordenada x de la celda.
		*/
		void newTile(const char *name, int y, int x);

		/**
		Empieza el parseo de una nueva entidad con el nombre proporcionado.

		@param name Nombre de la entidad nueva.
		*/
		void beginEntity(const char *name);

		/**
		Establece un nuevo atributo en la entidad que se esta parseando actualmente.

		@param name Nombre del nuevo atributo.
		@param value valor del nuevo atributo.
		*/
		void newAttrib(const char *name, const char *value);

		/**
		Termina el parseo de una nueva entidad.
		*/
		void endEntity();
	
	}; // class CParser

} // namespace ScriptManager

#endif // __ScriptManager_Parser_H