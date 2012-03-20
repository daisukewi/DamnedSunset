Map = {

	Grid = {
		type = "Grid",
		width = 20,
		height = 20,
		grid_size = 16,
	},

	World = {
		type = "World",
		position = {0,0,0},
		orientation = 0,
		model = "plane.mesh",
		static = true,
		physic_entity = "simple",
		physic_type = "static",
		physic_shape = "box",
		physic_normal = { 0, 1, 0 },
		physic_dimensions = { 160.0, 0.5, 160.0 },
		physic_height = 1,
		physic_radius = 1,
	},

	Jack = {
		type = "Player",
		position = {0, 5, 0},
		life = 100.0,
	},
	
	Erick = {
		type = "Player",
		position = {20, 5, 0},
		orientation = 90,
		life = 80.0,
	},
	
	Amor = {
		type = "Player",
		position = {40, 5, 0},
		life = 10.0,
	},

	Enemy = {
		type = "Enemy",
		position = {20, 5, 49},
	},

	EnemiesGenerator = {
		type = "Enemies",
		model = "torreta_pie.mesh",
	},
	
	Camera = {
		type = "Camera",
		distance = 60,
		height = 100,
		targetName = "PlayerGod",
		targetDistance = 10,
		targetHeight = 7,
	},
	
	PlayerGod = {
		type = "PlayerGod",
		isPlayer = true,
		position = {0, 0, 0},
		orientation = 225,
		isTargetCamera = true,
		northVision = 20,
		southVision = 40,
		eastVision = 25,
		westVision = 30,
		northEntity = 22,
		southEntity = 10,
		eastEntity = 17,
		westEntity = 17,
	},
	
	Sol = {
		type = "Sun",
		position = {0, 10, -100},
		orientation = 0,
		model = "esfera.mesh",
		scale = 30.0,
		speed = 5.0,
		inclination = 120.0,
	},
	
	Torreta1 = {
		type = "Turret",
		grid_position = "10 10",
		position = {15, 0, 5},	
	},
	
	Barril1 = {
		type = "Barril",
	},	
	
	Barril2 = {
		type = "Barril",
		position = {5, 10, 15},
	},	
	
	Barril3 = {
		type = "Barril",
		position = {-5, 1, 15},
	},
	
	Road0_0 = {
		type = "Road",
		position = { 0, 0 },
		model = "road.mesh",
	},

	Road0_1 = {
		type = "Road",
		position = { 0, 1 },
		model = "road.mesh",
	},

	Road0_2 = {
		type = "Road",
		position = { 0, 2 },
		model = "road.mesh",
	},

	Road0_3 = {
		type = "Road",
		position = { 0, 3 },
		model = "road.mesh",
	},

	Sand0_4 = {
		type = "Sand",
		position = { 0, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_5 = {
		type = "Sand",
		position = { 0, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_6 = {
		type = "Sand",
		position = { 0, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_7 = {
		type = "Sand",
		position = { 0, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_8 = {
		type = "Sand",
		position = { 0, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_9 = {
		type = "Sand",
		position = { 0, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_10 = {
		type = "Sand",
		position = { 0, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_11 = {
		type = "Sand",
		position = { 0, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_12 = {
		type = "Sand",
		position = { 0, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_13 = {
		type = "Sand",
		position = { 0, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_14 = {
		type = "Sand",
		position = { 0, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_15 = {
		type = "Sand",
		position = { 0, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_16 = {
		type = "Sand",
		position = { 0, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_17 = {
		type = "Sand",
		position = { 0, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_18 = {
		type = "Sand",
		position = { 0, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand0_19 = {
		type = "Sand",
		position = { 0, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_0 = {
		type = "Sand",
		position = { 1, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Road1_1 = {
		type = "Road",
		position = { 1, 1 },
		model = "road.mesh",
	},

	Road1_2 = {
		type = "Road",
		position = { 1, 2 },
		model = "road.mesh",
	},

	Road1_3 = {
		type = "Road",
		position = { 1, 3 },
		model = "road.mesh",
	},

	Road1_4 = {
		type = "Road",
		position = { 1, 4 },
		model = "road.mesh",
	},

	Sand1_5 = {
		type = "Sand",
		position = { 1, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_6 = {
		type = "Sand",
		position = { 1, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_7 = {
		type = "Sand",
		position = { 1, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_8 = {
		type = "Sand",
		position = { 1, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_9 = {
		type = "Sand",
		position = { 1, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_10 = {
		type = "Sand",
		position = { 1, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_11 = {
		type = "Sand",
		position = { 1, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_12 = {
		type = "Sand",
		position = { 1, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_13 = {
		type = "Sand",
		position = { 1, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_14 = {
		type = "Sand",
		position = { 1, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_15 = {
		type = "Sand",
		position = { 1, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_16 = {
		type = "Sand",
		position = { 1, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_17 = {
		type = "Sand",
		position = { 1, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_18 = {
		type = "Sand",
		position = { 1, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand1_19 = {
		type = "Sand",
		position = { 1, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_0 = {
		type = "Sand",
		position = { 2, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_1 = {
		type = "Sand",
		position = { 2, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Road2_2 = {
		type = "Road",
		position = { 2, 2 },
		model = "road.mesh",
	},

	Road2_3 = {
		type = "Road",
		position = { 2, 3 },
		model = "road.mesh",
	},

	Road2_4 = {
		type = "Road",
		position = { 2, 4 },
		model = "road.mesh",
	},

	Road2_5 = {
		type = "Road",
		position = { 2, 5 },
		model = "road.mesh",
	},

	Sand2_6 = {
		type = "Sand",
		position = { 2, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_7 = {
		type = "Sand",
		position = { 2, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_8 = {
		type = "Sand",
		position = { 2, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_9 = {
		type = "Sand",
		position = { 2, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_10 = {
		type = "Sand",
		position = { 2, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_11 = {
		type = "Sand",
		position = { 2, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_12 = {
		type = "Sand",
		position = { 2, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_13 = {
		type = "Sand",
		position = { 2, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_14 = {
		type = "Sand",
		position = { 2, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_15 = {
		type = "Sand",
		position = { 2, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_16 = {
		type = "Sand",
		position = { 2, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_17 = {
		type = "Sand",
		position = { 2, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_18 = {
		type = "Sand",
		position = { 2, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand2_19 = {
		type = "Sand",
		position = { 2, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_0 = {
		type = "Sand",
		position = { 3, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_1 = {
		type = "Sand",
		position = { 3, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_2 = {
		type = "Sand",
		position = { 3, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Road3_3 = {
		type = "Road",
		position = { 3, 3 },
		model = "road.mesh",
	},

	Road3_4 = {
		type = "Road",
		position = { 3, 4 },
		model = "road.mesh",
	},

	Road3_5 = {
		type = "Road",
		position = { 3, 5 },
		model = "road.mesh",
	},

	Road3_6 = {
		type = "Road",
		position = { 3, 6 },
		model = "road.mesh",
	},

	Sand3_7 = {
		type = "Sand",
		position = { 3, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_8 = {
		type = "Sand",
		position = { 3, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_9 = {
		type = "Sand",
		position = { 3, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_10 = {
		type = "Sand",
		position = { 3, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_11 = {
		type = "Sand",
		position = { 3, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_12 = {
		type = "Sand",
		position = { 3, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_13 = {
		type = "Sand",
		position = { 3, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_14 = {
		type = "Sand",
		position = { 3, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_15 = {
		type = "Sand",
		position = { 3, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_16 = {
		type = "Sand",
		position = { 3, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_17 = {
		type = "Sand",
		position = { 3, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_18 = {
		type = "Sand",
		position = { 3, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand3_19 = {
		type = "Sand",
		position = { 3, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_0 = {
		type = "Sand",
		position = { 4, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_1 = {
		type = "Sand",
		position = { 4, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_2 = {
		type = "Sand",
		position = { 4, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_3 = {
		type = "Sand",
		position = { 4, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Road4_4 = {
		type = "Road",
		position = { 4, 4 },
		model = "road.mesh",
	},

	Road4_5 = {
		type = "Road",
		position = { 4, 5 },
		model = "road.mesh",
	},

	Road4_6 = {
		type = "Road",
		position = { 4, 6 },
		model = "road.mesh",
	},

	Road4_7 = {
		type = "Road",
		position = { 4, 7 },
		model = "road.mesh",
	},

	Sand4_8 = {
		type = "Sand",
		position = { 4, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_9 = {
		type = "Sand",
		position = { 4, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_10 = {
		type = "Sand",
		position = { 4, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_11 = {
		type = "Sand",
		position = { 4, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_12 = {
		type = "Sand",
		position = { 4, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_13 = {
		type = "Sand",
		position = { 4, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_14 = {
		type = "Sand",
		position = { 4, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_15 = {
		type = "Sand",
		position = { 4, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_16 = {
		type = "Sand",
		position = { 4, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_17 = {
		type = "Sand",
		position = { 4, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_18 = {
		type = "Sand",
		position = { 4, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand4_19 = {
		type = "Sand",
		position = { 4, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_0 = {
		type = "Sand",
		position = { 5, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_1 = {
		type = "Sand",
		position = { 5, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_2 = {
		type = "Sand",
		position = { 5, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_3 = {
		type = "Sand",
		position = { 5, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_4 = {
		type = "Sand",
		position = { 5, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Road5_5 = {
		type = "Road",
		position = { 5, 5 },
		model = "road.mesh",
	},

	Road5_6 = {
		type = "Road",
		position = { 5, 6 },
		model = "road.mesh",
	},

	Road5_7 = {
		type = "Road",
		position = { 5, 7 },
		model = "road.mesh",
	},

	Road5_8 = {
		type = "Road",
		position = { 5, 8 },
		model = "road.mesh",
	},

	Sand5_9 = {
		type = "Sand",
		position = { 5, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_10 = {
		type = "Sand",
		position = { 5, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_11 = {
		type = "Sand",
		position = { 5, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_12 = {
		type = "Sand",
		position = { 5, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_13 = {
		type = "Sand",
		position = { 5, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_14 = {
		type = "Sand",
		position = { 5, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_15 = {
		type = "Sand",
		position = { 5, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_16 = {
		type = "Sand",
		position = { 5, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_17 = {
		type = "Sand",
		position = { 5, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_18 = {
		type = "Sand",
		position = { 5, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand5_19 = {
		type = "Sand",
		position = { 5, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_0 = {
		type = "Sand",
		position = { 6, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_1 = {
		type = "Sand",
		position = { 6, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_2 = {
		type = "Sand",
		position = { 6, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_3 = {
		type = "Sand",
		position = { 6, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_4 = {
		type = "Sand",
		position = { 6, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_5 = {
		type = "Sand",
		position = { 6, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Road6_6 = {
		type = "Road",
		position = { 6, 6 },
		model = "road.mesh",
	},

	Road6_7 = {
		type = "Road",
		position = { 6, 7 },
		model = "road.mesh",
	},

	Road6_8 = {
		type = "Road",
		position = { 6, 8 },
		model = "road.mesh",
	},

	Road6_9 = {
		type = "Road",
		position = { 6, 9 },
		model = "road.mesh",
	},

	Sand6_10 = {
		type = "Sand",
		position = { 6, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_11 = {
		type = "Sand",
		position = { 6, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_12 = {
		type = "Sand",
		position = { 6, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_13 = {
		type = "Sand",
		position = { 6, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_14 = {
		type = "Sand",
		position = { 6, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_15 = {
		type = "Sand",
		position = { 6, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_16 = {
		type = "Sand",
		position = { 6, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_17 = {
		type = "Sand",
		position = { 6, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_18 = {
		type = "Sand",
		position = { 6, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand6_19 = {
		type = "Sand",
		position = { 6, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_0 = {
		type = "Sand",
		position = { 7, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_1 = {
		type = "Sand",
		position = { 7, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_2 = {
		type = "Sand",
		position = { 7, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_3 = {
		type = "Sand",
		position = { 7, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_4 = {
		type = "Sand",
		position = { 7, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_5 = {
		type = "Sand",
		position = { 7, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_6 = {
		type = "Sand",
		position = { 7, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Road7_7 = {
		type = "Road",
		position = { 7, 7 },
		model = "road.mesh",
	},

	Road7_8 = {
		type = "Road",
		position = { 7, 8 },
		model = "road.mesh",
	},

	Road7_9 = {
		type = "Road",
		position = { 7, 9 },
		model = "road.mesh",
	},

	Road7_10 = {
		type = "Road",
		position = { 7, 10 },
		model = "road.mesh",
	},

	Sand7_11 = {
		type = "Sand",
		position = { 7, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_12 = {
		type = "Sand",
		position = { 7, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_13 = {
		type = "Sand",
		position = { 7, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_14 = {
		type = "Sand",
		position = { 7, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_15 = {
		type = "Sand",
		position = { 7, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_16 = {
		type = "Sand",
		position = { 7, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_17 = {
		type = "Sand",
		position = { 7, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_18 = {
		type = "Sand",
		position = { 7, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand7_19 = {
		type = "Sand",
		position = { 7, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_0 = {
		type = "Sand",
		position = { 8, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_1 = {
		type = "Sand",
		position = { 8, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_2 = {
		type = "Sand",
		position = { 8, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_3 = {
		type = "Sand",
		position = { 8, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_4 = {
		type = "Sand",
		position = { 8, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_5 = {
		type = "Sand",
		position = { 8, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_6 = {
		type = "Sand",
		position = { 8, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_7 = {
		type = "Sand",
		position = { 8, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Road8_8 = {
		type = "Road",
		position = { 8, 8 },
		model = "road.mesh",
	},

	Road8_9 = {
		type = "Road",
		position = { 8, 9 },
		model = "road.mesh",
	},

	Road8_10 = {
		type = "Road",
		position = { 8, 10 },
		model = "road.mesh",
	},

	Road8_11 = {
		type = "Road",
		position = { 8, 11 },
		model = "road.mesh",
	},

	Sand8_12 = {
		type = "Sand",
		position = { 8, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_13 = {
		type = "Sand",
		position = { 8, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_14 = {
		type = "Sand",
		position = { 8, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_15 = {
		type = "Sand",
		position = { 8, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_16 = {
		type = "Sand",
		position = { 8, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_17 = {
		type = "Sand",
		position = { 8, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_18 = {
		type = "Sand",
		position = { 8, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand8_19 = {
		type = "Sand",
		position = { 8, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_0 = {
		type = "Sand",
		position = { 9, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_1 = {
		type = "Sand",
		position = { 9, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_2 = {
		type = "Sand",
		position = { 9, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_3 = {
		type = "Sand",
		position = { 9, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_4 = {
		type = "Sand",
		position = { 9, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_5 = {
		type = "Sand",
		position = { 9, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_6 = {
		type = "Sand",
		position = { 9, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_7 = {
		type = "Sand",
		position = { 9, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_8 = {
		type = "Sand",
		position = { 9, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Road9_9 = {
		type = "Road",
		position = { 9, 9 },
		model = "road.mesh",
	},

	Road9_10 = {
		type = "Road",
		position = { 9, 10 },
		model = "road.mesh",
	},

	Road9_11 = {
		type = "Road",
		position = { 9, 11 },
		model = "road.mesh",
	},

	Road9_12 = {
		type = "Road",
		position = { 9, 12 },
		model = "road.mesh",
	},

	Sand9_13 = {
		type = "Sand",
		position = { 9, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_14 = {
		type = "Sand",
		position = { 9, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_15 = {
		type = "Sand",
		position = { 9, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_16 = {
		type = "Sand",
		position = { 9, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_17 = {
		type = "Sand",
		position = { 9, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_18 = {
		type = "Sand",
		position = { 9, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand9_19 = {
		type = "Sand",
		position = { 9, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_0 = {
		type = "Sand",
		position = { 10, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_1 = {
		type = "Sand",
		position = { 10, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_2 = {
		type = "Sand",
		position = { 10, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_3 = {
		type = "Sand",
		position = { 10, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_4 = {
		type = "Sand",
		position = { 10, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_5 = {
		type = "Sand",
		position = { 10, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_6 = {
		type = "Sand",
		position = { 10, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_7 = {
		type = "Sand",
		position = { 10, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_8 = {
		type = "Sand",
		position = { 10, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_9 = {
		type = "Sand",
		position = { 10, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Road10_10 = {
		type = "Road",
		position = { 10, 10 },
		model = "road.mesh",
	},

	Road10_11 = {
		type = "Road",
		position = { 10, 11 },
		model = "road.mesh",
	},

	Road10_12 = {
		type = "Road",
		position = { 10, 12 },
		model = "road.mesh",
	},

	Road10_13 = {
		type = "Road",
		position = { 10, 13 },
		model = "road.mesh",
	},

	Sand10_14 = {
		type = "Sand",
		position = { 10, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_15 = {
		type = "Sand",
		position = { 10, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_16 = {
		type = "Sand",
		position = { 10, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_17 = {
		type = "Sand",
		position = { 10, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_18 = {
		type = "Sand",
		position = { 10, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand10_19 = {
		type = "Sand",
		position = { 10, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_0 = {
		type = "Sand",
		position = { 11, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_1 = {
		type = "Sand",
		position = { 11, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_2 = {
		type = "Sand",
		position = { 11, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_3 = {
		type = "Sand",
		position = { 11, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_4 = {
		type = "Sand",
		position = { 11, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_5 = {
		type = "Sand",
		position = { 11, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_6 = {
		type = "Sand",
		position = { 11, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_7 = {
		type = "Sand",
		position = { 11, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_8 = {
		type = "Sand",
		position = { 11, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_9 = {
		type = "Sand",
		position = { 11, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_10 = {
		type = "Sand",
		position = { 11, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Road11_11 = {
		type = "Road",
		position = { 11, 11 },
		model = "road.mesh",
	},

	Road11_12 = {
		type = "Road",
		position = { 11, 12 },
		model = "road.mesh",
	},

	Road11_13 = {
		type = "Road",
		position = { 11, 13 },
		model = "road.mesh",
	},

	Road11_14 = {
		type = "Road",
		position = { 11, 14 },
		model = "road.mesh",
	},

	Sand11_15 = {
		type = "Sand",
		position = { 11, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_16 = {
		type = "Sand",
		position = { 11, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_17 = {
		type = "Sand",
		position = { 11, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_18 = {
		type = "Sand",
		position = { 11, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand11_19 = {
		type = "Sand",
		position = { 11, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_0 = {
		type = "Sand",
		position = { 12, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_1 = {
		type = "Sand",
		position = { 12, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_2 = {
		type = "Sand",
		position = { 12, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_3 = {
		type = "Sand",
		position = { 12, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_4 = {
		type = "Sand",
		position = { 12, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_5 = {
		type = "Sand",
		position = { 12, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_6 = {
		type = "Sand",
		position = { 12, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_7 = {
		type = "Sand",
		position = { 12, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_8 = {
		type = "Sand",
		position = { 12, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_9 = {
		type = "Sand",
		position = { 12, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_10 = {
		type = "Sand",
		position = { 12, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_11 = {
		type = "Sand",
		position = { 12, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Road12_12 = {
		type = "Road",
		position = { 12, 12 },
		model = "road.mesh",
	},

	Road12_13 = {
		type = "Road",
		position = { 12, 13 },
		model = "road.mesh",
	},

	Road12_14 = {
		type = "Road",
		position = { 12, 14 },
		model = "road.mesh",
	},

	Road12_15 = {
		type = "Road",
		position = { 12, 15 },
		model = "road.mesh",
	},

	Sand12_16 = {
		type = "Sand",
		position = { 12, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_17 = {
		type = "Sand",
		position = { 12, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_18 = {
		type = "Sand",
		position = { 12, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand12_19 = {
		type = "Sand",
		position = { 12, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_0 = {
		type = "Sand",
		position = { 13, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_1 = {
		type = "Sand",
		position = { 13, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_2 = {
		type = "Sand",
		position = { 13, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_3 = {
		type = "Sand",
		position = { 13, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_4 = {
		type = "Sand",
		position = { 13, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_5 = {
		type = "Sand",
		position = { 13, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_6 = {
		type = "Sand",
		position = { 13, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_7 = {
		type = "Sand",
		position = { 13, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_8 = {
		type = "Sand",
		position = { 13, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_9 = {
		type = "Sand",
		position = { 13, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_10 = {
		type = "Sand",
		position = { 13, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_11 = {
		type = "Sand",
		position = { 13, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_12 = {
		type = "Sand",
		position = { 13, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Road13_13 = {
		type = "Road",
		position = { 13, 13 },
		model = "road.mesh",
	},

	Road13_14 = {
		type = "Road",
		position = { 13, 14 },
		model = "road.mesh",
	},

	Road13_15 = {
		type = "Road",
		position = { 13, 15 },
		model = "road.mesh",
	},

	Road13_16 = {
		type = "Road",
		position = { 13, 16 },
		model = "road.mesh",
	},

	Sand13_17 = {
		type = "Sand",
		position = { 13, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_18 = {
		type = "Sand",
		position = { 13, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand13_19 = {
		type = "Sand",
		position = { 13, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_0 = {
		type = "Sand",
		position = { 14, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_1 = {
		type = "Sand",
		position = { 14, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_2 = {
		type = "Sand",
		position = { 14, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_3 = {
		type = "Sand",
		position = { 14, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_4 = {
		type = "Sand",
		position = { 14, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_5 = {
		type = "Sand",
		position = { 14, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_6 = {
		type = "Sand",
		position = { 14, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_7 = {
		type = "Sand",
		position = { 14, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_8 = {
		type = "Sand",
		position = { 14, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_9 = {
		type = "Sand",
		position = { 14, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_10 = {
		type = "Sand",
		position = { 14, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_11 = {
		type = "Sand",
		position = { 14, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_12 = {
		type = "Sand",
		position = { 14, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_13 = {
		type = "Sand",
		position = { 14, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Road14_14 = {
		type = "Road",
		position = { 14, 14 },
		model = "road.mesh",
	},

	Road14_15 = {
		type = "Road",
		position = { 14, 15 },
		model = "road.mesh",
	},

	Road14_16 = {
		type = "Road",
		position = { 14, 16 },
		model = "road.mesh",
	},

	Road14_17 = {
		type = "Road",
		position = { 14, 17 },
		model = "road.mesh",
	},

	Sand14_18 = {
		type = "Sand",
		position = { 14, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand14_19 = {
		type = "Sand",
		position = { 14, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_0 = {
		type = "Sand",
		position = { 15, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_1 = {
		type = "Sand",
		position = { 15, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_2 = {
		type = "Sand",
		position = { 15, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_3 = {
		type = "Sand",
		position = { 15, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_4 = {
		type = "Sand",
		position = { 15, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_5 = {
		type = "Sand",
		position = { 15, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_6 = {
		type = "Sand",
		position = { 15, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_7 = {
		type = "Sand",
		position = { 15, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_8 = {
		type = "Sand",
		position = { 15, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_9 = {
		type = "Sand",
		position = { 15, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_10 = {
		type = "Sand",
		position = { 15, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_11 = {
		type = "Sand",
		position = { 15, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_12 = {
		type = "Sand",
		position = { 15, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_13 = {
		type = "Sand",
		position = { 15, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand15_14 = {
		type = "Sand",
		position = { 15, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Road15_15 = {
		type = "Road",
		position = { 15, 15 },
		model = "road.mesh",
	},

	Road15_16 = {
		type = "Road",
		position = { 15, 16 },
		model = "road.mesh",
	},

	Road15_17 = {
		type = "Road",
		position = { 15, 17 },
		model = "road.mesh",
	},

	Road15_18 = {
		type = "Road",
		position = { 15, 18 },
		model = "road.mesh",
	},

	Sand15_19 = {
		type = "Sand",
		position = { 15, 19 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_0 = {
		type = "Sand",
		position = { 16, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_1 = {
		type = "Sand",
		position = { 16, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_2 = {
		type = "Sand",
		position = { 16, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_3 = {
		type = "Sand",
		position = { 16, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_4 = {
		type = "Sand",
		position = { 16, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_5 = {
		type = "Sand",
		position = { 16, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_6 = {
		type = "Sand",
		position = { 16, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_7 = {
		type = "Sand",
		position = { 16, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_8 = {
		type = "Sand",
		position = { 16, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_9 = {
		type = "Sand",
		position = { 16, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_10 = {
		type = "Sand",
		position = { 16, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_11 = {
		type = "Sand",
		position = { 16, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_12 = {
		type = "Sand",
		position = { 16, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_13 = {
		type = "Sand",
		position = { 16, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_14 = {
		type = "Sand",
		position = { 16, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand16_15 = {
		type = "Sand",
		position = { 16, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Road16_16 = {
		type = "Road",
		position = { 16, 16 },
		model = "road.mesh",
	},

	Road16_17 = {
		type = "Road",
		position = { 16, 17 },
		model = "road.mesh",
	},

	Road16_18 = {
		type = "Road",
		position = { 16, 18 },
		model = "road.mesh",
	},

	Road16_19 = {
		type = "Road",
		position = { 16, 19 },
		model = "road.mesh",
	},

	Sand17_0 = {
		type = "Sand",
		position = { 17, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_1 = {
		type = "Sand",
		position = { 17, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_2 = {
		type = "Sand",
		position = { 17, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_3 = {
		type = "Sand",
		position = { 17, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_4 = {
		type = "Sand",
		position = { 17, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_5 = {
		type = "Sand",
		position = { 17, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_6 = {
		type = "Sand",
		position = { 17, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_7 = {
		type = "Sand",
		position = { 17, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_8 = {
		type = "Sand",
		position = { 17, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_9 = {
		type = "Sand",
		position = { 17, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_10 = {
		type = "Sand",
		position = { 17, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_11 = {
		type = "Sand",
		position = { 17, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_12 = {
		type = "Sand",
		position = { 17, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_13 = {
		type = "Sand",
		position = { 17, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_14 = {
		type = "Sand",
		position = { 17, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_15 = {
		type = "Sand",
		position = { 17, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand17_16 = {
		type = "Sand",
		position = { 17, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Road17_17 = {
		type = "Road",
		position = { 17, 17 },
		model = "road.mesh",
	},

	Road17_18 = {
		type = "Road",
		position = { 17, 18 },
		model = "road.mesh",
	},

	Road17_19 = {
		type = "Road",
		position = { 17, 19 },
		model = "road.mesh",
	},

	Sand18_0 = {
		type = "Sand",
		position = { 18, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_1 = {
		type = "Sand",
		position = { 18, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_2 = {
		type = "Sand",
		position = { 18, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_3 = {
		type = "Sand",
		position = { 18, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_4 = {
		type = "Sand",
		position = { 18, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_5 = {
		type = "Sand",
		position = { 18, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_6 = {
		type = "Sand",
		position = { 18, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_7 = {
		type = "Sand",
		position = { 18, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_8 = {
		type = "Sand",
		position = { 18, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_9 = {
		type = "Sand",
		position = { 18, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_10 = {
		type = "Sand",
		position = { 18, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_11 = {
		type = "Sand",
		position = { 18, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_12 = {
		type = "Sand",
		position = { 18, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_13 = {
		type = "Sand",
		position = { 18, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_14 = {
		type = "Sand",
		position = { 18, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_15 = {
		type = "Sand",
		position = { 18, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_16 = {
		type = "Sand",
		position = { 18, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand18_17 = {
		type = "Sand",
		position = { 18, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Road18_18 = {
		type = "Road",
		position = { 18, 18 },
		model = "road.mesh",
	},

	Road18_19 = {
		type = "Road",
		position = { 18, 19 },
		model = "road.mesh",
	},

	Sand19_0 = {
		type = "Sand",
		position = { 19, 0 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_1 = {
		type = "Sand",
		position = { 19, 1 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_2 = {
		type = "Sand",
		position = { 19, 2 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_3 = {
		type = "Sand",
		position = { 19, 3 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_4 = {
		type = "Sand",
		position = { 19, 4 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_5 = {
		type = "Sand",
		position = { 19, 5 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_6 = {
		type = "Sand",
		position = { 19, 6 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_7 = {
		type = "Sand",
		position = { 19, 7 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_8 = {
		type = "Sand",
		position = { 19, 8 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_9 = {
		type = "Sand",
		position = { 19, 9 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_10 = {
		type = "Sand",
		position = { 19, 10 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_11 = {
		type = "Sand",
		position = { 19, 11 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_12 = {
		type = "Sand",
		position = { 19, 12 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_13 = {
		type = "Sand",
		position = { 19, 13 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_14 = {
		type = "Sand",
		position = { 19, 14 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_15 = {
		type = "Sand",
		position = { 19, 15 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_16 = {
		type = "Sand",
		position = { 19, 16 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_17 = {
		type = "Sand",
		position = { 19, 17 },
		model = "sand.mesh",
		coste = 2,
	},

	Sand19_18 = {
		type = "Sand",
		position = { 19, 18 },
		model = "sand.mesh",
		coste = 2,
	},

	Road19_19 = {
		type = "Road",
		position = { 19, 19 },
		model = "road.mesh",
	},
	
}