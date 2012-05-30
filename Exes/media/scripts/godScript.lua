--Creando tabla de datos de God
God = {
	Selected = 0
}

--Hablididades de los personajes
function habilidadGranada()
	print("habilidad granada")
end

function habilidadGranadaTeletransportadora()
	print("habilidad Granada Teletransportadora")
end

function habilidadRalentizarTiempo()
	print("habilidad Ralentizar Tiempo")
end

function habilidadCurar()
	print("habilidad Curar")
end

function construirTorreta()
	print("construir Torreta")
end

function inicializarBotonesDia()
	print("inicializarBotonesDia")
	cargarBoton(1,"martillo","construirTorreta")
	ocultarBoton(2)
	ocultarBoton(3)
	cargarBoton(4,"bolazul","cambiarADia")
	print("fin inicializarBotonesDia")
end

function cambiarADia()
	local mensaje = LUA_MCambiarDiaNoche()
	mensaje:setCambiarADia(false)
	mensaje:send()
	
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	ocultarBoton(4)
end

--Funciones que se llamaran cuando un personaje es seleccionado
function seleccionarPersonaje1()
	-- Crear y enviar el mensaje de entity selected
	------> SUPONGO QUE ESTE MENSJAE HABRA QUE BORRARLO DE AQUI - (al igual que en los otros 2 personajes)
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity("Jack")
	mensaje:setInterface(true)
	mensaje:send()
	
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	cargarBoton(4,"granada","habilidadGranada")
end

function seleccionarPersonaje2()
	-- Crear y enviar el mensaje de entity selected
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity("Erick")
	mensaje:setInterface(true)
	mensaje:send()
	
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	cargarBoton(4,"bolazul","habilidadGranadaTeletransportadora")
end

function seleccionarPersonaje3()
	-- Crear y enviar el mensaje de entity selected
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity("Amor")
	mensaje:setInterface(true)
	mensaje:send()
	
	ocultarBoton(1)
	ocultarBoton(2)
	cargarBoton(3,"bolazul","habilidadRalentizarTiempo")
	cargarBoton(4,"jeringa","habilidadCurar")
end

function processSelection(target, point_x, point_y, point_z)
	print("Se ha seleccionado la entidad " .. target)
	God.Selected = target
end

function processAction(target, point_x, point_y, point_z)
	if point_y ~= -1 then
		if God.Selected ~= -1 then
			if target ~= -1 then
				local mensaje = LUA_MAttackDistance()
				mensaje:setEntity(target)
				mensaje:setAttack(true)
				mensaje:setEntityTo(God.Selected)
				mensaje:send()
			else
				local mensaje = LUA_MAStarRoute()
				mensaje:setDestPointX(point_x)
				mensaje:setDestPointY(point_y)
				mensaje:setDestPointZ(point_z)
				mensaje:setEntityTo(God.Selected)
				mensaje:send()
			end
		end
	end
end