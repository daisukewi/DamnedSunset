/**
@file PhysicCharacter.h

Contiene la declaraci�n del componente que se utiliza para representar jugadores y enemigos en
el mundo f�sico usando character controllers.

@see Logic::CPhysicCharacter
@see Logic::CPhysicEntity

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/
#ifndef __Logic_PhysicCharacter_H
#define __Logic_PhysicCharacter_H

#include "PhysicEntity.h"

// Los componentes se definen dentro del namespace Logica
namespace Logic 
{
	/**
	Componente que se utiliza para representar jugadores y enemigos en el mundo f�sico usando 
	character controllers.
	<p>
	Este componente recibe mensajes de tipo AVATAR_WALK para mover el controller.
	<p>
	La implementaci�n de esta clase tambi�n gestiona las diferencias que existen entre el
	sistema de coordenadas local (SCL) l�gico y f�sico. El SCL que usa la l�gica para cada 
	entidad tiene su origen en la parte inferior de la entidad (los pies), mientras que 
	PhysX coloca por defecto el origen del SCL en medio de la entidad. En las entidades 
	f�sicas simples, podemos unificar los dos SCL definiendo una sencilla traslaci�n en la 
	descripci�n del modelo, pero la descripci�n de los character controllers no ofrece esa
	posibilidad. La conclusi�n es que debemos realizar una traslaci�n en el eje Y para 
	convertir entre coordenadas l�gicas y coordenadas f�sicas.
	
    @ingroup logicGroup

	@author Antonio S�nchez Ruiz-Granados
	@date Octubre, 2010
	*/
	class CPhysicCharacter : public CPhysicEntity
	{
		DEC_FACTORY(CPhysicCharacter);
	public:

		/**
		Constructor por defecto.
		*/
		CPhysicCharacter();

		/**
		Destructor (virtual).
		*/
		virtual ~CPhysicCharacter();

		/**
		Este componente s�lo acepta mensajes de tipo AVATAR_WALK.
		*/
		virtual bool accept(const TMessage &message);
		
		/**
		Si se recibe un mensaje de tipo AVATAR_WALK, se almacena su vector de 
		desplazamiento para posteriormente mover el character controller en el tick.
		De este moto, si en un ciclo se reciben varios mensaje de tipo SET_TRANSFORM 
		s�lo tendr� efecto el �ltimo que se reciba.
		*/
		virtual void process(const TMessage &message);

		/**
		Este m�todo se invoca en cada ciclo de la simulaci�n y hace lo siguiente:
		<ul>
		<li>Actualiza la posici�n de la entidad l�gica usando la informaci�n que proporciona
		el motor de f�sica.</li>
		
		<li>Mueve el character controller de acuerdo al �ltimo mensaje AVATAR_WALK recibido.</li>
		</ul>
		<p>
		Necesitamos sobreescribir el m�todo de la clase padre ya que los character controllers
		no tienen orientaci�n, s�lo posici�n. Adem�s debemos aplicar una traslaci�n al vector 
		de posici�n que obtenemos de PhysX ya que la l�gica y la f�sica	usan distintos or�genes 
		para los sistemas de coordenadas locales a la entidad (en los pies / en el centro de la 
		entidad).
		*/
		virtual void tick(unsigned int msecs);

	protected:

		/**
		Debemos sobreescribir este m�todo de la clase padre para aplicar una traslaci�n
		al character controller una vez creado (conversi�n entre coordenadas l�gicas y f�sicas).
		*/
		virtual IPhysicObj* createPhysicEntity(const Map::CEntity *entityInfo);

		/**
		Creamos un modelo para describir el character controller f�sico.
		 */
		virtual IPhysicModel* createPhysicModel(const Map::CEntity *entityInfo);

	private:
		/**
		Tranforma posiciones l�gicas a posiciones f�sicas.
		 */
		Vector3 fromLogicToPhysics(const Vector3 &v) { return Vector3(v.x, v.y + _offsetY, v.z); };

		/**
		Transforma posiciones f�sicas a posiciones l�gicas.
		*/
		Vector3 fromPhysicsToLogic(const Vector3 &v) { return Vector3(v.x, v.y - _offsetY, v.z); };

		/**
		Desplazamiento en el eje Y para transformar entre coordenadas l�gicas y coordenadas
		f�sicas.
		 */
		float _offsetY;

		/**
		Vector de desplazamiento recibido en el �ltimo mensaje de tipo AVATAR_WALK. 
		*/
		Vector3 _movement;

		/**
		Indica si el character controller esta apoyado sobre una superficie o cayendo.
		*/
		bool _falling;

	}; // class CPhysicCharacter

	REG_FACTORY(CPhysicCharacter);

} // namespace Logic

#endif // __Logic_PhysicCharacter_H
