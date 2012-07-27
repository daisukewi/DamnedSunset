function loadScripts()
	SManager:loadScript("parametersLoader")
	SManager:loadScript("utils")

	-- Scripts de la máquina de estados de la IA de los personajes
	SManager:loadScript("playerIAScript")
	SManager:loadScript("playerSecondaryIAScript")
	SManager:loadScript("habilities")

	-- Scripts de la máquina de estados de la IA de los enemigos.
	SManager:loadScript("enemyIdleState")
	SManager:loadScript("enemyAttackState")
	SManager:loadScript("enemyMoveState")
	SManager:loadScript("enemyRunState")
	SManager:loadScript("enemyScript")

	-- Scripts de la maquina de estados de God
	SManager:loadScript("godSelectionState")
	SManager:loadScript("godBuildingState")

	-- Scripts de la máquina de estados de la IA de la supermente.
	SManager:loadScript("enemyMindNightState")
	SManager:loadScript("enemyMindDayState")
	SManager:loadScript("enemyMindScript")

	-- Interfaz
	SManager:loadScript("interfaz/interfazControles")
	SManager:loadScript("interfaz/interfazNoche")
	SManager:loadScript("interfaz/interfazPrincipal")
	SManager:loadScript("interfaz/interfazDia")

	-- Scripts de misión.
	SManager:loadScript("mission1StagesConfiguration")
	SManager:loadScript("mission1Behaviour")

	-- Scipt del panel solar
	SManager:loadScript("panelSolar")
end
