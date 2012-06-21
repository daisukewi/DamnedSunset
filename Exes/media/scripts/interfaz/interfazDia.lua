function inicializarInterfazDia()
	if (interfazDia) then
		print("WARNING - inicializarInterfazDia - Interfaz ya inicializada")
	else
		-- Cargamos la interfaz
		winMgr:loadWindowLayout("InterfazDia.layout")
		interfazDia = winMgr:getWindow("InterfazDia")

		--Añadimos la interfaz a la interfaz principal
		interfazPrincipal:addChildWindow(interfazDia)
		
		winMgr:getWindow("InterfazDia/BotonAnochecer"):subscribeEvent("Clicked", "cambiarANoche")
	end
end

function activarInterfazDia()
	if (interfazDia) then
		-- Activamos la ventana de interfaz
		interfazDia:setVisible(true)
		interfazDia:activate()
	end
end

function desactivarInterfazDia()
	if (interfazDia) then
		interfazDia:deactivate()
		interfazDia:setVisible(false)
	end
end

function actualizarHorasAmanecer(timeAmanecer)
	if (interfazDia) then
		minutosAmanecer = timeAmanecer
		local horas = math.floor(minutosAmanecer/60)
		local minutos = minutosAmanecer - horas * 60
		local textoIntermedio
		if (minutos >= 10) then
			textoIntermedio = ":"
		else
			textoIntermedio = ":0"
		end
		winMgr:getWindow("InterfaDia/Recuros/Amanecer"):setText(horas .. textoIntermedio .. minutos)
	end
end

function actualizarSolenium(cantidadSolenium)
	if (interfazDia) then
		solenium = cantidadSolenium
		winMgr:getWindow("InterfaDia/Recuros/Solenium"):setText(solenium)
	end
end