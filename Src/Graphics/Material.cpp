//---------------------------------------------------------------------------
// Material.cpp
//---------------------------------------------------------------------------

/**
@file Material.cpp

Contiene la implementación de la clase que representa un material
que se puede asignar a entidades gráficas.

@see Graphics::CMaterial

@author Daniel Flamenco
@date Marzo, 2012
*/

#include "Material.h"

#include <assert.h>

#include <OgreTextureManager.h>
#include <OgreMaterialManager.h>
#include <OgreTexture.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgreHardwarePixelBuffer.h>

namespace Graphics 
{
	using namespace Ogre;

	static int _nextID = 0;

	CMaterial::CMaterial(const Ogre::Vector3 &color, const float alpha)
	{
		std::stringstream texName;
		texName << "DynamicTexture_" << _nextID;

		// Create the texture
		TexturePtr texture = TextureManager::getSingleton().createManual(
			texName.str(), // name
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			TextureType::TEX_TYPE_2D,      // type
			256, 256,         // width & height
			0,                // number of mipmaps
			PixelFormat::PF_BYTE_BGRA,     // pixel format
			TextureUsage::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE); // usage;

		// Get the pixel buffer
		HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();

		// Lock the pixel buffer and get a pixel box
		pixelBuffer->lock(HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
		const PixelBox& pixelBox = pixelBuffer->getCurrentLock();

		uint8* pDest = static_cast<uint8*>(pixelBox.data);

		// Fill in some pixel data. This will give a semi-transparent blue,
		// but this is of course dependent on the chosen pixel format.
		for (size_t j = 0; j < 256; j++)
			for(size_t i = 0; i < 256; i++)
			{
				*pDest++ = color.z; // B
				*pDest++ = color.y; // G
				*pDest++ = color.x; // R
				*pDest++ = alpha; // A
			}

		// Unlock the pixel buffer
		pixelBuffer->unlock();

		std::stringstream matName;
		matName << "DynamicTextureMaterial_" << _nextID++;

		// Create a material using the texture
		_material = new Ogre::MaterialPtr(MaterialManager::getSingleton().create(
			matName.str(), // name
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));

		(*_material)->getTechnique(0)->getPass(0)->createTextureUnitState(texName.str());
		(*_material)->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);

		_isManual = true;

	} // CMaterial

	// ---------------------------------------------

	CMaterial::CMaterial(const std::string &name)
	{
		_material = new Ogre::MaterialPtr(MaterialManager::getSingleton().getByName(name));

		//assert(_material == NULL && "No se ha encontrado el material indicado.");

		_isManual = false;
		
	} // CMaterial

	// ---------------------------------------------

	CMaterial::~CMaterial()
	{

	} // ~CMaterial

	// ---------------------------------------------

	Ogre::MaterialPtr CMaterial::GetMaterial()
	{
		return *_material;

	} // GetMaterial


} // namespace Graphics