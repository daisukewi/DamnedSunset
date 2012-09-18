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
			-- Primero deselecciono todos los objetivos actuales
			unselectCurrentTargets()
			-- Intento seleccionar el nuevo objetivo
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
	-- Evento de selección múltiple
	elseif (event == "OnMultiSelectionClick") then
		-- Solo proceso los clicks de selección en el caso de que sea de noche.
		if (not(day)) then
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
				-- Si se ha podido seleccionar un objetivo nuevo paso al estado de seleccionado.
				nextState = 2
			else
				-- Si no se ha podido seleccionar nada me quedo en el estado actual.
				nextState = 1
			end
		else
			-- Si no se ha pulsado una tecla correspondiente a un personaje me quedo en el estado actual.
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