-- TODO HACK - No estoy muy seguro pero esto igual tambi�n podr�a ir en las variables a inicializar cuando se carga el mapa.
-- La movida es que aqu� no lo veo tan mal porque est� en el contexto correcto adem�s no depende de nadie para inicializarse.
-- Lo mismo para el resto de variables dentro de cada secci�n de cada edificio.
buildingsCost = {}

--------------------------------------------------
--					Torreta						--
--------------------------------------------------

buildingsCost["Turret"] = {
	dayTime = 90,
	solenium = 100,
}

function buildTurret()
	buildParameters = {
		building = "Turret",
	}
	godEvent("OnStartBuild")
end