-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Erick
function activateErickSkills(playerID)
	players[playerID].showGUISkills = showErickSkills
	
	-- Configuración de los cooldowns de las habilidades.
	-- Cada índice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = { 
	}
	
	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
	}
end

-- Función que mostrará las habilidades de Erick en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showErickSkills()
	cargarBoton(2, "granada", "erickGrenade")
	cargarBoton(3, "bolazul", "bulletTime")

	if persSelect ~= 2 then
		cambiarBotones(2)
	end
end

--------------------------------------------------
--			Habilidad granada de Erick			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function erickGrenade()
end

function startErickGrenade()
end

function explodeErickGrenade()
end

function cancelErickGrenade()
end

--------------------------------------------------
--		Habilidad bullet time de Erick			--
--------------------------------------------------
-- La habilidad de bullet time es de tipo INMEDIATO

function bulletTime()
end