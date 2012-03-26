function processMap(map)
	-- Creo un objeto de C++ de tipo Parser.
	local cParser = Parser()
	-- Me recorro toda la tabla de entidades anteriormente cargada
	for key, value in pairs(map) do
	
		-- Aviso al parser de que empieza la definición de una nueva entidad
		cParser:beginEntity(key)
			
			-- A su ve cada entidad es una tabla con todos sus atributos así que me la recorro
			for k, v in pairs(value) do
			
				-- Si el valor que estoy leyendo es de tipo booleano, se lo paso al parser convertido en string
				if (type(v) == "boolean") then
					if (v == true) then
						cParser:newAttrib(k, "true")
					else
						cParser:newAttrib(k, "false")
					end
				-- Si el valor que estoy leyendo es de tipo tabla, agrupo los elementos de la tabla separados por un espacio y 
				-- se lo paso al parser en formato string
				elseif (type(v) == "table") then
					s = (v[1] .. " " .. v[2])
					if (rawlen(v) == 3) then
						s = (s .. " " .. v[3])
					end
					cParser:newAttrib(k, s)
				-- En cualquier otro caso, le paso el valor al parser para que lo guarde como un string.
				else
					cParser:newAttrib(k, tostring(v))
				end
				
			end
			
		-- Finalmente, cierro el parseo de la entidad actual.
		cParser:endEntity()
		
	end
end