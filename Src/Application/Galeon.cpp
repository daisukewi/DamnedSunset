//---------------------------------------------------------------------------
// Galeon.cpp
//---------------------------------------------------------------------------

/**
@file Galeon.cpp
Contiene el punto de entrada principal del programa Galeon. Seg�n la configuraci�n
de las opciones del precompilador (_VISUALLEAKDETECTOR) se comprueba existencia de 
leaks. En funci�n de la configuraci�n y plataforma se usa un main o un WinMain.

@author David Llans�
@date Julio, 2010
*/

#ifdef _DEBUG
// VLD: Completa biblioteca para detectar leaks y donde se produjeron en modo de
// depuraci�n. Ralentiza moderadamente el lanzamiento de la aplicaci�n aunque no 
// en exceso su ejecuci�n. Si se desea anular la comprobaci�n basta con comentar 
// la siguiente l�nea.
//#define _VISUALLEAKDETECTOR

#ifdef _VISUALLEAKDETECTOR
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <vld.h> 
#endif // _VISUALLEAKDETECTOR

#endif // _DEBUG


#include "Application/GaleonApplication.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main(int argc, char **argv) 
{
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
#endif // (defined _DEBUG) || !(defined _WIN32)

	// Aqui llegamos a lo que verdaderamente importa. Lanzamos la aplicaci�n.
	{
		Application::CGaleonApplication miApp;

		if (miApp.init())
			miApp.run();

		miApp.release();
	}

	return 0;

} // main
