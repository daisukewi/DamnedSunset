function loadScripts()
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
	
	-- Scripts de la máquina de estados de la IA de la supermente.
	SManager:loadScript("enemyMindNormalState")
	SManager:loadScript("enemyMindScript")
	
	-- Interfaz
	SManager:loadScript("interfaz/interfazControles")
	SManager:loadScript("interfaz")
	
	-- Scripts de misión.
	SManager:loadScript("mission1StagesConfiguration")
	SManager:loadScript("mission1Behaviour")
end