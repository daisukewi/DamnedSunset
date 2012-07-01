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

function startBuildTurrent()
	print("construir Torreta")
	setBuildingState()
	startBuild("Turret")
end

function keyEscPress()
	cancelBuild()
	finishBuildingState()
end

function inicializarBotonesDia()
	print("inicializarBotonesDia")
	cargarBoton(1,"martillo","startBuildTurrent")
	ocultarBoton(2)
	ocultarBoton(3)
	cargarBoton(4,"bolazul","cambiarANoche")
	print("fin inicializarBotonesDia")
	
	cargarBotonIA(1,"BotonIA1", "funcionIA1")
	cargarBotonIA(2,"BotonIA2", "funcionIA2")
	cargarBotonIA(3,"BotonIA3", "funcionIA3")
end

function funcionIA1()
	local mensaje = LUA_MSetPlayerState()
	mensaje:setPlayerState("idle")
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
	print("Enviado mensaje IDLE")
end

function funcionIA2()
	local mensaje = LUA_MSetPlayerState()
	mensaje:setPlayerState("hold")
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
	print("Enviado mensaje HOLD")
end

function funcionIA3()
	local mensaje = LUA_MSetPlayerState()
	mensaje:setPlayerState("follow")
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
	print("Enviado mensaje FOLLOW")
end

function cambiarANoche()
	print("\nANOCHECER\n")
	
	day = false
	
	local mensaje = LUA_MCambiarDiaNoche()
	mensaje:setCambiarADia(false)
	mensaje:send()
	
	-- Interfaz
	activarInterfazNoche()
	desactivarInterfazDia()
	cargarInterfazControlesNoche()
end

function cambiarADia()
	print("\nAMANECER\n")
	
	day = true
	
	local mensaje = LUA_MCambiarDiaNoche()
	mensaje:setCambiarADia(true)
	mensaje:send()
	
	-- Interfaz
	desactivarInterfazNoche()
	activarInterfazDia()
	cargarInterfazControlesDia()
	
	actualizarHorasAmanecer(12 * 60)
	actualizarSolenium(750)
end

