--------------------------------------------------
--				Estado seleccionado				--
--------------------------------------------------

-- Recogida de eventos del estado seleccionado de god.
function godSelectedStateEvent(event)
-- El estado de seleccionado es el estado 2.
	local nextState
	
	-- Evento de click de selecci�n.
	if (event == "OnSelectionClick") then
		-- Solo proceso la selecci�n si el objetivo es distinto del que tengo seleccionado ahora mismo.
		if (god.selected ~= selectionParameters.target) then
			-- Primero deselecciono el objetivo actual.
			unselectCurrentTarget()
			if (selectNewTarget(selectionParameters.target)) then
				-- Si se ha podido seleccionar un objetivo nuevo, me quedo en el estado actual.
				nextState = 2
			else
				-- Si no se ha podido seleccionar nada paso al estado de idle.
				nextState = 1
			end
		else
			-- Si el objetivo de la selecci�n es el mismo que ya tengo seleccionado, no hago nada y me quedo en el estado actual.
			nextState = 2
		end
	-- Evento de click de acci�n.
	elseif (event == "OnActionClick") then
		if (actionParameters.point_y ~= -1) then
			-- Primero compruebo si el objetivo seleccionado es un personaje.
			if ((god.selected ~= -1) and (isPlayer(god.selected))) then
				-- Si el objetivo de la acci�n es un enemigo le mando una orden de ataque al personaje seleccionado.
				if ((actionParameters.target ~= -1) and (isEnemy(actionParameters.target))) then
					sendAttack(actionParameters.target, god.selected)
				else
					-- Si el objetivo de la acci�n no es ning�n entidad o no es un enemigo le mando una orden de movimiento al personaje seleccionado.
					sendMovement(actionParameters.point_x, actionParameters.point_y, actionParameters.point_z, god.selected)
				end
			end
		end
		
		-- Sea la acci�n que sea la que se haya hecho sobre el objetivo me quedo en el estado actual ya que no influye sobre la selecci�n.
		nextState = 2
	-- Evento de click en una habilidad del personaje seleccionado.
	elseif (event == "OnSkillClick") then
		-- Si el cooldown de la habilidad es cero o menos la hago.
		if (players[god.selected].currentSkillsCooldown[skillParameters.skill] <= 0) then
			-- Empiezo la habilidad.
			god.startSkillFunction()
			
			-- Me guardo el �ndice de la habilidad
			god.currentSkill = skillParameters.skill
			
			-- Me guardo en otra variable distinta la funci�n de cancelaci�n de la habilidad actual
			-- por si hay que cancelarla porque se ha pulsado en otra habilidad distinta.
			god.previousCancelSkillFunction = god.cancelSkillFunction
		
			-- Paso al estado de gesti�n de la habilidad.
			nextState = 3
		else
			-- En el caso de que la habiliad est� todav�a en tiempo de cooldown me quedo en el estado actual sin hacer nada.
			nextState = 2
		end
	else
		nextState = 2
	end
	
	return nextState
end

-- Acci�n del estado seleccionado de god.
function godSelectedStateAction()
-- El estado de seleccionado es el estado 2.
	local nextState = 2
	
	return nextState
end