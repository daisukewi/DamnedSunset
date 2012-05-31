--Creando tabla de datos de God
God = {
	Selected = -1
}

function processSelection(target, point_x, point_y, point_z)
	print("Se ha seleccionado la entidad " .. target)
	
	selectNewTarget(target)
end

function processAction(target, point_x, point_y, point_z)
	if point_y ~= -1 then
		if God.Selected ~= -1 then
			if target ~= -1 then
				print("Atacando a la entidad " .. target)
				local atack = LUA_MAttackEntity()
				atack:setAttack(true)
				atack:setEntity(target)
				atack:setEntityTo(God.Selected)
				atack:send()
			else
				sendMovement(point_x, point_y, point_z)
			end
		end
	end
end

function selectNewTarget(target)
	--Unselect current target
	if God.Selected ~= -1 then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(God.Selected)
		mensaje:setSelectedEntity(0)
		mensaje:send()
	end
	
	--Select new target 
	God.Selected = target
	
	--Send selected to new target
	if target ~= -1 then
		print("Selecting new target")
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(target)
		mensaje:setSelectedEntity(target)
		mensaje:send()
		
		print("Setting new camera target")
		local mensaje = LUA_MUbicarCamara()
		mensaje:setTarget(target)
		mensaje:send()
		
		print("Loading selected target GUI")
		loadPlayerGUI(target)
	end
end

function unselectCurrentTarget()
	if God.Selected ~= -1 then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(God.Selected)
		mensaje:setSelectedEntity(0)
		mensaje:send()
	end
end

--Hacerlo diferente para cada heroe
function loadPlayerGUI (player)
	ocultarBotones()
	print("Setting buttons for player " .. player)
	cargarBoton(1, "martillo", "construirTorreta")
	cargarBoton(2, "granada", "habilidadGranada")
	cargarBoton(3, "bolazul", "habilidadRalentizarTiempo")
	cargarBoton(4, "jeringa", "habilidadCurar")
	print("Buttons setted correctly")
end

function sendMovement(point_x, point_y, point_z)
	print("Moviendo entidad " .. God.Selected)
	local mensaje = LUA_MAStarRoute()
	mensaje:setDestPointX(point_x)
	mensaje:setDestPointY(point_y)
	mensaje:setDestPointZ(point_z)
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
end

function sendAttack (enemy)
	local mensaje = LUA_MAttackDistance()
	mensaje:setEntity(target)
	mensaje:setAttack(true)
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
end