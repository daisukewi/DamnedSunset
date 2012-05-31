function loadScripts()
	SManager:loadScript("utils")
	SManager:loadScript("playerScript")
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
	--SManager:loadScript("interfaz/interfazControles")
	
	-- Scripts de misión.
	SManager:loadScript("mission1StagesConfiguration")
	SManager:loadScript("mission1Behaviour")
end