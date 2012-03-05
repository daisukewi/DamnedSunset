//---------------------------------------------------------------------------
// Material.h
//---------------------------------------------------------------------------

/**
@file Material.h

Contiene la declaración de la clase que representa un material
que se puede asignar a entidades gráficas.

@see Graphics::CMaterial

@author Daniel Flamenco
@date Marzo, 2012
*/

#ifndef __Graphics_Material_H
#define __Graphics_Material_H

#include <string>

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class MaterialPtr;
	class Vector3;
}

namespace Graphics 
{
	/**
	Clase que representa un material con textura y color que se puede asignar
	a un objeto gráfico.
	<p>
	Oculta los detalles escabrosos del motor gráfico.
	
	@ingroup graphicsGroup

	@author Daniel Flamenco
	@date Marzo, 2012
	*/
	class CMaterial
	{
	public:

		/**
		Constructor de la clase con textura.

		@param name Nombre del archivo de textura a utilizar para
		crear el material.
		*/
		CMaterial(const std::string &name);

		/**
		Constructor de la clase con color.

		@param color Color en RGB que tendrá el material creado.
		@param alpha Valor de transparencia del color.
		@remarks Los valores del color y la transparencia tienen
		que comprenderse entre 0.0f y 1.0f.
		*/
		CMaterial(const Ogre::Vector3 &color, const float alpha);

		/**
		Destructor de la clase.
		*/
		virtual ~CMaterial();

		/**
		Devuelve el material de ogre para asignarselo a un objeto en escena.

		@returns Puntero que contiene la descripción del material de Ogre.
		*/
		Ogre::MaterialPtr GetMaterial();
	
	private:

		/**
		Puntero al material de ogre que tiene la textura solicitada.
		*/
		Ogre::MaterialPtr* _material;

		/**
		Atributo que indica si el material se ha creado dinámicamente
		o ha sido cargado de un fichero.
		*/
		bool _isManual;

	}; // class CMaterial

} // namespace Graphics

#endif // __Graphics_Material_H
