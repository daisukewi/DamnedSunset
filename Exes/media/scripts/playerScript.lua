--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle.
function playerIdleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	return 1
end

-- Acción del estado idle.
function playerIdleStateAction(entity)
	
	return 1
end

--------------------------------------------------
--				Estado siguiendo					--
--------------------------------------------------

-- Recogida de eventos del estado atacando.
function playerFollowStateEvent(event, entity)

	local nextState
	nextState = 2
	if (event == "OnEnemySeen") then
	
		-- Si no hay ningún enemigo al que atacar
		if (players[entity].attackEnemy == -1) then
			
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
			
		else
			-- Si el enemigo que se ha visto es el que se estaba siguiendo
			if (players[entity].attackEnemy == playerEventParam.target) then
				-- Comprobar que se le estaba siguiendo, si no no hace falta enviar el mensaje porque ya lo está atacando
				if (players[entity].enemyFollow == true )then
					
					local mensaje = LUA_MAttackDistance()
					mensaje:setContinue(true)
					mensaje:setAttack(true)
					mensaje:setEntityTo(entity)
					mensaje:setEntity(players[entity].attackEnemy)
					mensaje:send()
				
					print('LUA: MANDAR ATACAR A ENEMIGO ANTERIOR')
				end
			end
		end
		
	elseif (event == "OnEnemyLost") then
	
		if (players[entity].attackEnemy == playerEventParam.target) then
			players[entity].enemyFollow = true
			
			local mensajeStop = LUA_MAttackDistance()
			mensajeStop:setAttack(false)
			mensajeStop:setEntityTo(entity)
			mensajeStop:send()
			
			print('LUA: ENEMIGO HA SALIDO')
		end
		
	elseif (event == "OnEnemyDie") then
		
		if (players[entity].attackEnemy == playerEventParam.target) then
			players[entity].attackEnemy = -1
			players[entity].enemyFollow = false
			stopGoTo(entity)

			print('LUA: ENEMIGO A MUERTO')
		end
	
	end
	
	return nextState
end

-- Acción del estado atacando.
function playerFollowStateAction(entity)
	local nextState
	nextState = 2
	if (players[entity].enemyFollow == true) then
	
		print('LUA: PERSEGUIR')
		goTo(enemies[players[entity].attackEnemy].posX,enemies[players[entity].attackEnemy].posY,enemies[players[entity].attackEnemy].posZ,entity)
	
	end
	
	return nextState
end

--------------------------------------------------
--				Estado mantener posicion					--
--------------------------------------------------

-- Recogida de eventos del mantener posición.
function playerHoldStateEvent(event, entity)
	local nextState
	nextState = 3
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

-- Acción del estado mantener posición.
function playerHoldStateAction(entity)
	local nextState
	nextState = 3
	
	return nextState
end

--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
playerIdleState = { event = playerIdleStateEvent, action = playerIdleStateAction }
playerFollowState = { event = playerFollowStateEvent, action = playerFollowStateAction }
playerHoldState = { event = playerHoldStateEvent, action = playerHoldStateAction }

-- Tabla con todos los estados.
playerStates = {
	{ name = "idle", state = playerIdleState },
	{ name = "follow", state = playerFollowState },
	{ name = "hold", state = playerHoldState },
}

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function playerEvent(event, entity)
	--print('playerEvent: ')
	
	if (event == "StateChange") then
		local state
		players[entity].attackEnemy = -1
		if (playerEventParam.state == 'idle') then
			state = 1
			print('IDLE')
		elseif (playerEventParam.state == 'follow') then
			players[entity].enemyFollow = false
			state = 2
			print('FOLLOW')
		elseif (playerEventParam.state == 'hold') then
			state = 3
			print('HOLD')
		end
		
		players[entity].state = state
	else
		local nextState = playerStates[players[entity].state].state.event(event, entity)
		players[entity].state = nextState
	end
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerAIAction(entity)
	local nextState = playerStates[players[entity].state].state.action(entity)
	players[entity].state = nextState
end