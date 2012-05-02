//*****************************************************************************
// Creacion  : 21/05/2005
// Contenido : Terreno fisico generado por un trimesh.
//
//*****************************************************************************
#ifndef _PHYSIC_TERRAIN_H_
#define _PHYSIC_TERRAIN_H_

#include	 "BaseSubsystems/Math.h"

/**
Namespace que contiene las clases nuevas relacionadas con la parte f�sica. 
<p>
En este proyecto tambi�n existe c�digo heredado que est� fuera de este namespace.
El nombre de esas clases comienza por IPhysic o CPhysic.

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/
namespace Physics {

	class CPhysicTerrain
	{

	public:

		CPhysicTerrain(int nVertexCount, int nIndexCount, Vector3* aVertex, unsigned int* aIndex);
		~CPhysicTerrain();

	};

}

#endif