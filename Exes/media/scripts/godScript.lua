--Creando tabla de datos de God
God = {
	Selected = -1
}

function processSelection(target, point_x, point_y, point_z)
	print("Se ha seleccionado la entidad " .. target)
	
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
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(target)
		mensaje:setSelectedEntity(target)
		mensaje:send()
		
		local mensaje = LUA_MUbicarCamara()
		mensaje:setTarget(target)
		mensaje:send()
		
		loadPlayerGUI(target)
	end
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
	cargarBoton(1, "martillo")
	cargarBoton(2, "granada")
	cargarBoton(3, "bolazul")
	cargarBoton(4, "jeringa")
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