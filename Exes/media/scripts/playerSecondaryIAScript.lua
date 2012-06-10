-- Calcula a que posici�n debe de ir el 

--------------------------------------------------
--				Estado Follow Automatic						--
--------------------------------------------------

-- Recogida de eventos del estado Follow Automatic	 .
function playerFollowAutomaticStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	return 1
end

-- Acci�n del estado Follow Automatic	.
function playerFollowAutomaticStateAction(entity)
	local nextState
	return 1
end

--------------------------------------------------
--				Estado siguiendo					--
--------------------------------------------------

-- Recogida de eventos del estado atacando.
function playerFollowManualStateEvent(event, entity)

	local nextState
	nextState = 2
	
	
	return nextState
end

-- Acci�n del estado atacando.
function playerFollowManualAction(entity)
	local nextState
	nextState = 2
	
	
	return nextState
end

--------------------------------------------------
--				M�quina de estados				--
--------------------------------------------------

-- Definici�n de los distintos estados y sus acciones.
playerFollowAutomaticState = { event = playerFollowAutomaticStateEvent, action = playerFollowAutomaticStateAction }
playerFollowManualState = { event = playerFollowManualStateEvent, action = playerFollowManualStateAction }


-- Tabla con todos los estados.
playerSecondaryStates = {
	{ name = "follow_automatic", state = playerFollowAutomaticState },
	{ name = "follow_manual", state = playerFollowManualState }
}


-- Variables para guardar los IDs de los personjaes y acceder a su posici�n 
playerJackID = -1
playerErickID = -1
playerAmorID = -1


-- Funci�n que recoger� los eventos a los cuales reaccionar� la m�quina de estados.
function playerSecondaryEvent(event, entity)
	--print('playerEvent: ')
	
	if (event == "StateChange") then
		local state
		players[entity].attackEnemy = -1
		if (playerEventParam.state == 'follow_manual') then
			state = 1
			print('FOLLOW_MANUAL')
		elseif (playerEventParam.state == 'follow_automatic') then
			state = 2
			print('FOLLOW_AUTOMATIC')
		end
		
		players[entity].secondaryState = state
	else
		local nextState = playerSecondaryStates[players[entity].secondaryState].state.event(event, entity)
		players[entity].secondaryState = nextState
	end
end

-- Funci�n que se llamar� en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerSecondaryAIAction(entity)
	local nextState = playerSecondaryStates[players[entity].secondaryState].state.action(entity)
	players[entity].secondaryState = nextState
end