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
//declaración de la clase
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
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.
		<p>
		La implementación registrará al componente en algunos observers en 
		los que pueda necesitar estar registrado (como el cronómetro del 
		sistema, etc.).

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		<p>
		La implementación eliminará al componente de algunos observers en los 
		que pueda estar registrado (como el cronómetro del sistema, etc.).
		*/
		virtual void deactivate();

	protected:
		
		///**
		//Dirección física del archivo
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
