--------------------------------------------------
--				Estado seleccionado				--
--------------------------------------------------

-- Recogida de eventos del estado seleccionado de god.
function godSelectedStateEvent(event)
-- El estado de seleccionado es el estado 2.
	local nextState

	-- Evento de click de selección.
	if (event == "OnSelectionClick") then
		-- Me guardo el seleccionado actualmente para no permitir la deseleccion de personajes.
		local selected = god.playersSelected[1]
	
		-- Primero deselecciono todos los objetivos actuales
		unselectCurrentTargets()
		-- Intento seleccionar el nuevo objetivo
		if (selectNewTarget(selectionParameters.target)) then
			-- Si se ha podido seleccionar un objetivo nuevo, me quedo en el estado actual.
			nextState = 2
		else
			-- Si no se ha podido seleccionar nada continuo con el seleccionado anteriormente y me quedo en el estado actual.
			selectNewTarget(selected)
			nextState = 2
		end
	-- Evento de selección múltiple
	elseif (event == "OnMultiSelectionClick") then
		-- Me guardo el seleccionado actualmente para no permitir la deseleccion de personajes.
		local selected = god.playersSelected[1]
	
		-- Primero deselecciono todos los objetivos actuales
		unselectCurrentTargets()

		-- Hago una búsqueda por los objetivos seleccionados buscando al mismo tiempo cual es el primero
		local primarySelected = false
		for key, playerID in pairs(multiSelectionParameters) do
			if (playerID ~= -1) then
				if (not(primarySelected)) then
					if (selectNewTarget(playerID)) then
						primarySelected = true
					end
				else
					selectNewSecondTarget(playerID)
				end
			end
		end

		if (primarySelected) then
			nextState = 2
		else
			-- Si no se ha podido seleccionar nada continuo con el seleccionado anteriormente y me quedo en el estado actual.
			selectNewTarget(selected)
			nextState = 2
		end
	-- Evento de click de acción.
	elseif (event == "OnActionClick") then
		if (actionParameters.point_y ~= -1) then
			-- Primero compruebo si el primer objetivo seleccionado es un personaje.
			if ((god.playersSelected[1] ~= -1) and (isPlayer(god.playersSelected[1]))) then

				-- Chapuza para que Norah deje de curar si se le ordena moverse o atacar
				if god.playersSelected[1] == getEntityID("Norah") then
					cancelCure(god.playersSelected[1])
				end

				-- Si el objetivo de la acción es un enemigo le mando una orden de ataque al todos los personajes seleccionados
				if ((actionParameters.target ~= -1) and ((isEnemy(actionParameters.target)) or (isEnemyBuilding(actionParameters.target)))) then
					for i, playerID in pairs(god.playersSelected) do
						sendAttack(actionParameters.target, playerID)
					end
				else
					-- Si el objetivo de la acción no es ningún entidad o no es un enemigo le mando una orden de movimiento a todos los personajes seleccionados.
					for i, playerID in pairs(god.playersSelected) do
						sendMovement(actionParameters.point_x, actionParameters.point_y, actionParameters.point_z, playerID)
					end
				end
			end
		end

		-- Sea la acción que sea la que se haya hecho sobre el objetivo me quedo en el estado actual ya que no influye sobre la selección.
		nextState = 2
	-- Evento de click en una habilidad del personaje seleccionado.
	elseif (event == "OnSkillClick") then
		-- Si el cooldown de la habilidad es cero o menos la hago.
		if (players[god.playersSelected[1]].currentSkillsCooldown[skillParameters.skill] <= 0) then
			-- Empiezo la habilidad.
			god.startSkillFunction()

			-- Me guardo el índice de la habilidad
			god.currentSkill = skillParameters.skill

			-- Me guardo en otra variable distinta la función de cancelación de la habilidad actual
			-- por si hay que cancelarla porque se ha pulsado en otra habilidad distinta.
			god.previousCancelSkillFunction = god.cancelSkillFunction

			-- Paso al estado de gestión de la habilidad.
			nextState = 3
		else
			-- En el caso de que la habiliad esté todavía en tiempo de cooldown me quedo en el estado actual sin hacer nada.
			nextState = 2
		end
	-- Evento de teclado
	elseif (event == "OnKeyEvent") then
		local entityID = 0;

		-- Miro que tecla numérica ha pulsado el usuario y me guardo el ID de la entidad.
		if (keyEventParameters.key == "NUMBER1") then
			entityID = getEntityID("Jack")
		elseif (keyEventParameters.key == "NUMBER2") then
			entityID = getEntityID("Erick")
		elseif (keyEventParameters.key == "NUMBER3") then
			entityID = getEntityID("Norah")
		end

		-- Si el ID es alguno válido es porque se ha pulsado una tecla que corresponde a un personaje, por lo tanto procedo a seleccionarlo.
		if (entityID ~= 0) then
			-- Primero deselecciono todos los objetivos actuales
			unselectCurrentTargets()
			-- Intento seleccionar el nuevo objetivo
			if (selectNewTarget(entityID)) then
				-- Si se ha podido seleccionar un objetivo nuevo me quedo en el estado actual.
				nextState = 2
			else
				-- Si no se ha podido seleccionar nada paso al estado de idle.
				nextState = 1
			end
		else
			-- Si no se ha pulsado una tecla correspondiente a un personaje me quedo en el estado actual.
			nextState = 2
		end
	-- Evento de que empieza el día
	elseif (event == "OnDayStart") then
		-- Deselecciono todos los personajes.
		unselectCurrentTargets()
		
		-- Paso al estado de idle.
		nextState = 1
	else
		nextState = 2
	end

	return nextState
end

-- Acción del estado seleccionado de god.
function godSelectedStateAction()
-- El estado de seleccionado es el estado 2.
	local nextState = 2

	return nextState
end
