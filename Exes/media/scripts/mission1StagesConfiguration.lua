stages = {
	
	-- Configuración etapa 1
	[1] = {
	
		-- Enemigos spawneados por cada spawn point
		spawnEnemies = {
			
			[1] = 1,
			[2] = 1,
			[3] = 1,
			[4] = 1,
			
		},
		
		-- Tiempo entre spawn de enemigos de cada spawn point (en segundos)
		spawnTime = {
			
			[1] = 30,
			[2] = 10,
			[3] = 120,
			[4] = 240,
			
		},
		
	},
	
	-- Configuración etapa 2
	[2] = {
	
		-- Enemigos spawneados por cada spawn point
		spawnEnemies = {
			
			[1] = 2,
			[2] = 2,
			[3] = 2,
			[4] = 2,
			
		},
		
		-- Tiempo entre spawn de enemigos de cada spawn point
		spawnTime = {
			
			[1] = 60,
			[2] = 120,
			[3] = 240,
			[4] = 480,
			
		},
		
	},
	
}

currentStage = 1