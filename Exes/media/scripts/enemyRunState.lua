--------------------------------------------------
--				Estado huyendo					--
--------------------------------------------------

-- Recogida de eventos del estado huyendo.
function runStateEvent(event, entity)
-- El estado de huyendo es el estado 4.
	local nextState

	-- En principio no hay ningún evento que me haga salir de este estado pero pongo
	-- las comprobaciones para no perder la congruencia de los datos por si salgo por
	-- otros motivos.
	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
	elseif (event == "OnPlayerLost") then
		enemies[entity].playersSeen[enemyEventParam.target] = false
	end
	
	nextState = 4
	
	return nextState
end

-- Acción del estado huyendo.
function runStateAction(entity)
-- El estado de huyendo es el estado 4.
	local nextState
	
	if (enemies[entity].life > enemies[entity].runLifeThreshold) then
		-- Si en algún momento mi vida es mayor que el umbral vuelvo al estado de idle.
		nextState = 1
	else
		-- En cualquier otro caso sigo huyendo, por lo que me quedo en el estado actual.
		nextState = 4
	end
	
	return nextState
end