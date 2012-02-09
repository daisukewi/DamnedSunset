/**
@file Billboard.h

@see Graphics::CBillboard

@author Isaac
@date febrero, 2012
*/


#ifndef __Graphics_Billboard_H
#define __Graphics_Billboard_H

#include <string>

namespace Logic
{
	class CEntity;
}
namespace Ogre 
{
	class Entity;
	class SceneNode;
	class BillboardSet;
	class Vector3;
}

namespace Graphics 
{
	class CScene;
}

namespace Graphics 
{
	/**

	@ingroup graphicsGroup

	@author Isaac
	@date Febrero, 2012
	*/
	class CBillboard 
	{
	public:

		/**
		Constructor de la clase.
		*/
		CBillboard();

		/**
		Destructor de la aplicación.
		*/
		virtual ~CBillboard();
		
		void createBillBoard(Logic::CEntity * entity);
		void setMaterial(std::string s);
		void setDimensions(float x, float y);
		void setPosition(float x, float y, float z);
		void setPosicionImagen(float x, float x2, float y, float y2);
		void setDirection(Ogre::Vector3 v);
		void setVisible(bool b);
	protected:
		friend class CScene;
		

		Ogre::BillboardSet* _billboardset;
	};

}

#endif
