//---------------------------------------------------------------------------
// Estadisticas.cpp
//---------------------------------------------------------------------------

/**
@file Estadisticas.h


@see BaseSubsystems::IClock

@author Isaac Gallarzagoitia
@date Junio, 2012
*/




#include "Estadisticas.h"

//Este cpp solo tiene sentido si esta definido ACTIVAR_ESTADISTICAS
#ifdef ACTIVAR_ESTADISTICAS
	#include <map>

	#include "BaseSubsystems/Server.h"

	#include <iostream>
	#include <algorithm>
	#include <vector>

	static std::map<std::string, int> _statistics;

	static unsigned long _time1;
	static std::string _name;

	static int borrar;

	// ---------------------------------------------------------------------------------------

	bool OrdenaPorInt(std::pair<std::string, int> x, std::pair<std::string, int> y) 
	{
		return x.second > y.second;
	}

	// ---------------------------------------------------------------------------------------

	void BEGIN_STATS(std::string componentName) {
		_time1 = BaseSubsystems::CServer::getSingletonPtr()->getActualTime();
		_name = componentName;
	};

	// ---------------------------------------------------------------------------------------

	void END_STATS()
	{
		if (!_statistics.count(_name) ) {
			_statistics[ _name ] = 0;
		}

		unsigned long time2 = BaseSubsystems::CServer::getSingletonPtr()->getActualTime();
		unsigned long diffTime = time2-_time1;

		_statistics[ _name ] = _statistics[ _name ] + diffTime;

	};

	// ---------------------------------------------------------------------------------------

	void PRINT_STATS()
	{
		std::string name;

		unsigned long totalTime = 0;
		//Mostramos el componente con mas tiempo


		std::map<std::string, int>::const_iterator it2;

		std::vector< std::pair<std::string, int> > vector;

		for( it2 = _statistics.begin();    it2!=_statistics.end(); ++it2)
		{
			unsigned long  time = (*it2).second;
			totalTime += time;
			vector.push_back(*it2);
		}


		sort(vector.begin(), vector.end(), OrdenaPorInt);


		std::vector< std::pair<std::string, int> >::const_iterator it3;
		int i = 0;
		float porcentaje = 0;

		if (borrar % 1000 == 0)
				std::cout << "----------------------------------------" << std::endl << std::endl;


		for( it3 = vector.begin();    it3 != vector.end() && i < 5; ++it3, ++i)
		{
			unsigned long  time = (*it3).second;
			if (totalTime > 0)
				porcentaje  = (float)time / totalTime * 100;

			name = (*it3).first;

			if (borrar % 1000 == 0)
				std::cout << "COMPONENTE: " << name << " " << porcentaje << "%" << std::endl;
		}
		++borrar;
	};
	
#endif