function processMap(map)
	-- Creo una variable local donde voy a guardar el mapa para parsearlo al final de todas las entidades.
	local gridMap
	-- Creo un objeto de C++ de tipo Parser.
	local cParser = Parser()
	-- Me recorro toda la tabla de entidades anteriormente cargada
	for key, value in pairs(map) do
	
		-- Aviso al parser de que empieza la definición de una nueva entidad
		cParser:beginEntity(key)
			
			-- A su vez cada entidad es una tabla con todos sus atributos así que me la recorro
			for k, v in pairs(value) do
			
				-- Si el valor que estoy leyendo es de tipo booleano, se lo paso al parser convertido en string
				if (type(v) == "boolean") then
					if (v == true) then
						cParser:newAttrib(k, "true")
					else
						cParser:newAttrib(k, "false")
					end
				elseif (type(v) == "table") then
					-- Si el valor que estoy leyendo es de tipo tabla, primero compruebo si la longitud es menor que tres ya que
					-- de ser así se trata de un vector.
					if (rawlen(v) <= 3) then
						s = (v[1] .. " " .. v[2])
						if (rawlen(v) == 3) then
							s = (s .. " " .. v[3])
						end
					-- Si la longitud de la tabla es mayor de tres, entonces es la definición de las casillas del mapa.
					else
						-- Me guardo el mapa para parsearlo cuando ya haya parseado todas las entidades
						gridMap = v
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
	
	-- Cuando ya he parseado todas las entidades, parseo el mapa en una función a parte.
	if (gridMap ~= nil) then
		processGrid(gridMap, cParser)
	end
	
end

function processGrid(grid, cParser)
	-- Aviso que empiezo el parseo de las celdas del mapa.
	cParser:beginGrid(rawlen(grid), rawlen(grid[1]))
	
	-- Hago el parseo en sí con un doble for.
	for y, val1 in pairs(grid) do
		for x, val2 in pairs(val1) do
			cParser:newTile(val2, (y - 1), (x - 1))
		end
	end
end