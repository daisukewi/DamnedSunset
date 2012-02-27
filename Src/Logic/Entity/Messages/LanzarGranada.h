
#ifndef __Logic_LanzarGranada_H
#define __Logic_LanzarGranada_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{
	enum OrdenGranada
	{
		mostrar = 0,
		ocultar = 1,
		lanzar = 2,
	};

	class MLanzarGranada : public IMessage
	{
	public:
		MLanzarGranada();
		~MLanzarGranada();
		void setPosition(Vector2 v) {_position = new Vector2(v.x,v.y);}
		Vector2* getPosition() {return _position;}
		OrdenGranada getOrden() {return _ordenGranada;}
		void setOrdenGranada(OrdenGranada o) {_ordenGranada = o;} 
	protected:
		Vector2 * _position;
		enum OrdenGranada _ordenGranada;
	};

} // namespace Logic

#endif