function fsadfsadf()
	print("4")
end

function funcionConstruir()
	print("1")
	cargarBoton(1,"torreta","fsadfsadf")
	--cargarBoton(2,"torreta","inicializarBotonesDia")
	--cargarBoton(3,"torreta","inicializarBotonesDia")
	--cargarBoton(4,"volver","inicializarBotonesDia")
	print("3")
end

function inicializarBotonesDia()
	print("inicializarBotonesDia")
	cargarBoton(1,"martillo","funcionConstruir")
	cargarBoton(2,"granada","funcionConstruir")
	cargarBoton(3,"bolazul","funcionConstruir")
	cargarBoton(4,"jeringa","funcionConstruir")
end

function cargarBoton(numBoton,imageName,funcion)
	--Guardamos en la variable local "boton" el boton que vamos a modificar
	local boton
	if numBoton == 1 then
		boton = botonControles1
    elseif numBoton == 2 then
		boton = botonControles2
    elseif numBoton == 3 then
		boton = botonControles3
	elseif numBoton == 4 then
		boton = botonControles4
    end

	--Asignamos la funcion al boton
	boton:removeAllEvents(void)
	boton:subscribeEvent("Clicked", funcion)
	
	--Cargamos las imagenes al boton
	local imageNameComun = "set:InterfazUtils image:"
	local imageNameFinal = imageNameComun .. imageName

	boton:setProperty("NormalImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 2
	boton:setProperty("HoverImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 3
	boton:setProperty("PushedImage",imageNameFinal)
	print("2")
end

function inicializarInterfazControles()
	-- Cargamos la interfaz
	CEGUI.WindowManager:getSingleton():loadWindowLayout("InterfazControles.layout")
	interfazC = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles")

	-- Activamos la ventana de interfaz
	CEGUI.System:getSingleton():setGUISheet(interfazC)
	interfazC:setVisible(true)
	interfazC:activate()
	
	--Guargamod los botones en variables para poder acceder facilmente a ellos
	botonControles1 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b1")
	botonControles2 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b2")
	botonControles3 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b3")
	botonControles4 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b4")
	
	--Inicializamos los botones del dia
	inicializarBotonesDia()
end