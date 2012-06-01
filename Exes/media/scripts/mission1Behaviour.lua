function mission1DoorTrigger(entityID)
	print("He recibido el evento del trigger.")
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
	sacarVentana("Mission Successful!")
end