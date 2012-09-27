function mission1DoorTrigger(entityID)
	player = players[entityID]
	
	if ((player ~= nil) and (currentStage == 1)) then
		sacarVentana("Hemos encontrado la puerta. Hay que destruir los dos generadores para abrirla.")
		currentStage = 2
	end
end

function destroyGenerator1(entityID)
	if (currentStage == 1) then
		sacarVentana("Hemos destruido un generador esto deberia abrir la puerta.")
		currentStage = 3
	elseif (currentStage == 2) then
		sacarVentana("Hemos destruido el primer generador, solo queda uno.")
		currentStage = 3
	elseif (currentStage == 3) then
		sacarVentana("Hemos destruido los dos generadores. Matemos al vampiro jefe y larguemonos.")
		deleteEntity(getEntityID("EnemyDoor"))
		currentStage = 4
	end
end

function destroyGenerator2(entityID)
	if (currentStage == 1) then
		sacarVentana("Hemos destruido un generador esto deberia abrir la puerta.")
		currentStage = 3
	elseif (currentStage == 2) then
		sacarVentana("Hemos destruido el primer generador, solo queda uno.")
		currentStage = 3
	elseif (currentStage == 3) then
		sacarVentana("Hemos destruido los dos generadores. Matemos al vampiro jefe y larguemonos.")
		deleteEntity(getEntityID("EnemyDoor"))
		currentStage = 4
	end
end

function mission1End(entityID)
	sacarVentana("Via libre. Vamonos de aqui antes de que vengan mas chupasangres.")
	gameOver()
end

function generatorUnderAttack(entityID)
	enemyMindEventParam = { entity = entityID }
	enemyMindEvent("GeneratorUnderAttack")
end

function enemyDeath()
	-- Recompensa en solenium por cada enemigo muerto. En este caso 5.
	god.solenium = god.solenium + 5
end

function playerDeath()
	playersDeath = playersDeath + 1
	
	if (playersDeath >= 3) then
		gameOver()
	end
end

-- HACK - Inicialización super guarra de una variable que voy a necesitar.
playersDeath = 0