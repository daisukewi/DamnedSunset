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
	local mensaje = LUA_MCambiarDiaNoche()
	mensaje:setCambiarADia(false)
	mensaje:send()
	
	-- Interfaz
	activarInterfazNoche()
	cargarInterfazControlesNoche()
end

function cambiarADia()
	print("\nAMANECER\n")
	
	-- Interfaz
	desactivarInterfazNoche()
	cargarInterfazControlesDia()
end

