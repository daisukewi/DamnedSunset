function mission1DoorTrigger(entityID)
	player = players[entityID]
	
	if ((player ~= nil) and (currentStage == 1)) then
		sacarVentana("Mision 2: Destruir 2 generadores.")
		currentStage = 2
	end
end

function destroyGenerator1(entityID)
	if (currentStage == 1) then
		sacarVentana("Mision 2: Destruir el generador restante.")
		currentStage = 3
	elseif (currentStage == 2) then
		sacarVentana("Mision 3: Destruir el generador restante.")
		currentStage = 3
	elseif (currentStage == 3) then
		sacarVentana("Mision 4: Matar al vampiro jefe")
		deleteEntity(getEntityID("EnemyDoor"))
		currentStage = 4
	end
end

function destroyGenerator2(entityID)
	if (currentStage == 1) then
		sacarVentana("Mision 2: Destruir el generador restante.")
		currentStage = 3
	elseif (currentStage == 2) then
		sacarVentana("Mision 3: Destruir el generador restante.")
		currentStage = 3
	elseif (currentStage == 3) then
		sacarVentana("Mision 4: Matar al vampiro jefe")
		deleteEntity(getEntityID("EnemyDoor"))
		currentStage = 4
	end
end

function mission1End(entityID)
	sacarVentana("Mission Successful!!")
end

function generatorUnderAttack(entityID)
	enemyMindEventParam = { entity = entityID }
	enemyMindEvent("GeneratorUnderAttack")
end

function enemyDeath()
	-- Recompensa en solenium por cada enemigo muerto. En este caso 20.
	god.solenium = god.solenium + 20
end