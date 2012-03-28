/**
@file MapTile.h

Contiene la declaración de la clase que representa una celda del mapa leida 
del fichero del mapa.

@see Map::CTile

@author Alberto Plaza
@date Marzo, 2012
*/

#ifndef __Map_MapTile_H
#define __Map_MapTile_H

#include "BaseSubsystems/Math.h"
#include <string>

namespace Map
{
	/**
	Clase que representa una celda del mapa leida del fichero del mapa. Es
	simplemente una colección de pares <atributo,valor> más un string
	con el tipo de celda. 
	<p>
	La clase contiene métodos accesores que devuelven un atributo 
	convertido al tipo de datos requerido. El demandante es responsable 
	de solicitar el atributo por el método accesor adecuado, si el
	atributo no existe o no se puede convertir en el tipo de datos deseado
	salta una excepción. Acepta extraer strings, enteros, flotantes, 
	flotantes de doble precisión, booleanos o posiciones (éstas deben
	seguir el formato "(x,y,z)").

	@author Alberto Plaza
	@date Marzo, 2012
	*/
	class CTile
	{
	public:

		/** 
		Constructor de la clase.
		*/
		CTile() : _type("") {}

		/**
		Destructor.
		*/
		~CTile() {}

		/**
		Añade un atributo a la lista de atributos de la celda.

		@param attr Nombre del atributo a añadir.
		@param value Valor del atributo.
		*/
		void setAttribute(const std::string &attr, const std::string &value);

		/**
		Dice si se ha añadido un atributo.

		@param attr Nombre del atributo.
		@return true si contiene el atributo.
		*/
		bool hasAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido. Si no existe devuelve "".

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		const std::string &getStringAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido de tipo entero. Si no existe 
		salta una excepción.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		int getIntAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido de tipo flotante. Si no existe 
		salta una excepción.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		float getFloatAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido de tipo double. Si no existe 
		salta una excepción.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		double getDoubleAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido de tipo booleano. Si no existe 
		salta una excepción.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		bool getBoolAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido de tipo posición. Si no existe 
		salta una excepción. Las posiciones deben tener el formato "(x,y,z)".

		@param attr Nombre del atributo a recuperar.
		@param x Valor del eje X.
		@param y Valor del eje Y.
		@param z Valor del eje Z.
		*/
		const Vector3 getVector3Attribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente añadido de tipo tamaño IxJ. Si no existe 
		salta una excepción. Las posiciones deben tener el formato "(x,y)".

		@param attr Nombre del atributo a recuperar.
		@param x Valor del eje X.
		@param y Valor del eje Y.
		*/
		const Vector2 getVector2Attribute(const std::string &attr) const;

		/**
		Devuelve un string con el tipo de celda.

		@return Tipo de celda.
		*/
		const std::string &getType() const {return _type;}

		/**
		Establece el tipo de celda.

		@param type Tipo de celda.
		*/
		void setType(const std::string &type) {_type = type;}
		
		/**
		Tipo lista de CTile
		*/
		typedef std::map<std::string, std::string> TAttrList;

		/**
		Devuelve la lista de atributos de la celda.

		@return La lista de atributos de la celda.
		*/
		TAttrList getAttributes() {return _attributes;}
		
	protected:
		/**
		Atributos de la entidad.
		*/
		TAttrList _attributes;
		/**
		Tipo de la entidad.
		*/
		std::string _type;

	}; // class CTile

} // namespace Map

#endif // __Map_MapTile_H