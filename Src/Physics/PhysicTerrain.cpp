
#include "PhysicTerrain.h"
#include "PhysicGlobals.h"
#include "NxTriangleMeshDesc.h"
#include "NxStream.h"

#include "BaseSubsystems/Math.h"

#include "Tools/NxuStream2/NXU_Helper.h"
#include "Tools/NxuStream2/NXU_Schema.h"
#include "Tools/NxuStream2/NXU_cooking.h"
#include "Tools/NxuStream2/NXU_SchemaStream.h"
#include "Tools/NxuStream2/NXU_PhysicsExport.h"

/**
Namespace que contiene las clases nuevas relacionadas con la parte física. 
<p>
En este proyecto también existe código heredado que está fuera de este namespace.
El nombre de esas clases comienza por IPhysic o CPhysic.

@author Antonio Sánchez Ruiz-Granados
@date Octubre, 2010
*/
namespace Physics {

	class UserStream : public NxStream
	{
	public:
		UserStream(const char* filename, bool load);
		virtual                     ~UserStream();

		virtual     NxU8            readByte()                              const;
		virtual     NxU16           readWord()                              const;
		virtual     NxU32           readDword()                             const;
		virtual     float           readFloat()                             const;
		virtual     double          readDouble()                            const;
		virtual     void            readBuffer(void* buffer, NxU32 size)    const;

		virtual     NxStream&       storeByte(NxU8 b);
		virtual     NxStream&       storeWord(NxU16 w);
		virtual     NxStream&       storeDword(NxU32 dw);
		virtual     NxStream&       storeFloat(NxReal f);
		virtual     NxStream&       storeDouble(NxF64 f);
		virtual     NxStream&       storeBuffer(const void* buffer, NxU32 size);

		FILE*           fp;
	};


	UserStream::UserStream(const char* filename, bool load) : fp(NULL)
	{
		fp = fopen(filename, load ? "rb" : "wb");
	}

	UserStream::~UserStream()
	{
		if(fp)  fclose(fp);
	}

	// Loading API
	NxU8 UserStream::readByte() const
	{
		NxU8 b;
		size_t r = fread(&b, sizeof(NxU8), 1, fp);
		NX_ASSERT(r);
		return b;
	}

	NxU16 UserStream::readWord() const
	{
		NxU16 w;
		size_t r = fread(&w, sizeof(NxU16), 1, fp);
		NX_ASSERT(r);
		return w;
	}

	NxU32 UserStream::readDword() const
	{
		NxU32 dw;
		size_t r = fread(&dw, sizeof(NxU32), 1, fp);
		NX_ASSERT(r);
		return dw;
	}

	float UserStream::readFloat() const
	{
		float f;
		size_t r = fread(&f, sizeof(float), 1, fp);
		NX_ASSERT(r);
		return f;
	}

	double UserStream::readDouble() const
	{
		double f;
		size_t r = fread(&f, sizeof(double), 1, fp);
		NX_ASSERT(r);
		return f;
	}

	void UserStream::readBuffer(void* buffer, NxU32 size)   const
	{
		size_t w = fread(buffer, size, 1, fp);
		NX_ASSERT(w);
	}

	// Saving API
	NxStream& UserStream::storeByte(NxU8 b)
	{
		size_t w = fwrite(&b, sizeof(NxU8), 1, fp);
		NX_ASSERT(w);
		return *this;
	}

	NxStream& UserStream::storeWord(NxU16 w)
	{
		size_t ww = fwrite(&w, sizeof(NxU16), 1, fp);
		NX_ASSERT(ww);
		return *this;
	}

	NxStream& UserStream::storeDword(NxU32 dw)
	{
		size_t ww = fwrite(&dw, sizeof(NxU32), 1, fp);
		NX_ASSERT(ww);
		return *this;
	}

	NxStream& UserStream::storeFloat(NxReal f)
	{
		size_t ww = fwrite(&f, sizeof(NxReal), 1, fp);
		NX_ASSERT(ww);
		return *this;
	}

	NxStream& UserStream::storeDouble(NxF64 f)
	{
		size_t ww = fwrite(&f, sizeof(NxF64), 1, fp);
		NX_ASSERT(ww);
		return *this;
	}

	NxStream& UserStream::storeBuffer(const void* buffer, NxU32 size)
	{
		size_t w = fwrite(buffer, size, 1, fp);
		NX_ASSERT(w);
		return *this;
	}

	CPhysicTerrain::CPhysicTerrain(int nVertexCount, int nIndexCount, Vector3* aVertex, unsigned int* aIndex)
	{
		// Create an NxTriangleMeshDesc for our landscape physics.
		// - This code borrows from the AGEIA PhysX Documentation, NxTriangleMesh Class Reference
		NxTriangleMeshDesc meshDesc;
		meshDesc.numVertices = nVertexCount;
		meshDesc.numTriangles = nIndexCount / 3;
		meshDesc.pointStrideBytes = sizeof( Vector3 );
		meshDesc.triangleStrideBytes = 3*sizeof( unsigned int );
		meshDesc.points = aVertex;
		meshDesc.triangles = aIndex;
		meshDesc.flags = 0;
		meshDesc.heightFieldVerticalAxis = NX_Y;
		meshDesc.heightFieldVerticalExtent= -1000.0f;

		if ( !meshDesc.isValid() )
		{
			assert( false );
			return;
		}

		// Note:  cooking is a slow process and should generally be done offline.
		// As long as we've loaded all our levels with new meshes at least once before
		// building the installer, then these files should already be cooked and placed
		// in the media/physics data directory.  In which case, this function will not need to be
		// called, since our previous call to LoadCookedTriangleMeshFile will have loaded 
		// and returned the NxTriangleMesh data.
		bool bSuccess = NXU::CookTriangleMesh( meshDesc, UserStream( "media\\DamnedSunsetTerrain_Physic.xml", false ));
		//@TODO: Sacar el nombre del terreno del map.lua

		if ( !bSuccess )
		{
			// Not sure why this wouldn't succeed.  Can't write to file maybe?  Read-only directory?
			assert( false );
			return;
		}

		//NxTriangleMesh* pTriangleMesh = createTriangleMesh( SchemaStream( "media/DamnedSunsetTerrain_Physic.xml", false ) );
		//if ( !pTriangleMesh )
		//{
		//	assert( false );
		//	return;
		//}
	}

	CPhysicTerrain::~CPhysicTerrain()
	{

	}

}