Archetype = {

	World = {
		type = "World",
		tag = "world",
		physic_collision_group = 1,
		billboardMoverMaterial = "circuloSeleccion",
		billboardMoverDimension = 10.0,
		billboardMoverTime = 2.0,
		position = {0, 0, 0},
		orientation = 0,
	},

	PlayerGod = {
		type = "PlayerGod",
		mouseDistance = 100,
		cameraDistance = 150,
		cameraVelocity = 500,
		mouseVelocity = 4,
		dayTime = 10000,
		dayTimeAlarm = 1000,
		nightTime = 1000000,
		speed = 0.15,
	},

	Obstacle = {
		type = "Obstacle",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle90x1 = {
		type = "Obstacle90x1",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle1x90 = {
		type = "Obstacle1x90",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle5x1 = {
		type = "Obstacle5x1",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle10x1 = {
		type = "Obstacle10x1",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle2x1 = {
		type = "Obstacle2x1",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle1x5 = {
		type = "Obstacle1x5",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle1x10 = {
		type = "Obstacle1x10",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Obstacle1x2 = {
		type = "Obstacle1x2",
		tag = "world",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
		disableComponent = "CPhysicEntity"
	},

	Entity = {
		type = "Entity",
		position = {0, 0, 0},
		orientation = 0,
		model = "torreta_pie.mesh",
	},

	PhantomTurret = {
		type = "PhantomTurret",
		position = {0, -50, 0},
		orientation = 0,
		dimension = { 1, 1 },
		model = "torreta_pie.mesh",
	},

	Turret = {
		type = "Turret",
		tag = "playerBuilding",
		position = {0, 0, 0},
		orientation = 0,
		building_size = "1 1",
		dimension = { 1, 1 },
		model = "torreta_pie.mesh",
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 8, 8 },
		physic_height = 16,
		physic_radius = 16,
		physic_collision_group = 2,
		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_static",
		trigger = true,
		trigger_radius = 25,
		trigger_height = 1,
		trigger_collision_group = 3,
		precision = 0.1,
		damage = 2,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,12.0,0.0},

		life = 100.0,
		maxLife = 100.0,

		timeBetweenShoots = 5.0,
	},

	PanelSolar = {
		type = "PanelSolar",
		tag = "playerBuilding",
		position = {0, 0, 0},
		orientation = 0,
		building_size = "1 1",
		model = "torreta_pie.mesh",
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 8, 8 },
		physic_height = 16,
		physic_radius = 16,
		physic_collision_group = 2,

		radioEnergy = 100.0,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,12.0,0.0},

		life = 100.0,
		maxLife = 100.0,
	},

	EnemyEnergyGenerator = {
		type = "EnemyEnergyGenerator",
		tag = "enemyBuilding",
		position = {0, 0, 0},
		scale = 10.0,
		orientation = 0,
		model = "torreta_pie.mesh",
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 8, 8 },
		physic_height = 16,
		physic_radius = 16,
		physic_collision_group = 2,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,12.0,0.0},

		life = 100.0,
		maxLife = 100.0,
	},

	DoorStage2Trigger = {
		type = "DoorStage2Trigger",
		trigger = true,
		trigger_shape = "trigger_box",
		trigger_type = "trigger_static",
		trigger_collision_group = 3,
	},

	Barril = {
		type = "Barril",
		position = {0, 1, 0},
		orientation = 0,
		model = "barril.mesh",
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 2.3, 2.5, 2.3 },
		physic_height = 2,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 6,
	},

	EnemyMind = {
		type = "EnemyMind",
	},

	Enemies = {
		type = "Enemies",
		periodo = 10000,
		automaticSpawn = false,
		model = "esfera.mesh"
	},

	Enemy = {
		type = "Enemy",
		tag = "enemy",
		orientation = 0,
		life = 100.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "zombiearm.mesh",
		defaultAnimation = "Stand",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 5.5,
		physic_height = 10,
		physic_collision_group = 5,
		speed = 0.02,
		angularSpeed = 0.005,
		accel = 0.001,
		angularAccel = 0.0001,
		movementTolerance = 7.0,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,25.0,0.0},

		billboardSeleccionMaterial = "circuloSeleccion",
		billboardSeleccionWith = 15.0,
		billboardSeleccionHeight = 15.0,

		afectaEmpujar = 100,

		distOfView = 100,

		initState = 1,
		memInitPoint = true,
		runLifeThreshold = 50,

		damage = 10,
		attackCoolDown = 250,

		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_kinematic",
		trigger = true,
		trigger_radius = 50,
		trigger_height = 5,
		trigger_collision_group = 3,

		duracionCarga = 1000,
		coolDownCarga = 10000,
		
		lifeCureSound = "",
		lifeCureEffect = "",
		lifeDamageSound = "",
		lifeDamageEffect = "Blood",
		
		distanceAttackSound = "RifleShot1.ogg",
		distanceAttackEffect = "",
		
		healSound = "",
		healEffect = "",
		
		poisonSound = "",
		poisonEffect = "",
	},

	Granada = {
		type = "Granada",
		position = {0, 3, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 12.0,
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 1.0, 1.0, 1.0 },
		physic_height = 2.0,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 9,

		damage = 60.0,
		timeEmpujar = 0.3,
		distEmpujarSeg = 150.0,
	},

	GranadaAturdir = {
		type = "GranadaAturdir",
		position = {0, 3, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 12.0,
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 1.0, 1.0, 1.0 },
		physic_height = 2.0,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 9,

		time = 3.0,
	},

	GranadaEnvenenar = {
		type = "GranadaEnvenenar",
		position = {0, 3, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 12.0,
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 1.0, 1.0, 1.0 },
		physic_height = 2.0,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 9,

		time = 10.0,
		damage = 20.0,
		count = 4.0,
	},

	BolaTeltr = {
		type = "BolaTeltr",
		position = {0, 3, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 12.0,
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 1.0, 1.0, 1.0 },
		physic_height = 2.0,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 9,
		distEmpujarSeg = 150.0,

		dimension = {1, 1},
	},

	Jack = {
		type = "Jack",
		tag = "Player",
		position = {0, 5, 0},
		orientation = 270,
		life = 100.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "Jack.mesh",
		defaultAnimation = "Stand",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 5.5,
		physic_height = 10,
		physic_collision_group = 4,
		speed = 0.05,
		angularSpeed = 50.0,
		accel = 0.001,
		angularAccel = 11.0,
		movementTolerance = 3.0,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 8.0,
		billboardLifeHeight = 1.0,
		billboardLifePosition = {0.0,20.0,0.0},

		billboardSeleccionMaterial = "circuloSeleccion",
		billboardMultipleSeleccionMaterial = "circuloMultipleSeleccion",
		billboardSeleccionWith = 10.0,
		billboardSeleccionHeight = 10.0,

		billboardLanzamientoMaterial = "circuloSeleccion",
		billboardLanzamientoWith = 150.0,
		billboardLanzamientoHeight = 150.0,
		alcanceGranada = 70.0,
		nombreGranada = "Granada",

		afectaEmpujar = 100,

		timeRabia = 0.3,
		distRabiaSeg = 80.0,

		timeBurla = 5000,

		initState = 1,

		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_kinematic",
		trigger = true,
		trigger_radius = 150,
		trigger_collision_group = 3,

		damage = 10,

		selection_shape = "trigger_capsule",
		selection_type = "trigger_kinematic",
		selection_trigger = true,
		selection_radius = 8,
		selection_height = 12,
		selection_collision_group = 7,

		reduceDamageTime = 5000,
		reduceDamageDistance = 100,
		reduceDamage = -1.0,
		
		
		lifeCureSound = "",
		lifeCureEffect = "",
		lifeDamageSound = "",
		lifeDamageEffect = "Blood",
		
		distanceAttackSound = "RifleShot1.ogg",
		distanceAttackEffect = "",
		
		healSound = "",
		healEffect = "",
		
		poisonSound = "",
		poisonEffect = "",
		
		
	},

	Erick = {
		type = "Erick",
		tag = "Player",
		position = {0, 5, 0},
		orientation = 270,
		life = 100.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "Erick.mesh",
		defaultAnimation = "Stand",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 5.5,
		physic_height = 10,
		physic_collision_group = 4,
		speed = 0.05,
		angularSpeed = 50.0,
		accel = 0.001,
		angularAccel = 11.0,
		movementTolerance = 3.0,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 8.0,
		billboardLifeHeight = 1.0,
		billboardLifePosition = {0.0,20.0,0.0},

		billboardSeleccionMaterial = "circuloSeleccion",
		billboardMultipleSeleccionMaterial = "circuloMultipleSeleccion",
		billboardSeleccionWith = 10.0,
		billboardSeleccionHeight = 10.0,

		billboardLanzamientoMaterial = "circuloSeleccion",
		billboardLanzamientoWith = 150.0,
		billboardLanzamientoHeight = 150.0,
		alcanceGranada = 70.0,
		nombreGranada = "GranadaAturdir",

		billboardDisparoMaterial = "circuloSeleccion",
		billboardDisparoWith = 150.0,
		billboardDisparoHeight = 150.0,

		billboardLlamasMaterial = "circuloSeleccion",
		billboardLlamasWith = 150.0,
		billboardLlamasHeight = 150.0,

		afectaEmpujar = 100,

		angleDisparoPotente = 60,
		radioDisparoPotente = 100,
		damageDisparoPotente = 20,

		angleLanzallamas = 25,
		radioLanzallamas = 80,
		damageLanzallamas = 15,
		timeLanzallamas = 3000,
		frecDamageLlamas = 750,

		initState = 1,

		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_kinematic",
		trigger = true,
		trigger_radius = 80,
		trigger_collision_group = 3,

		damage = 33,

		selection_shape = "trigger_capsule",
		selection_type = "trigger_kinematic",
		selection_trigger = true,
		selection_radius = 8,
		selection_height = 12,
		selection_collision_group = 7,
		
		lifeCureSound = "",
		lifeCureEffect = "",
		lifeDamageSound = "",
		lifeDamageEffect = "Blood",
		
		distanceAttackSound = "RifleShot1.ogg",
		distanceAttackEffect = "",
		
		healSound = "",
		healEffect = "",
		
		poisonSound = "",
		poisonEffect = "",
	},

	Norah = {
		type = "Norah",
		tag = "Player",
		position = {0, 5, 0},
		orientation = 270,
		life = 100.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "Norah.mesh",
		defaultAnimation = "Stand",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 5.5,
		physic_height = 10,
		physic_collision_group = 4,
		speed = 0.05,
		angularSpeed = 50.0,
		accel = 0.001,
		angularAccel = 11.0,
		movementTolerance = 3.0,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 8.0,
		billboardLifeHeight = 1.0,
		billboardLifePosition = {0.0,20.0,0.0},

		billboardSeleccionMaterial = "circuloSeleccion",
		billboardMultipleSeleccionMaterial = "circuloMultipleSeleccion",
		billboardSeleccionWith = 10.0,
		billboardSeleccionHeight = 10.0,

		billboardLanzamientoMaterial = "circuloSeleccion",
		billboardLanzamientoWith = 150.0,
		billboardLanzamientoHeight = 150.0,
		alcanceGranada = 70.0,
		nombreGranada = "GranadaEnvenenar",

		afectaEmpujar = 100,

		initState = 1,

		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_kinematic",
		trigger = true,
		trigger_radius = 80,
		trigger_collision_group = 3,

		damage = 33,


		selection_shape = "trigger_capsule",
		selection_type = "trigger_kinematic",
		selection_trigger = true,
		selection_radius = 8,
		selection_height = 12,
		selection_collision_group = 7,


		healZoneTime = 5000,
		healZoneDistance = 100,
		healZoneValue = 30,

		lifeCureSound = "",
		lifeCureEffect = "",
		lifeDamageSound = "",
		lifeDamageEffect = "Blood",
		
		distanceAttackSound = "RifleShot1.ogg",
		distanceAttackEffect = "",
		
		healSound = "",
		healEffect = "",
		
		poisonSound = "",
		poisonEffect = "",
		
	},

	Waypoint = {
		type = "Waypoint",
		position = {0, 0, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 8.0,
	},

	CentroMando = {
		type = "CentroMando",
		tag = "playerBuilding",
		position = {0, 0, 0},
		cupulaRadius = 150.0,
		scale = 10.0,
		orientation = 180,
		model = "centro_informatico.mesh",
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 8, 8 },
		physic_height = 16,
		physic_radius = 16,
		physic_collision_group = 2,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,12.0,0.0},

		life = 100.0,
		maxLife = 100.0,
	},

	EnemyDoor = {
		type = "EnemyDoor",
		tag = "enemyBuilding",
		position = {0, 0, 0},
		cupulaPosition = {0, 0, 0},
		cupulaRadius = 100.0,
		scale = 10.0,
		orientation = 0,
		model = "torreta_pie.mesh",
		physic_entity = "simple",
		physic_type = "kinematic",
		physic_shape = "box",
		physic_dimensions = { 8, 8, 8 },
		physic_height = 16,
		physic_radius = 16,
		physic_collision_group = 2,
	},

	EnemyBoss = {
		type = "EnemyBoss",
		tag = "enemy",
		orientation = 0,
		life = 500.0,
		maxLife = 500.0,
		isPlayer = false,
		model = "loco.mesh",
		defaultAnimation = "Stand",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 5,
		physic_height = 8,
		physic_collision_group = 5,
		speed = 0.02,
		angularSpeed = 0.005,
		accel = 0.001,
		angularAccel = 0.0001,
		movementTolerance = 7.0,

		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,12.0,0.0},

		billboardSeleccionMaterial = "circuloSeleccion",
		billboardSeleccionWith = 15.0,
		billboardSeleccionHeight = 15.0,

		afectaEmpujar = 100,

		distOfView = 100,

		initState = 1,
		memInitPoint = true,
		runLifeThreshold = 0,

		damage = 30,

		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_kinematic",
		trigger = true,
		trigger_radius = 75,
		trigger_height = 5,
		trigger_collision_group = 3,
	},

}
