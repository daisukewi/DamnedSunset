--------------------------------------------------
--				M�quina de estados				--
--------------------------------------------------

-- Definici�n de los distintos estados y sus acciones.
godIdleState = { event = godIdleStateEvent, action = godIdleStateAction }
godSelectedState = { event = godSelectedStateEvent, action = godSelectedStateAction }
godSkillState = { event = godSkillStateEvent, action = godSkillStateAction }
godBuildingState = { event = godBuildingStateEvent, action = godBuildingStateAction }

-- Tabla con todos los estados.
godStates = {
	{ name = "idle", state = godIdleState },
	{ name = "selected", state = godSelectedState },
	{ name = "skill", state = godSkillState },
	{ name = "build", state = godBuildingState }
}

-- Funci�n que recoger� los eventos a los cuales reaccionar� la m�quina de estados.
function godEvent(event)
	local nextState = godStates[god.state].state.event(event)
	god.state = nextState
end

-- Funci�n que se llamar� en cada tick para ejecutar las acciones que haga falta en el estado actual.
function godAction()
	-- Antes de llamar a la funci�n de transici�n de la m�quina de estados, actualizo los cooldowns de todas las habilidades de todos los personajes.
	updateSkillsCooldown(godActionParameters.deltaTime)

	local nextState = godStates[god.state].state.action()
	god.state = nextState
end

-- TODO HACK - Superhack de la muerte para poner los recursos iniciales del jugador. Lo pongo aqu� de forma provisional hasta que Dani termine su movida de
-- inicializaci�n de par�metros. Esto est� fatalmente hecho, no lo hag�is en ning�n sitio, que conste que es provisional nada mas.

-- El recurso del tiempo son doce horas pero lo pongo en minutos para poder hacer que haya edificios que cuesten una hora y cuarenta minutos o algo as�.
-- Al mismo tiempo se adapta a la forma de mostrarla ya que la funci�n de actualizar tiempo espera el tiempo en minutos.
god.dayTime = 720

-- Solenium, ahora mismo lo pongo un poco el primer n�mero que se me ocurre porque no s� ni lo que van a valer los edificios.
god.solenium = 1000