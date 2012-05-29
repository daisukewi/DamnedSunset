function loadScripts()
	SManager:loadScript("utils")
	SManager:loadScript("playerScript")
	
	-- Scripts de la m�quina de estados de la IA de los enemigos.
	SManager:loadScript("enemyIdleState")
	SManager:loadScript("enemyAttackState")
	SManager:loadScript("enemyMoveState")
	SManager:loadScript("enemyRunState")
	SManager:loadScript("enemyScript")
	
	-- Scripts de la m�quina de estados de la IA de la supermente.
	SManager:loadScript("enemyMindNormalState")
	SManager:loadScript("enemyMindScript")
	
	-- Interfaz
	--SManager:loadScript("interfazControles")
end