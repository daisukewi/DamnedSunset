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
