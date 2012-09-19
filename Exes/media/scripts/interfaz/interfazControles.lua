
function cargarInterfazControlesDia()
	-- Inicializar botones dia
	cargarBoton(1,"martillo","buildTurret")
	ocultarBoton(2)
	ocultarBoton(3)
	cargarBoton(4,"bolazul","cambiarANoche")

	CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/MenuBotonesIA"):setVisible(false)
end

function cargarInterfazControlesNoche()
	-- Inicializar botones dia
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	ocultarBoton(4)

	cargarBotonIA(1,"BotonIA1", "funcionIA1")
	cargarBotonIA(2,"BotonIA2", "funcionIA2")
	cargarBotonIA(3,"BotonIA3", "funcionIA3")
	CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/MenuBotonesIA"):setVisible(true)
end

--Las funciones de los botones redirigen a la funcion que asignemos a dicho boton
--No asignamos directamente las funciones al evento del boton, porque da problemas al cambiar el mismo evento que se esta produciendo
function clickBoton1()
	if funcionBoton1 ~= "" then
		_G[funcionBoton1]()
	end
end
function clickBoton2()
	if funcionBoton2 ~= "" then
		_G[funcionBoton2]()
	end
end
function clickBoton3()
	if funcionBoton3 ~= "" then
		_G[funcionBoton3]()
	end
end
function clickBoton4()
	if funcionBoton4 ~= "" then
		_G[funcionBoton4]()
	end
end

function clickBotonIA1()
	if funcionBotonIA1 ~= "" then
		_G[funcionBotonIA1]()
	end
	activarBotonIA(1)
end

function clickBotonIA2()
	if funcionBotonIA2 ~= "" then
		_G[funcionBotonIA2]()
	end
	activarBotonIA(2)
end

function clickBotonIA3()
	if funcionBotonIA3 ~= "" then
		_G[funcionBotonIA3]()
	end
	activarBotonIA(3)
end

--Funcion que cargar en un boton, una imagen y una funcion
function cargarBoton(numBoton,imageName,funcion)
	--Guardamos en la variable local "boton" el boton que vamos a modificar
	local boton
	if numBoton == 1 then
		boton = botonControles1
		funcionBoton1 = funcion
    elseif numBoton == 2 then
		boton = botonControles2
		funcionBoton2 = funcion
    elseif numBoton == 3 then
		boton = botonControles3
		funcionBoton3 = funcion
	elseif numBoton == 4 then
		boton = botonControles4
		funcionBoton4 = funcion
    end

	--Cargamos las imagenes al boton
	local imageNameComun = "set:BotonesHabilidades image:"
	local imageNameFinal = imageNameComun .. imageName

	boton:setProperty("NormalImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 'h'
	boton:setProperty("HoverImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 'p'
	boton:setProperty("PushedImage",imageNameFinal)
	boton:setVisible(true)
end

function ocultarBoton(numBoton)
	if numBoton == 1 then
		botonControles1:setVisible(false)
    elseif numBoton == 2 then
		botonControles2:setVisible(false)
    elseif numBoton == 3 then
		botonControles3:setVisible(false)
	elseif numBoton == 4 then
		botonControles4:setVisible(false)
    end
end

--Funcion que cargar en un boton, una imagen y una funcion
function cargarBotonIA(numBoton,imageName,funcion)
	--Guardamos en la variable local "boton" el boton que vamos a modificar
	local boton
	if numBoton == 1 then
		boton = botonIA1
		funcionBotonIA1 = funcion
    elseif numBoton == 2 then
		boton = botonIA2
		funcionBotonIA2 = funcion
    elseif numBoton == 3 then
		boton = botonIA3
		funcionBotonIA3 = funcion
    end

	--Cargamos las imagenes al boton
	local imageNameComun = "set:BotonesIA image:"

	local imageNameFinal = imageNameComun .. imageName .. 1
	boton:setProperty("NormalImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 2
	boton:setProperty("HoverImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 3
	boton:setProperty("PushedImage",imageNameFinal)
	boton:setVisible(true)
end

function ocultarBotonIA(numBoton)
	if numBoton == 1 then
		botonIA1:setVisible(false)
    elseif numBoton == 2 then
		botonIA2:setVisible(false)
    elseif numBoton == 3 then
		botonIA3:setVisible(false)
    end
end

--Inicializacion de la interfaz de los controles
function inicializarInterfazControles()
	if (interfazControles) then
		print("WARNING - inicializarInterfazControles - Interfaz ya inicializada")
	else
		-- Cargamos la interfaz
		winMgr:loadWindowLayout("InterfazControles.layout")
	end

	interfazControles = winMgr:getWindow("InterfazControles")

	--Añadimos la interfaz a la interfaz principal
	interfazPrincipal:addChildWindow(interfazControles)
	interfazControles:setVisible(true)
	interfazControles:activate()

	--Guargamod los botones en variables para poder acceder facilmente a ellos
	botonControles1 = winMgr:getWindow("InterfazControles/Menu/b1")
	botonControles2 = winMgr:getWindow("InterfazControles/Menu/b2")
	botonControles3 = winMgr:getWindow("InterfazControles/Menu/b3")
	botonControles4 = winMgr:getWindow("InterfazControles/Menu/b4")

	--Subscribimos los botones a sus funciones
	botonControles1:subscribeEvent("Clicked", clickBoton1)
	botonControles2:subscribeEvent("Clicked", clickBoton2)
	botonControles3:subscribeEvent("Clicked", clickBoton3)
	botonControles4:subscribeEvent("Clicked", clickBoton4)

	--Guargamod los botones en variables para poder acceder facilmente a ellos
	botonIA1 = winMgr:getWindow("InterfazControles/BotonIA1")
	botonIA2 = winMgr:getWindow("InterfazControles/BotonIA2")
	botonIA3 = winMgr:getWindow("InterfazControles/BotonIA3")

	--Subscribimos los botones a sus funciones
	botonIA1:subscribeEvent("Clicked", clickBotonIA1)
	botonIA2:subscribeEvent("Clicked", clickBotonIA2)
	botonIA3:subscribeEvent("Clicked", clickBotonIA3)

	winMgr:getWindow("InterfazControles/MenuBotonesIA"):setVisible(false)
end
