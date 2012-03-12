function processMap(map) 
	for key, value in pairs(map) do
		print ("Leyendo entidad: " .. key);
		--[[beginEntity(key)
			for k,v in pairs(value) do
				if type(v) == "boolean" then
					if v==true then
						newAttrib(k, "true")
					else
						newAttrib(k, "false")
					end
				--elseif type(v) == "table" then		Sería algo así si las posiciones fueran tablas en lugar de strings.
					--newAttrib(k, v[0], v[1], v[2])	Habría que implementar la función newAttrib en c++ para que coja tablas.
				else
					newAttrib(k, v)
				end
			end
		endEntity(key)]]
	end
end