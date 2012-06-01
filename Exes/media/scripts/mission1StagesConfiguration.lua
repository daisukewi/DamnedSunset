stages = {
	
	-- Configuración etapa 1
	[1] = {
	
		-- Enemigos spawneados por cada spawn point
		spawnEnemies = {
			
			[1] = 5,
			[2] = 6,
			[3] = 5,
			[4] = 4,
			
		},
		
		-- Tiempo entre spawn de enemigos de cada spawn point (en segundos)
		spawnTime = {
			
			[1] = 30,
			[2] = 30,
			[3] = 40,
			[4] = 40,
			
		},
		
	},
	
	-- Configuración etapa 2
	[2] = {
	
		-- Enemigos spawneados por cada spawn point
		spawnEnemies = {
			
			[1] = 5,
			[2] = 5,
			[3] = 6,
			[4] = 5,
			
		},
		
		-- Tiempo entre spawn de enemigos de cada spawn point
		spawnTime = {
			
			[1] = 10,
			[2] = 10,
			[3] = 20,
			[4] = 20,
			
		},
		
	},
	
}

currentStage = 1