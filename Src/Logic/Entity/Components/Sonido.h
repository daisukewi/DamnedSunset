/**
@file Sonido.h

@see Logic::CSonido
@see Logic::IComponent

*/
#ifndef __Logic_Sonido_H
#define __Logic_Sonido_H

#include "Logic/Entity/Component.h"
#include "Sound/Server.h"
#include "Sound/Sound.h"

using namespace std;




namespace Sounds{
	class CSound;
}
//declaraci�n de la clase
namespace Logic 
{
	class CSonido : public IComponent
	{
		DEC_FACTORY(CSonido);
	public:


		/**
		Constructor por defecto
		*/

		CSonido() : IComponent() {numSounds = 10; _path = "media/sounds/";}

		//CSonido() : IComponent(), _Sonido(""), _id(NULL), _position(0,0,0), _SoundType("2D"), _idChannel(0), _loop(false) {}

		/**
		Constructor por defecto, los sonidos los destruye el servidor.
		*/
		~CSonido(){}
		
		/**

		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		*/
		virtual bool accept(IMessage *message);

		/**
		*/
		virtual void process(IMessage *message);

		/**
		*/
		virtual void tick(unsigned int msecs);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.
		<p>
		La implementaci�n registrar� al componente en algunos observers en 
		los que pueda necesitar estar registrado (como el cron�metro del 
		sistema, etc.).

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		<p>
		La implementaci�n eliminar� al componente de algunos observers en los 
		que pueda estar registrado (como el cron�metro del sistema, etc.).
		*/
		virtual void deactivate();

	protected:
		
		///**
		//Direcci�n f�sica del archivo
		//*/
		//std::string _Sonido;

		///**
		//Tipo de Sonido, 3D, ambiental
		//*/
		//std::string _SoundType;

		///**
		//Identificadores de los sonidos
		//*/
		//char *_id;

		///**
		//Identificadores de los canales 
		//*/
		//int _idChannel;

		///**
		//Sonido en bucle.
		//*/
		//bool _loop;

		///**
		//Tipo del sonido, 2D o 3D
		//*/
		//Sounds::soundType _type;
		///**
		//Posicion
		//*/
		//Vector3 _position;
	
		//Total de sonidos que se pueden reproducir a la vez por entidad
		int numSounds;

		//Contador de sonidos
		int countSounds;

		//Lista de sonidos
		Sounds::CSound* _sound[10];

		/**
		Ruta de los sonidos
		*/
		std::string _path;


	}; // class CSonido

	REG_FACTORY(CSonido);

} // namespace Logic

#endif // __Logic_Sonido_H
