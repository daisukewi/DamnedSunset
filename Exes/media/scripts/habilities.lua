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
	if (god.playersSelected[1]  ~= 0) then
		playerEventParam = { state = 'idle' }
		playerEvent("StateChange",god.playersSelected[1])
	end
end

function funcionIA2()
	if (god.playersSelected[1]  ~= 0) then
		playerEventParam = { state = 'follow' } 
		playerEvent("StateChange",god.playersSelected[1])
	end
end

function funcionIA3()
	if (god.playersSelected[1]  ~= 0) then
		playerEventParam = { state = 'hold' } 
		playerEvent("StateChange",god.playersSelected[1])
	end
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
	
	--actualizarHorasAmanecer(12 * 60)
	actualizarHorasAmanecer(god.dayTime)
	--actualizarSolenium(750)
	actualizarSolenium(god.solenium)
end

