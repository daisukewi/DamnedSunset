--Creando tabla de datos de God
God = {
	Selected = -1,
	SecondSelected = -1,
	ThirdSelected = -1
}

GodSelected = -1

-- Procesa la selección múltiple. Los tres parámetros corresponden a los 3 personajes. en caso de que valgan -1, ese persnaje no ha sido seleccionado
function processMultipleSelection(target1, target2, target3)
	local auxSecondSelected = -1
	local auxThirdSelected = -1
	local auxSelected = God.Selected
	local actualTargetNotSelected = false
	-- Si hay un personaje seleccionado

	if (God.Selected ~= -1) then

		-- Si se ha vuelto a selecionnar uno de los personajes seleccionados.
		if (target1 == God.Selected) then
			auxSecondSelected = target2
			auxThirdSelected = target3
		elseif (target2 == God.Selected) then
			auxSecondSelected = target1
			auxThirdSelected = target3
		elseif (target3 == God.Selected) then
			auxSecondSelected = target1
			auxThirdSelected = target2
		else
			-- Si no se ha vuelto a seleccionar ninguno de los ya seleccionados
			-- Hacer lo mismo que si no se encuentra ningún personaje seleccionado
			actualTargetNotSelected = true
		end

	-- Si no hay un personaje seleccionado		
	else
		actualTargetNotSelected = true
	end

	
	if (actualTargetNotSelected == true) then
		if (target1 ~= -1) then
			auxSelected = target1
			auxSecondSelected = target2
			auxThirdSelected = target3
		else
			if (target2 ~= -1) then
				auxSelected = target2
				auxSecondSelected = target1
				auxThirdSelected = target3
			else
				if (target3 ~= -1) then
					auxSelected = target3
					auxSecondSelected = target1
					auxThirdSelected = target2
				end
			end
		end
	end
	
	if (auxSelected ~= God.Selected) then
		unselectCurrentTarget()
	end

	if (auxSecondSelected ~= God.SecondSelected) then
		if (God.SecondSelected ~= -1) then
			unselectSecondSelected()
		end
		
		if (auxSecondSelected ~= -1) then
			selectSecondSelected(auxSecondSelected)
		end
	
	end

	if (auxThirdSelected ~= God.ThirdSelected) then
		if (God.ThirdSelected ~= -1) then
			unselectThirdSelected()
		end
		
		if (auxThirdSelected ~= -1) then
			selectThirdSelected(auxThirdSelected)
		end
	end

	if (auxSelected ~= God.Selected) then
		selectNewTarget(auxSelected)
	end
end

function processSelection(target, point_x, point_y, point_z)
	unselectSecondSelected()
	unselectThirdSelected()
	if (God.Selecetd ~= target) then
		unselectCurrentTarget()
		selectNewTarget(target)
	end
end

function processAction(target, point_x, point_y, point_z)
	if point_y ~= -1 then
		if God.Selected ~= -1 and isPlayer(God.Selected) then
			if target ~= -1 and isEnemy(target) then
				sendAttack(target, God.Selected)
				-- Si hay varios personajes seleccionados enviarles la misma acción
				if (God.SecondSelected ~= -1) then
					sendAttack(target, God.SecondSelected)
				end
				if (God.ThirdSelected ~= -1) then
					sendAttack(target, God.ThirdSelected)
				end
			else
				sendMovement(point_x, point_y, point_z, God.Selected)
				-- Si hay varios personajes seleccionados enviarles la misma acción
				if (God.SecondSelected ~= -1) then
					sendMovement(point_x, point_y, point_z, God.SecondSelected)
				end
				if (God.ThirdSelected ~= -1) then
					sendMovement(point_x, point_y, point_z, God.ThirdSelected)
				end
			end
		end
	end
end

function selectNewTarget(target)

	--Select new target
	God.Selected = target

	--Send selected to new target
	if target ~= -1 and isPlayer(target) then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(target)
		mensaje:setSelectedEntity(target)
		mensaje:send()

		local mensaje = LUA_MUbicarCamara()
		mensaje:setTarget(target)
		mensaje:send()

		loadPlayerGUI(target)
	end
	
	GodSelected = God.Selected

end

function unselectCurrentTarget()
	if God.Selected ~= -1 then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(God.Selected)
		mensaje:setSelectedEntity(0)
		mensaje:send()
		God.Selected = -1
	end
end

function loadPlayerGUI (player)
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	ocultarBoton(4)

	name = getName(player)
	if name == "Jack" then
		cargarBoton(2, "granada", "habilidadGranada")
		if persSelect ~= 1 then
			cambiarBotones(1)
		end
	elseif name == "Erick" then
		cargarBoton(2, "granada", "habilidadGranada")
		cargarBoton(3, "bolazul", "habilidadRalentizarTiempo")
		if persSelect ~= 2 then
			cambiarBotones(2)
		end
	elseif name == "Amor" then
		cargarBoton(2, "granada", "habilidadGranada")
		cargarBoton(4, "jeringa", "habilidadCurar")
		if persSelect ~= 3 then
			cambiarBotones(3)
		end
	end
end

function sendMovement(point_x, point_y, point_z, entity)
	local mensaje = LUA_MAStarRoute()
	mensaje:setDestPointX(point_x)
	mensaje:setDestPointY(point_y)
	mensaje:setDestPointZ(point_z)
	mensaje:setEntityTo(entity)
	mensaje:send()
end

function sendAttack (target, entity)
	local mensaje = LUA_MAttackDistance()
	mensaje:setEntity(target)
	mensaje:setAttack(true)
	mensaje:setEntityTo(entity)
	mensaje:send()
end
function processKeyboardEvent(key)
	if (key == "TAB") then
		alternatePlayer()
	end
end
-- Función que se encarga de alternar de jugador cuando se pulsa el tabulador
function alternatePlayer()
	if (God.Selected ~= -1) then
		local aux = -1
		local aux2 = -1
		local aux3 = -1
		if (God.SecondSelected ~= -1) and (God.ThirdSelected ~= -1) then
			aux = God.Selected
			aux2 = God.SecondSelected
			aux3 = God.ThirdSelected
			unselectCurrentTarget()
			unselectSecondSelected()
			unselectThirdSelected()
			selectNewTarget(aux2)
			selectSecondSelected(aux3)
			selectThirdSelected(aux)
		elseif (God.SecondSelected == -1) and (God.ThirdSelected ~= -1) then
			aux = God.Selected
			aux2 = God.ThirdSelected
			unselectCurrentTarget()
			unselectThirdSelected()
			selectNewTarget(aux2)
			selectSecondSelected(aux)
		elseif (God.SecondSelected ~= -1) and (God.ThirdSelected == -1) then
			aux = God.Selected
			aux2 = God.SecondSelected
			unselectCurrentTarget()
			unselectSecondSelected()
			selectNewTarget(aux2)
			selectSecondSelected(aux)
		end
	end
end

function unselectSecondSelected()
	if (God.SecondSelected ~= -1) then
		local unselectSecondMensaje = LUA_MEntitySelected()
		unselectSecondMensaje:setSelectedType("SECONDARY")
		unselectSecondMensaje:setEntityTo(God.SecondSelected)
		unselectSecondMensaje:setSelectedEntity(0)
		unselectSecondMensaje:send()
		God.SecondSelected = -1
	end
end

function unselectThirdSelected()
	if (God.ThirdSelected ~= -1) then
		local unselectThirdMensaje = LUA_MEntitySelected()
		unselectThirdMensaje:setSelectedType("SECONDARY")
		unselectThirdMensaje:setEntityTo(God.ThirdSelected)
		unselectThirdMensaje:setSelectedEntity(0)
		unselectThirdMensaje:send()
		God.ThirdSelected = -1
	end
end

function selectSecondSelected(SecondSelected)
	if (SecondSelected ~= -1) then
		God.SecondSelected = SecondSelected
		local selectSecondMensaje = LUA_MEntitySelected()
		selectSecondMensaje:setSelectedType("SECONDARY")
		selectSecondMensaje:setEntityTo(God.SecondSelected)
		selectSecondMensaje:setSelectedEntity(God.SecondSelected)
		selectSecondMensaje:send()
	end
end

function selectThirdSelected(ThirdSelected)
	if (ThirdSelected ~= -1) then
		God.ThirdSelected = ThirdSelected
		local selectThirdMensaje = LUA_MEntitySelected()
		selectThirdMensaje:setSelectedType("SECONDARY")
		selectThirdMensaje:setEntityTo(God.ThirdSelected)
		selectThirdMensaje:setSelectedEntity(God.ThirdSelected)
		selectThirdMensaje:send()
	end
end