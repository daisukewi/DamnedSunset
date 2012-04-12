/**
@file Sound.h

Contiene la declaración de la clase CSound que representa un sonido con todas sus variables.
Se usa desde el componente de sonido. No se usa en el servidor ni en el soundManager

@see Sonido::CSound

@author Alberto Ortega
@date Marzo, 2012
*/
#ifndef __Sound_H
#define __Sound_H

#include "BaseSubsystems/Math.h"
#include "Server.h"

// Declaración de la clase
namespace Sounds
{
	/**
	Contiene la información relativa a un sonido para poder acceder a ella desde el componente de sonido de 
	la entidad correspondiente.

	@ingroup Sound

	@author Luis Rojas
	@date Feb, 2012
	*/
	class CSound
	{

		private:

		/**
		Dirección física del archivo
		*/
		std::string _sound;

		/**
		Identificadores de los sonidos
		*/
		char *_id;

		/**
		Identificadores de los canales 
		*/
		int _idChannel;

		/**
		Sonido en bucle.
		*/
		bool _loop;

		/**
		Tipo del sonido, 2D o 3D
		*/
		Sounds::soundType _type;

		/**
		Posicion
		*/
		Vector3 _position;


	public:
		/**
		Constructor
		*/
		CSound(): _idChannel(0), _loop(false), _id(""),_position(Vector3(0,0,0)),_type(Sounds::Sound3D){};

		/**
		Destructor
		*/
		virtual ~CSound(){};

		/**
		Métodos get y set de cada variable
		*/

		void			setSound(std::string sound)	{_sound = sound;}
		std::string		getSound()						{return _sound;}

		void setId(char *id){_id = id;}
		char* getId(){return _id;}

		void setIdChannel(int idChannel){_idChannel = idChannel;}
		int getIdChannel() {return _idChannel;}

		void setLoop(bool loop){_loop = loop;}
		bool getLoop(){return _loop;}

		void setSoundType(Sounds::soundType soundType){_type = soundType;}
		Sounds::soundType getSoundType (){return _type;}

		void setPosition(Vector3 position){_position = position;}
		Vector3 getPosition(){return _position;}


	}; // class CSound

} // namespace Sounds

#endif // __Sound_H
