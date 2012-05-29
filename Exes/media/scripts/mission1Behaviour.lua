function mission1DoorTrigger(entityID)
	print("He recibido el evento del trigger.")
	player = players[entityID]
	
	if ((player ~= nil) and (currentStage == 1)) then
		print("He reconocido a un jugador como entidad que ha chocado contra mi. Cambiando de estado de la misión...")
		currentStage = 2
	end
end