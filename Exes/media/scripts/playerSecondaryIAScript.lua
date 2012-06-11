
-- Guarda el personaje al que se está siguiendo
playerFollowID = -1

-- Calcula a que posición debe de ir el personaje cuando sigue a otro
function needMove(entity)
	aux = false;
	difX = players[entity].posX - players[playerFollowID].posX
	difY = players[entity].posY - players[playerFollowID].posY
	difZ = players[entity].posZ - players[playerFollowID].posZ
	
	if ((math.abs(difX) + math.abs(difZ)) > 50) then
		aux = true
	end
	return aux
end

--------------------------------------------------
--				Estado Follow Automatic						--
--------------------------------------------------

-- Recogida de eventos del estado Follow Automatic	 .
function playerFollowAutomaticStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState = 1
	
	if (event == "OnEnemySeen") then
	
		if (players[entity].attackEnemy == playerEventParam.target) then
		
		else
			
			players[entity].attackEnemy = playerEventParam.target
			
			local mensajeStop = LUA_MAttackDistance()
			mensajeStop:setAttack(false)
			mensajeStop:setEntityTo(entity)
			mensajeStop:send()
			
			
			local mensaje = LUA_MAttackDistance()
			mensaje:setContinue(true)
			mensaje:setAttack(true)
			mensaje:setEntityTo(entity)
			mensaje:setEntity(playerEventParam.target)
			mensaje:send()
		
		
			print('MENSAJE ENVIADO')
		end
		
	end
	
	return nextState
end

-- Acción del estado Follow Automatic	.
function playerFollowAutomaticStateAction(entity)
	
	local nextState
	if (playerFollowID ~= -1) then	
		if (needMove(entity)) then
			goTo(entity, players[playerFollowID].posX, players[playerFollowID].posY,players[playerFollowID].posZ)
		else
			stopGoTo(entity)
		end
	else
		print ('Error en playerSecondaryScript.lua. Si se está ejecutando la IA de la multiselección tiene que haber un personaje selecionado')
	end
	
	
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

-- Acción del estado atacando.
function playerFollowManualStateAction(entity)
	local nextState
	nextState = 2
	
	
	return nextState
end

--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
playerFollowAutomaticState = { event = playerFollowAutomaticStateEvent, action = playerFollowAutomaticStateAction }
playerFollowManualState = { event = playerFollowManualStateEvent, action = playerFollowManualStateAction }


-- Tabla con todos los estados.
playerSecondaryStates = {
	{ name = "follow_automatic", state = playerFollowAutomaticState },
	{ name = "follow_manual", state = playerFollowManualState }
}

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function playerSecondaryEvent(event, entity)
	--print('playerEvent: ')
	
	if (event == "StateChange") then
		local state
		-- players[entity].attackEnemy = -1
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

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerSecondaryAIAction(entity)
	print('SECONDARY: '..entity)
	playerFollowID = God.Selected
	local nextState = playerSecondaryStates[players[entity].secondaryState].state.action(entity)
	players[entity].secondaryState = nextState
end