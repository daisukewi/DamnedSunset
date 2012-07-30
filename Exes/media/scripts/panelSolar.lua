function activarEdificiosCercanos(entity, activar)
	-- Me recorro todos los edificios del mapa
	for key, value in pairs(buildings) do
		local coordX = buildings[entity].posX - value.posX
		local coordY = buildings[entity].posY - value.posY
		local coordZ = buildings[entity].posZ - value.posZ
		local ratio  = Archetype.PanelSolar.radioEnergy
		-- Si el edificio está a una distancia del panel solar menor que el radio, activamos el edificio
		if ((coordX * coordX) + (coordY * coordY) + (coordZ * coordZ) <= ratio * ratio) then
			if activar then
				value.activate = value.activate + 1
				print("Edificio activadooooo!!!\n")
			else
				if value.activate <= 0 then
					value.activate = 0
					print("El edificio no debería tener el activate negativo")
				else
					value.activate = value.activate - 1
				end

			end
		end
	end

end
