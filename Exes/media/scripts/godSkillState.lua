--------------------------------------------------
--				Estado de skill					--
--------------------------------------------------

-- Recogida de eventos del estado skill de god.
function godSkillStateEvent(event)
-- El estado de skill es el estado 3.
	local nextState
	
	-- Evento de click de selecci�n.
	if (event == "OnSelectionClick") then
		-- Si el objetivo de la habilidad es un punto en el terreno, relleno la informaci�n del punto y llamo al final de la habilidad.
		if (god.clickTarget == nil) then
			-- Actualizo su cooldown para que empiece a contar.
			players[god.playersSelected[1]].currentSkillsCooldown[god.currentSkill] = players[god.playersSelected[1]].skillsCooldown[god.currentSkill]
		
			skillParameters = selectionParameters
			god.finishSkillFunction()
			
			-- Al finalizar la habilidad paso al estado de personaje seleccionado.
			nextState = 2
		-- Si el objetivo de la habilidad coincide con el objetivo seleccionado entonces lanzo la habilidad.
		elseif (god.clickTarget == getTag(selectionParameters.target)) then
			-- Actualizo su cooldown para que empiece a contar.
			players[god.playersSelected[1]].currentSkillsCooldown[god.currentSkill] = players[god.playersSelected[1]].skillsCooldown[god.currentSkill]
		
			skillParameters = selectionParameters
			god.finishSkillFunction()
			
			-- Al finalizar la habilidad paso al estado de personaje seleccionado.
			nextState = 2
		else
			-- En cualquier otro caso me quedo en el estado actual esperando que el usuario haga algo con la habilidad.
			nextState = 3
		end
	-- Evento de click de acci�n.
	elseif (event == "OnActionClick") then
		-- En cualquier caso de click de acci�n, cancelo la habilidad y vuelvo al estado de personaje seleccionado.
		god.cancelSkillFunction()
		
		nextState = 2
	-- Evento de click en una habilidad del personaje seleccionado.
	elseif (event == "OnSkillClick") then
		-- Si el cooldown de la habilidad es cero o menos la hago, sino, me quedo como estaba;
		-- esperando la respuesta del jugador parar completar la habilidad actual.
		if (players[god.playersSelected[1]].currentSkillsCooldown[skillParameters.skill] <= 0) then
			-- Primero cancelo la habilidad activada anteriormente.
			god.previousCancelSkillFunction()
			
			-- Despu�s empiezo la nueva habilidad.
			god.startSkillFunction()

			-- Me guardo el �ndice de la habilidad
			god.currentSkill = skillParameters.skill			

			-- Me vuelvo a guardar una copia de la funci�n de cancelaci�n por si vuelve a ocurrir el mismo caso.
			god.previousCancelSkillFunction = god.cancelSkillFunction
		end
		
		-- Me quedo en el estado actual en cualquier caso.
		nextState = 3
	else
		nextState = 3
	end
	
	return nextState
end

-- Acci�n del estado skill de god.
function godSkillStateAction()
-- El estado de skill es el estado 3.
	local nextState = 3
	
	return nextState
end