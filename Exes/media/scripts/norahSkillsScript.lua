-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Norah
function activateNorahSkills(playerID)
	players[playerID].showGUISkills = showNorahSkills
	
	-- Configuración de los cooldowns de las habilidades.
	-- Cada índice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = { 
		[1] = 5, 
		[2] = 5,
	}
	
	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
		[1] = 0,
		[2] = 5,
	}
end

-- Función que mostrará las habilidades de Norah en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showNorahSkills()
	cargarBoton(2, "granada", "norahGrenade")
	cargarBoton(4, "jeringa", "norahHeal")
	
	if persSelect ~= 3 then
		cambiarBotones(3)
	end
end

--------------------------------------------------
--			Habilidad granada de Norah			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function norahGrenade()
	god.startSkillFunction = startNorahGrenade
	skillParameters = {
		skill = 1,
	}
	godEvent("OnSkillClick")
end

function startNorahGrenade()
	god.finishSkillFunction = explodeNorahGrenade
	god.cancelSkillFunction = cancelNorahGrenade
	god.clickTarget = nil
	
	startGrenade(god.playersSelected[1], 0, 0, 0)
end

function explodeNorahGrenade()
	launchGrenade(god.playersSelected[1], 0, 0, 0)
end

function cancelNorahGrenade()
	cancelGrenade(god.playersSelected[1], 0, 0, 0)
end

--------------------------------------------------
--			Habilidad curar de Norah			--
--------------------------------------------------
-- La habilidad curar es de tipo NO INMEDIATO

function norahHeal()
end

function startNorahHeal()
end

function executeNorahHeal()
end

function cancelNorahHeal()
end