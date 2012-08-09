-- Asignaci�n de la funci�n que se llamar� cuando se quiera mostrar en el GUI
-- las habilidades de Jack
function activateJackSkills(playerID)
	players[playerID].showGUISkills = showJackSkills

	-- Configuraci�n de los cooldowns de las habilidades.
	-- Cada �ndice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = {
		[1] = 5,
		[2] = 5,
	}

	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
		[1] = 0,
		[2] = 0,
	}
end

-- Funci�n que mostrar� las habilidades de Jack en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showJackSkills()
	cargarBoton(2, "granada", "jackGrenade")
	cargarBoton(3, "bolazul", "jackEmpuje")

	if persSelect ~= 1 then
		cambiarBotones(1)
	end
end

--------------------------------------------------
--			Habilidad granada de Jack			--
--------------------------------------------------
-- La habilidad de la granada es la n�mero 1
-- La habilidad de la granada es de tipo NO INMEDIATO

function jackGrenade()
	god.startSkillFunction = startJackGrenade
	skillParameters = {
		skill = 1,
	}
	print("jackGrenade")
	godEvent("OnSkillClick")
end

function startJackGrenade()
	god.finishSkillFunction = explodeJackGrenade
	god.cancelSkillFunction = cancelJackGrenade
	god.clickTarget = nil

	startGrenade(god.selected)
	print("startJackGrenade")
end

function explodeJackGrenade()
	launchGrenade(god.selected)
	print("explodeJackGrenade")
end

function cancelJackGrenade()
	cancelGrenade(god.selected)
	print("cancelJackGrenade")
end

--------------------------------------------------
--			Habilidad c�rculo empuje de Jack	--
--------------------------------------------------
-- La habilidad del c�rculo empuje es la n�mero 2
-- La habilidad del c�rculo empuje es de tipo INMEDIATO

function jackEmpuje()
	--skillParameters = {
	--	skill = 2,
	--}
	--godEvent("OnSkillClick")

	empujarCircle(god.selected)
	print("jackEmpuje")
end
