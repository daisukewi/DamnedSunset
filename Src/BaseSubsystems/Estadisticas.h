//---------------------------------------------------------------------------
// Estadisticas.h
//---------------------------------------------------------------------------

/**
@file Estadisticas.h


@see BaseSubsystems::IClock

@author Isaac Gallarzagoitia
@date Junio, 2012
*/



//#define ACTIVAR_ESTADISTICAS //Comentar/Descomentar esta linea para activar o desactivar las estadisticas



#ifndef __Estadisticas_H
	#define __Estadisticas_H

	#include <string>
	#include <iostream>

	#ifdef ACTIVAR_ESTADISTICAS
		//Definimos las funciones
		void BEGIN_STATS(std::string componentName);
		void END_STATS();
		void PRINT_STATS();
	#else
		//Definimos las funciones, para que las detecte pero que se reemplacen por nada
		#define BEGIN_STATS()
		#define END_STATS()
		#define PRINT_STATS()
	#endif
#endif