//---------------------------------------------------------------------------
// EntityDebug.h
//---------------------------------------------------------------------------

/**
@file EntityDebug.h

Contiene la declaraci�n de la clase que representa una entidad gr�fica de debug, necesaria para el pintado de la f�sica.

@see Graphics::CEntity

@author Alberto Ortega
@date Febrero, 2011
*/

#ifndef __Graphics_EntityDebug_H
#define __Graphics_EntityDebug_H

#include "BaseSubsystems/Math.h"
#include "Graphics\Entity.h"
#include "Graphics\Server.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class Entity;
	class SceneNode;
	class Material;
}

namespace Graphics 
{
	class CScene;
}

namespace Graphics 
{
	/**
	Clase que representa una entidad gr�fica. Esta entidada gr�fica tiene como modelo
	el prefab correspondiente a la entidada f�sica. En principio solo representa esferas o prismas.
	Las c�psulas ser�n representadas mediante un primas 
	Contiene una referencia a una entidad de Ogre y al Nodo que la contiene.
	Oculta los detalles escabrosos del motor gr�fico.
	<p>
	Al construir la clase solo se almacenan los atributos necesarios para
	la carga de las entidades de Ogre. Para cargar la entidad en Ogre y que 
	sea reenderizada, �sta debe a�adirse a una escenada de Ogre mediante el 
	m�todo attachToScene(). Solo la clase CScene puede invocar los m�todos 
	para a�adir o eliminar entidades de una escena y por tanto forzar su 
	carga o descarga en el motor de Ogre. Esto deriva de que en Ogre la carga
	de entidades se hace por las escenas, por lo que en nuestra arquitectura
	no permitimos entidades cargadas que no pertenezcan a ninguna escena.
	Al a�adir una entidad a una escena se fuerza su carga en Ogre invocando a 
	load.
	<p>
	Todas las modificaciones que se deseen hacer sobre los atributos de la
	entidad gr�fica (posici�n, orientaci�n, escala...) se deber�n hacer una 
	vez que las estructuras de Ogre han sido cargadas. De la misma manera 
	la entidad debe estar cargada para poder acceder a ellos.
	<p>
	Pueden implementarse clases derivadas de �stas, que permitan
	modelos con distintas caracter�sticas. Por ejemplo, �sta clase
	no permite especificar la animaci�n utilizada. No va a ser necesario
	especificarla ya que solo dibujar� prefabas sin animaci�n,.
	
	@ingroup graphicsGroup

	@author Alberto Ortega
	@date Febrero, 2011
	*/
	class CEntityDebug : public CEntity 
	{
	public:

		/**
		Constructor de la clase. (Cubo)

		@param name Nombre de la entidad.

		@param mesh Nombre del modelo que debe cargarse.
		
		@param prefab de ogre que va a ser dibujado. 

		@param dimensions dimensiones del prefab (cubo)

		@material meterial del prefab
		*/
		CEntityDebug(const std::string &name, const Graphics::TOgrePrefab &prefab,const Vector3 &dimensions, const std::string &material);

		/**
		Constructor de la clase. (Capsula)

		@param name Nombre de la entidad.

		@param mesh Nombre del modelo que debe cargarse.
		
		@param prefab de ogre que va a ser dibujado. 

		@param height altura de la c�psula

		@param radius radio de la c�psula

		@param material material del prefab
		*/
		CEntityDebug(const std::string &name, const Graphics::TOgrePrefab &prefab,const float &height, const float &radius, const std::string &material);


		//CEntity(const std::string &name, const 
		/**
		Destructor de la aplicaci�n.
		*/
		virtual ~CEntityDebug();

		/**
		Cambia la posici�n y orientaci�n de la entidad.

		@param transform Referencia a la matriz de transformaci�n con la 
		que debe posicionarse y orientarse la entidad.
		*/
		virtual void setTransform(const Matrix4 &transform);

		/**
		Cambia la posici�n de la entidad.

		@param position Nueva posici�n para el nodo que contiene la entidad 
		de Ogre.
		*/
		virtual void setPosition(const Vector3& position);

		/**
		Cambia la orientaci�n de la entidad.

		@param orientation Referencia a la matriz de rotaci�n con la que debe 
		orientarse la entidad.
		*/
		virtual void setOrientation(const Matrix3 &orientation);

		/**
		 Establece la propiedad visible de la entidad. Si
		 la entidad est� puesta invisible, no deber�a dibujarse.
		 La propiedad indica si la entidad debe dibujarse o no,
		 es decir, no est� relacionada con si la entidad est�
		 dentro del campo de visi�n de la c�mara o no.
		 <p>
		 El m�todo cambia la propiedad visible a todas las 
		 subentidades o nodos que contenga _entityNode.

		 @param visible Nuevo valor de la propiedad visible.
		 */
		virtual void setVisible(bool visible);

		/**
		 Devuelve el valor de la propiedad visible.
		 La propiedad indica si la entidad debe dibujarse o no,
		 es decir, no est� relacionada con si la entidad est�
		 dentro del campo de visi�n de la c�mara o no.

		 @return Cierto si la entidad es visible (est� activa 
		 para ser reenderizada).
		*/
		virtual const bool getVisible();

		/**
		 Escala la entidad.

		 @param scale Valores de la escala en los diferentes ejes.
		 */
		void setScale(const Vector3 &scale);

		/**
		 Escala la entidad.

		 @param scale Valor de la escala para los 3 ejes.
		 */
		void setScale(float scale);

		/**
		 Devuelve el valor de la escala de la entidad.

		 @return Valores de la escala en los diferentes ejes.
		*/
		const Vector3 &getScale();


		/**
		Asigna el valor del tama�o del prefab
		
		@param dimensions Vector3 que indica el tama�oa del prefab
		*/
		void setDimensions(const Vector3 &dimensions);

		/**
		Devuelve el valor del tama�o del prefab

		@return _dimensions
		*/
		Vector3 &getDimensions();


		/**
		Asigna el valor del radio de la c�psula

		@param radius indica el radio de la c�psula
		*/
		void setRadius(const float &radius);


		/**
		Devuelve el valor del radio de la c�psula

		@return _radius
		*/
		float &getRadius();

		/**
		Asigna el valor de la altura de la c�psula

		@param height valor de la altura de la c�psula
		*/
		void setHeight(const float &height);

		/**
		Devuelve el valor de la altura de la c�psula

		@return _height valor de la altura de la c�psula
		*/
		float &getHeight();

		/**
		Devuelve el metarial de Ogre
		*/
		std::string getMaterial(){return _material;}


		/**
		Devuelve la entidad de Ogre.

		@return puntero a la entidad de Ogre.
		*/
		virtual Ogre::Entity* getEntity() {return _entity;}

		virtual void attachBillboardSet(CBillboard* b);

	protected:

		// CScene es la �nica que puede a�adir o eliminar entidades de una 
		// escena y por tanto cargar o descargar entidades.
		// Por otro lado cada entidad debe pertenecer a una escena. Solo 
		// permitimos a la escena actualizar el estado.
		friend class CScene;

		/**
		A�ade la entidad al SceneManager pasado por par�metro. Si la entidad
		no est� cargada se fuerza su carga.

		@param sceneMgr Gestor de la escena de Ogre a la que se quiere a�adir
		la entidad.
		@return true si la entidad se pudo cargar y a�adir a la escena.
		*/
		virtual bool attachToScene(CScene *scene);

		/**
		Descarga una entidad de la escena en la que se encuentra cargada.

		@return true si la entidad se descargo y elimin� de la escena
		correctamente. Si la entidad no estaba cargada se devuelve false.
		*/
		virtual bool deattachFromScene();
		
		/**
		Carga la entidad gr�fica correspondiente al nombre _mesh. No hace 
		comprobaci�nes de si la entidad est� ya cargada o de si pertenece a
		otra escena. Esto se debe hacer de manera externa.

		@return true si la entidad pudo crear los objetos necesarios en Ogre
		o si la entidad ya estaba cargada.
		*/
		virtual bool load();

		/**
		Elimina las estructuras creadas en Ogre mediante load(). No hace 
		comprobaci�nes de si la entidad est� o no cargada o de si pertenece
		a una escena. Esto se debe hacer de manera externa.
		*/
		virtual void unload();
		
		/**
		Actualiza el estado de la entidad cada ciclo. En esta clase no se
		necesita actualizar el estado cada ciclo, pero en las hijas puede que
		si.
		
		@param secs N�mero de segundos transcurridos desde la �ltima llamada.
		*/
		virtual void tick(float secs);
		
		/**
		Nodo que contiene la entidad de Ogre.
		*/
		Ogre::SceneNode *_entityNode;
	
		/**
		Entidad de Ogre.
		*/
		Ogre::Entity *_entity;

		/**
		Quiz�s es mejor meter la clase CScene

		Controla todos los elementos Ogre de una escena. Su equivalente
		en la l�gica del juego ser�a el mapa o nivel. 
		*/
		CScene *_scene;

		/**
		Nombre de la entidad.
		*/
		std::string _name;

		/**
		Nombre del modelo de la entidad.
		*/
		std::string _mesh;

		/**
		Nombre del prefab de la entidada
		*/
		TOgrePrefab _prefab;

		/**
		Indica si la entidad ha sido cargada en el motor gr�fico.
		*/
		bool _loaded;

		/**
		Indica el tama�o del prefab de la entidad (no se usa para las c�psulas)
		*/
		Vector3 _dimensions;

		/**
		Indica el tama�o de las c�psulas
		*/
		float _radius;
		float _height;

		/**
		Indica el material del prefab
		*/
		//Ogre::Material *_material;

		/**
		Indica el material del prefab
		*/
		std::string _material;
		
	}; // class CEntity

} // namespace Graphics

#endif // __Graphics_EntityDebug_H