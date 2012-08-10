--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle de god.
function godIdleStateEvent(event)
-- El estado de idle es el estado 1.
	local nextState
	
	-- Evento de click de selección.
	if (event == "OnSelectionClick") then
		-- Solo proceso los clicks de selección en el caso de que sea de noche.
		if (not(day)) then
			-- Solo proceso la selección si el objetivo es distinto del que tengo seleccionado ahora mismo.
			if (god.selected ~= selectionParameters.target) then
				-- Primero deselecciono el objetivo actual.
				unselectCurrentTarget()
				if (selectNewTarget(selectionParameters.target)) then
					-- Si se ha podido seleccionar un objetivo nuevo paso al estado de seleccionado.
					nextState = 2
				else
					-- Si no se ha podido seleccionar nada me quedo en el estado actual.
					nextState = 1
				end
			else
				nextState = 1
			end
		else
			nextState = 1
		end
	-- Evento de construcción de edificio
	elseif (event == "OnStartBuild") then
		-- Si me queda tiempo y solenium restante para construir el edificio empiezo su construcción pero todavía no resto los recursos.
		if ((god.dayTime >= buildingsCost[buildParameters.building].dayTime) and (god.solenium >= buildingsCost[buildParameters.building].solenium)) then
			-- Empiezo a construir el edificio.
			startBuild(buildParameters.building)
		
			-- Paso al estado de construyendo para gestionar la construcción del edificio.
			nextState = 4
		else
			-- En el caso de que no tenga suficiente de alguno de los recursos saco una ventana informativa y me quedo en el estado actual.
			sacarVentana("Recursos insuficientes para construir el edificio seleccionado.")
			
			nextState = 1
		end
	else
		nextState = 1
	end
	
	return nextState
end

-- Acción del estado idle de god.
function godIdleStateAction()
-- El estado de idle es el estado 1.
	local nextState = 1
	
	return nextState
end