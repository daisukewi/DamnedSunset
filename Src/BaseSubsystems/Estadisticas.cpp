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

	#include <iostream>
	#include <algorithm>
	#include <vector>

	#include <ctime>

	struct STATS { 
		int totalTime; 
		unsigned int repeats; 
	};


	static std::map<std::string, STATS> _statistics;

	static unsigned long _time1;
	static std::string _name;

	static unsigned int _statistics_time = 0;

	static clock_t _startClock;

	void startTime()
	{
	  using namespace std;
	  _startClock = clock();
	}

	unsigned int timeElapsed()
	{
		clock_t end = clock();
		return double(end - _startClock) / CLOCKS_PER_SEC * 1000;
	}

	// ---------------------------------------------------------------------------------------

	bool OrdenaPorInt(std::pair<std::string, STATS> x, std::pair<std::string, STATS> y) 
	{
		return x.second.totalTime > y.second.totalTime;
	}

	// ---------------------------------------------------------------------------------------

	void BEGIN_STATS(std::string name) {
		_name = name;
		//_time1 = BaseSubsystems::CServer::getSingletonPtr()->getActualTime();
		startTime();
	};

	// ---------------------------------------------------------------------------------------

	void END_STATS()
	{

		unsigned int msecs = timeElapsed();
		//unsigned long time2 = BaseSubsystems::CServer::getSingletonPtr()->getActualTime();
		unsigned long diffTime = msecs;//time2 - _time1;
		CLOCKS_PER_SEC;

		//diffTime puede ser 0 si ha tardado menos de un milisegundo
		//if (diffTime)
		{
			if (!_statistics.count(_name) ) {
				_statistics[ _name ].repeats = 0;
				_statistics[ _name ].totalTime = 0;
			}
			++_statistics[ _name ].repeats;
			_statistics[ _name ].totalTime += diffTime;
		}
	};

	// ---------------------------------------------------------------------------------------

	void RESTART_STATS()
	{
		_statistics.clear();
	}

	#define MAX_PRINTS 5000 //No hara print si no han pasado estos msecs

	void PRINT_STATS(unsigned int msecs) 
	{
		_statistics_time += msecs;
		if (_statistics_time >= MAX_PRINTS)
		{
			_statistics_time = 0;
			PRINT_STATS();
		}
	}


	void PRINT_STATS()
	{
		std::string name;

		unsigned long totalTime = 0;
		unsigned long totalRepeats = 0;
		//Mostramos el componente con mas tiempo


		std::map<std::string, STATS>::const_iterator it2;

		std::vector< std::pair<std::string, STATS> > vector;

		//Pasamos el map a un vector para ordenarlo
		for( it2 = _statistics.begin();    it2 != _statistics.end(); ++it2)
		{
			totalTime += (*it2).second.totalTime;
			totalRepeats += (*it2).second.repeats;
			vector.push_back(*it2);
		}

		//Lo ordenamos
		sort(vector.begin(), vector.end(), OrdenaPorInt);


		std::vector< std::pair<std::string, STATS> >::const_iterator it3;
		int i = 0;
		float porcentaje = 0;
		float porcentajeRepeats = 0;
		std::cout << std::endl  << " ---   ESTADISTICAS   ---" << std::endl;


		for( it3 = vector.begin();    it3 != vector.end() && i < 10; ++it3, ++i)
		{
			unsigned long  time = (*it3).second.totalTime;
			unsigned long  repeats = (*it3).second.repeats;

			if (totalTime > 0)
				porcentaje  = (float)time / totalTime * 100;
			else
				porcentaje = 0;

			if (totalRepeats > 0)
				porcentajeRepeats  = (float)repeats / totalRepeats * 100;
			else
				porcentajeRepeats = 0;

			float avgTime = (float)time / repeats * 1000;

			name = (*it3).first;

			printf("%20s",name.c_str());

			printf("%s %5.2f","  Time:", porcentaje);
			printf("%s %5.2f","  Repeats:", porcentajeRepeats);
			printf("%s %7.2f msecs","  AvgTime:", avgTime);
			printf("\n");
		}
		std::cout << std::endl  << " --- FIN ESTADISTICAS ---" << std::endl;

		_statistics.clear();
	};
	
#endif