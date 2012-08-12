-- TODO HACK - No estoy muy seguro pero esto igual también podría ir en las variables a inicializar cuando se carga el mapa.
-- La movida es que aquí no lo veo tan mal porque está en el contexto correcto además no depende de nadie para inicializarse.
-- Lo mismo para el resto de variables dentro de cada sección de cada edificio.
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