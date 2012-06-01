Map = {

	Sand = {
		normal_texture = "toon_desertb.jpg",
		height = 0,
		is_texture_base = true,
		max_height = 0,
		texture_size = 128,
		difuse_texture = "toon_desert.jpg",
		cost = 0,
		texture_blendheight = 0,
	},

	Road = {
		normal_texture = "road3_NRM.tif",
		height = 1,
		texture_blendheightmax = 3,
		max_height = 1,
		texture_size = 64,
		difuse_texture = "road3.jpg",
		cost = 0,
		texture_blendheight = 1,
	},

	Mountain = {
		normal_texture = "mountain_NRM.tif",
		height = 10,
		texture_blendheightmax = 255,
		max_height = 50,
		texture_size = 128,
		difuse_texture = "mountain.jpg",
		cost = -1,
		texture_blendheight = 2,
	},

	Grid = {
		grid_size = 16,
		type = "Grid",
		width = 90,
		height = 90,
		grid_map = {
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Road", "Road", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
		},
	},

	ScriptsLoader = {
		dimension = { 1, 1 },
		activateFunction = "loadScripts",
		grid_position = { 88, 0 },
		type = "ScriptsLoader",
		script = "scriptsLoader",
	},

	World = {
		physic_entity = "simple",
		type = "World",
		physic_type = "static",
		dimension = { 1, 1 },
		physic_shape = "box",
		physic_dimensions = {720.0, 0.5, 720.0},
	},

	Jack = {
		afectaEmpujar = 50,
		dimension = { 1, 1 },
		life = 100.0,
		grid_position = { 44, 24 },
		nombreGranada = "Granada",
		tickFunction = "jackTick",
		script = "jackScript",
		type = "Player",
	},

	Erick = {
		afectaEmpujar = 100,
		dimension = { 1, 1 },
		life = 100.0,
		grid_position = { 42, 25 },
		nombreGranada = "BolaTeltr",
		type = "Player",
	},

	Amor = {
		afectaEmpujar = 150,
		dimension = { 1, 1 },
		life = 100.0,
		grid_position = { 40, 26 },
		type = "Player",
		script = "amorScript",
	},

	PlayerGod = {
		isPlayer = true,
		orientation = 225,
		dimension = { 1, 1 },
		cameraVelocity = 500,
		isTargetCamera = true,
		grid_position = { 41, 23 },
		cameraDistance = 10,
		mouseVelocity = 4,
		script = "godScript",
		type = "PlayerGod",
		mouseDistance = 100,
	},

	Camera = {
		dimension = { 1, 1 },
		distance = 150,
		height = 300,
		grid_position = { 41, 22 },
		targetHeight = 7,
		targetName = "PlayerGod",
		type = "Camera",
		targetDistance = 10,
	},

	EnemiesSpawner1 = {
		model = "esfera.mesh",
		dimension = { 1, 1 },
		grid_position = { 55, 1 },
		ID = 1,
		type = "Enemies",
	},

	EnemiesSpawner2 = {
		model = "esfera.mesh",
		dimension = { 1, 1 },
		grid_position = { 87, 30 },
		ID = 2,
		type = "Enemies",
	},

	EnemiesSpawner3 = {
		model = "esfera.mesh",
		dimension = { 1, 1 },
		grid_position = { 4, 19 },
		ID = 3,
		type = "Enemies",
	},

	EnemiesSpawner4 = {
		model = "esfera.mesh",
		dimension = { 1, 1 },
		grid_position = { 28, 60 },
		ID = 4,
		type = "Enemies",
	},

	EnemyMind = {
		dimension = { 1, 1 },
		initStage = 1,
		grid_position = { 85, 0 },
		type = "EnemyMind",
		initState = 1,
	},

	Entity15 = {
		dimension = { 1, 1 },
		grid_position = { 89, 8 },
		type = "Obstacle",
	},

	Entity17 = {
		dimension = { 1, 1 },
		grid_position = { 87, 9 },
		type = "Obstacle",
	},

	Entity16 = {
		dimension = { 1, 1 },
		grid_position = { 88, 8 },
		type = "Obstacle",
	},

	Entity19 = {
		dimension = { 1, 1 },
		grid_position = { 85, 9 },
		type = "Obstacle",
	},

	Entity18 = {
		dimension = { 1, 1 },
		grid_position = { 86, 9 },
		type = "Obstacle",
	},

	Entity21 = {
		dimension = { 1, 1 },
		grid_position = { 83, 10 },
		type = "Obstacle",
	},

	Entity20 = {
		dimension = { 1, 1 },
		grid_position = { 84, 9 },
		type = "Obstacle",
	},

	Entity23 = {
		dimension = { 1, 1 },
		grid_position = { 83, 9 },
		type = "Obstacle",
	},

	Entity25 = {
		dimension = { 1, 1 },
		grid_position = { 83, 12 },
		type = "Obstacle",
	},

	Entity24 = {
		dimension = { 1, 1 },
		grid_position = { 83, 11 },
		type = "Obstacle",
	},

	Entity27 = {
		dimension = { 1, 1 },
		grid_position = { 83, 14 },
		type = "Obstacle",
	},

	Entity26 = {
		dimension = { 1, 1 },
		grid_position = { 83, 13 },
		type = "Obstacle",
	},

	Entity29 = {
		dimension = { 1, 1 },
		grid_position = { 83, 16 },
		type = "Obstacle",
	},

	Entity28 = {
		dimension = { 1, 1 },
		grid_position = { 83, 15 },
		type = "Obstacle",
	},

	Entity31 = {
		dimension = { 1, 1 },
		grid_position = { 83, 18 },
		type = "Obstacle",
	},

	Entity30 = {
		dimension = { 1, 1 },
		grid_position = { 83, 17 },
		type = "Obstacle",
	},

	Entity34 = {
		dimension = { 1, 1 },
		grid_position = { 84, 19 },
		type = "Obstacle",
	},

	Entity35 = {
		dimension = { 1, 1 },
		grid_position = { 84, 20 },
		type = "Obstacle",
	},

	Entity32 = {
		dimension = { 1, 1 },
		grid_position = { 84, 18 },
		type = "Obstacle",
	},

	Entity33 = {
		dimension = { 1, 1 },
		grid_position = { 87, 8 },
		type = "Obstacle",
	},

	Entity38 = {
		dimension = { 1, 1 },
		grid_position = { 84, 23 },
		type = "Obstacle",
	},

	Entity39 = {
		dimension = { 1, 1 },
		grid_position = { 84, 24 },
		type = "Obstacle",
	},

	Entity36 = {
		dimension = { 1, 1 },
		grid_position = { 84, 21 },
		type = "Obstacle",
	},

	Entity37 = {
		dimension = { 1, 1 },
		grid_position = { 84, 22 },
		type = "Obstacle",
	},

	Entity42 = {
		dimension = { 1, 1 },
		grid_position = { 84, 27 },
		type = "Obstacle",
	},

	Entity43 = {
		dimension = { 1, 1 },
		grid_position = { 84, 28 },
		type = "Obstacle",
	},

	Entity40 = {
		dimension = { 1, 1 },
		grid_position = { 84, 26 },
		type = "Obstacle",
	},

	Entity41 = {
		dimension = { 1, 1 },
		grid_position = { 84, 25 },
		type = "Obstacle",
	},

	Entity46 = {
		dimension = { 1, 1 },
		grid_position = { 83, 30 },
		type = "Obstacle",
	},

	Entity47 = {
		dimension = { 1, 1 },
		grid_position = { 83, 31 },
		type = "Obstacle",
	},

	Entity44 = {
		dimension = { 1, 1 },
		grid_position = { 83, 28 },
		type = "Obstacle",
	},

	Entity45 = {
		dimension = { 1, 1 },
		grid_position = { 83, 29 },
		type = "Obstacle",
	},

	Entity51 = {
		dimension = { 1, 1 },
		grid_position = { 83, 36 },
		type = "Obstacle",
	},

	Entity50 = {
		dimension = { 1, 1 },
		grid_position = { 83, 34 },
		type = "Obstacle",
	},

	Entity49 = {
		dimension = { 1, 1 },
		grid_position = { 83, 33 },
		type = "Obstacle",
	},

	Entity48 = {
		dimension = { 1, 1 },
		grid_position = { 83, 32 },
		type = "Obstacle",
	},

	Entity55 = {
		dimension = { 1, 1 },
		grid_position = { 83, 39 },
		type = "Obstacle",
	},

	Entity54 = {
		dimension = { 1, 1 },
		grid_position = { 83, 38 },
		type = "Obstacle",
	},

	Entity53 = {
		dimension = { 1, 1 },
		grid_position = { 83, 37 },
		type = "Obstacle",
	},

	Entity52 = {
		dimension = { 1, 1 },
		grid_position = { 83, 35 },
		type = "Obstacle",
	},

	Entity59 = {
		dimension = { 1, 1 },
		grid_position = { 82, 42 },
		type = "Obstacle",
	},

	Entity58 = {
		dimension = { 1, 1 },
		grid_position = { 82, 41 },
		type = "Obstacle",
	},

	Entity57 = {
		dimension = { 1, 1 },
		grid_position = { 82, 40 },
		type = "Obstacle",
	},

	Entity56 = {
		dimension = { 1, 1 },
		grid_position = { 83, 40 },
		type = "Obstacle",
	},

	Entity63 = {
		dimension = { 1, 1 },
		grid_position = { 81, 45 },
		type = "Obstacle",
	},

	Entity62 = {
		dimension = { 1, 1 },
		grid_position = { 81, 44 },
		type = "Obstacle",
	},

	Entity61 = {
		dimension = { 1, 1 },
		grid_position = { 82, 44 },
		type = "Obstacle",
	},

	Entity60 = {
		dimension = { 1, 1 },
		grid_position = { 82, 43 },
		type = "Obstacle",
	},

	Entity68 = {
		dimension = { 1, 1 },
		grid_position = { 80, 48 },
		type = "Obstacle",
	},

	Entity69 = {
		dimension = { 1, 1 },
		grid_position = { 79, 48 },
		type = "Obstacle",
	},

	Entity70 = {
		dimension = { 1, 1 },
		grid_position = { 79, 49 },
		type = "Obstacle",
	},

	Entity71 = {
		dimension = { 1, 1 },
		grid_position = { 78, 49 },
		type = "Obstacle",
	},

	Entity64 = {
		dimension = { 1, 1 },
		grid_position = { 81, 46 },
		type = "Obstacle",
	},

	Entity66 = {
		dimension = { 1, 1 },
		grid_position = { 81, 47 },
		type = "Obstacle",
	},

	Entity67 = {
		dimension = { 1, 1 },
		grid_position = { 80, 47 },
		type = "Obstacle",
	},

	Entity76 = {
		dimension = { 1, 1 },
		grid_position = { 74, 50 },
		type = "Obstacle",
	},

	Entity77 = {
		dimension = { 1, 1 },
		grid_position = { 73, 50 },
		type = "Obstacle",
	},

	Entity78 = {
		dimension = { 1, 1 },
		grid_position = { 73, 49 },
		type = "Obstacle",
	},

	Entity79 = {
		dimension = { 1, 1 },
		grid_position = { 72, 49 },
		type = "Obstacle",
	},

	Entity72 = {
		dimension = { 1, 1 },
		grid_position = { 77, 49 },
		type = "Obstacle",
	},

	Entity73 = {
		dimension = { 1, 1 },
		grid_position = { 77, 50 },
		type = "Obstacle",
	},

	Entity74 = {
		dimension = { 1, 1 },
		grid_position = { 76, 50 },
		type = "Obstacle",
	},

	Entity75 = {
		dimension = { 1, 1 },
		grid_position = { 75, 50 },
		type = "Obstacle",
	},

	Entity85 = {
		dimension = { 1, 1 },
		grid_position = { 68, 47 },
		type = "Obstacle",
	},

	Entity84 = {
		dimension = { 1, 1 },
		grid_position = { 69, 47 },
		type = "Obstacle",
	},

	Entity87 = {
		dimension = { 1, 1 },
		grid_position = { 67, 46 },
		type = "Obstacle",
	},

	Entity86 = {
		dimension = { 1, 1 },
		grid_position = { 68, 46 },
		type = "Obstacle",
	},

	Entity81 = {
		dimension = { 1, 1 },
		grid_position = { 71, 48 },
		type = "Obstacle",
	},

	Entity80 = {
		dimension = { 1, 1 },
		grid_position = { 71, 49 },
		type = "Obstacle",
	},

	Entity83 = {
		dimension = { 1, 1 },
		grid_position = { 69, 48 },
		type = "Obstacle",
	},

	Entity82 = {
		dimension = { 1, 1 },
		grid_position = { 70, 48 },
		type = "Obstacle",
	},

	Entity93 = {
		dimension = { 1, 1 },
		grid_position = { 65, 42 },
		type = "Obstacle",
	},

	Entity92 = {
		dimension = { 1, 1 },
		grid_position = { 66, 42 },
		type = "Obstacle",
	},

	Entity95 = {
		dimension = { 1, 1 },
		grid_position = { 65, 40 },
		type = "Obstacle",
	},

	Entity94 = {
		dimension = { 1, 1 },
		grid_position = { 65, 41 },
		type = "Obstacle",
	},

	Entity89 = {
		dimension = { 1, 1 },
		grid_position = { 67, 44 },
		type = "Obstacle",
	},

	Entity88 = {
		dimension = { 1, 1 },
		grid_position = { 67, 45 },
		type = "Obstacle",
	},

	Entity91 = {
		dimension = { 1, 1 },
		grid_position = { 66, 43 },
		type = "Obstacle",
	},

	Entity90 = {
		dimension = { 1, 1 },
		grid_position = { 66, 44 },
		type = "Obstacle",
	},

	Entity102 = {
		dimension = { 1, 1 },
		grid_position = { 62, 36 },
		type = "Obstacle",
	},

	Entity103 = {
		dimension = { 1, 1 },
		grid_position = { 63, 35 },
		type = "Obstacle",
	},

	Entity100 = {
		dimension = { 1, 1 },
		grid_position = { 63, 36 },
		type = "Obstacle",
	},

	Entity101 = {
		dimension = { 1, 1 },
		grid_position = { 63, 37 },
		type = "Obstacle",
	},

	Entity98 = {
		dimension = { 1, 1 },
		grid_position = { 64, 38 },
		type = "Obstacle",
	},

	Entity99 = {
		dimension = { 1, 1 },
		grid_position = { 63, 38 },
		type = "Obstacle",
	},

	Entity96 = {
		dimension = { 1, 1 },
		grid_position = { 64, 40 },
		type = "Obstacle",
	},

	Entity97 = {
		dimension = { 1, 1 },
		grid_position = { 64, 39 },
		type = "Obstacle",
	},

	Entity110 = {
		dimension = { 1, 1 },
		grid_position = { 65, 30 },
		type = "Obstacle",
	},

	Entity111 = {
		dimension = { 1, 1 },
		grid_position = { 65, 29 },
		type = "Obstacle",
	},

	Entity108 = {
		dimension = { 1, 1 },
		grid_position = { 65, 32 },
		type = "Obstacle",
	},

	Entity109 = {
		dimension = { 1, 1 },
		grid_position = { 65, 31 },
		type = "Obstacle",
	},

	Entity106 = {
		dimension = { 1, 1 },
		grid_position = { 65, 34 },
		type = "Obstacle",
	},

	Entity107 = {
		dimension = { 1, 1 },
		grid_position = { 65, 33 },
		type = "Obstacle",
	},

	Entity104 = {
		dimension = { 1, 1 },
		grid_position = { 64, 35 },
		type = "Obstacle",
	},

	Entity105 = {
		dimension = { 1, 1 },
		grid_position = { 64, 34 },
		type = "Obstacle",
	},

	Entity119 = {
		dimension = { 1, 1 },
		grid_position = { 64, 22 },
		type = "Obstacle",
	},

	Entity118 = {
		dimension = { 1, 1 },
		grid_position = { 64, 23 },
		type = "Obstacle",
	},

	Entity117 = {
		dimension = { 1, 1 },
		grid_position = { 64, 24 },
		type = "Obstacle",
	},

	Entity116 = {
		dimension = { 1, 1 },
		grid_position = { 65, 24 },
		type = "Obstacle",
	},

	Entity115 = {
		dimension = { 1, 1 },
		grid_position = { 65, 25 },
		type = "Obstacle",
	},

	Entity114 = {
		dimension = { 1, 1 },
		grid_position = { 65, 26 },
		type = "Obstacle",
	},

	Entity113 = {
		dimension = { 1, 1 },
		grid_position = { 65, 27 },
		type = "Obstacle",
	},

	Entity112 = {
		dimension = { 1, 1 },
		grid_position = { 65, 28 },
		type = "Obstacle",
	},

	Entity127 = {
		dimension = { 1, 1 },
		grid_position = { 63, 15 },
		type = "Obstacle",
	},

	Entity126 = {
		dimension = { 1, 1 },
		grid_position = { 64, 16 },
		type = "Obstacle",
	},

	Entity125 = {
		dimension = { 1, 1 },
		grid_position = { 64, 15 },
		type = "Obstacle",
	},

	Entity124 = {
		dimension = { 1, 1 },
		grid_position = { 64, 17 },
		type = "Obstacle",
	},

	Entity123 = {
		dimension = { 1, 1 },
		grid_position = { 64, 18 },
		type = "Obstacle",
	},

	Entity122 = {
		dimension = { 1, 1 },
		grid_position = { 64, 19 },
		type = "Obstacle",
	},

	Entity121 = {
		dimension = { 1, 1 },
		grid_position = { 64, 20 },
		type = "Obstacle",
	},

	Entity120 = {
		dimension = { 1, 1 },
		grid_position = { 64, 21 },
		type = "Obstacle",
	},

	Entity137 = {
		dimension = { 1, 1 },
		grid_position = { 62, 6 },
		type = "Obstacle",
	},

	Entity136 = {
		dimension = { 1, 1 },
		grid_position = { 62, 7 },
		type = "Obstacle",
	},

	Entity139 = {
		dimension = { 1, 1 },
		grid_position = { 61, 5 },
		type = "Obstacle",
	},

	Entity138 = {
		dimension = { 1, 1 },
		grid_position = { 61, 6 },
		type = "Obstacle",
	},

	Entity141 = {
		dimension = { 1, 1 },
		grid_position = { 61, 3 },
		type = "Obstacle",
	},

	Entity140 = {
		dimension = { 1, 1 },
		grid_position = { 61, 4 },
		type = "Obstacle",
	},

	Entity143 = {
		dimension = { 1, 1 },
		grid_position = { 61, 1 },
		type = "Obstacle",
	},

	Entity142 = {
		dimension = { 1, 1 },
		grid_position = { 61, 2 },
		type = "Obstacle",
	},

	Entity129 = {
		dimension = { 1, 1 },
		grid_position = { 63, 13 },
		type = "Obstacle",
	},

	Entity128 = {
		dimension = { 1, 1 },
		grid_position = { 63, 14 },
		type = "Obstacle",
	},

	Entity131 = {
		dimension = { 1, 1 },
		grid_position = { 63, 11 },
		type = "Obstacle",
	},

	Entity130 = {
		dimension = { 1, 1 },
		grid_position = { 63, 12 },
		type = "Obstacle",
	},

	Entity133 = {
		dimension = { 1, 1 },
		grid_position = { 62, 10 },
		type = "Obstacle",
	},

	Entity132 = {
		dimension = { 1, 1 },
		grid_position = { 63, 10 },
		type = "Obstacle",
	},

	Entity135 = {
		dimension = { 1, 1 },
		grid_position = { 62, 8 },
		type = "Obstacle",
	},

	Entity134 = {
		dimension = { 1, 1 },
		grid_position = { 62, 9 },
		type = "Obstacle",
	},

	Entity152 = {
		dimension = { 1, 1 },
		grid_position = { 51, 4 },
		type = "Obstacle",
	},

	Entity153 = {
		dimension = { 1, 1 },
		grid_position = { 51, 6 },
		type = "Obstacle",
	},

	Entity154 = {
		dimension = { 1, 1 },
		grid_position = { 51, 5 },
		type = "Obstacle",
	},

	Entity155 = {
		dimension = { 1, 1 },
		grid_position = { 51, 7 },
		type = "Obstacle",
	},

	Entity156 = {
		dimension = { 1, 1 },
		grid_position = { 51, 8 },
		type = "Obstacle",
	},

	Entity157 = {
		dimension = { 1, 1 },
		grid_position = { 52, 8 },
		type = "Obstacle",
	},

	Entity158 = {
		dimension = { 1, 1 },
		grid_position = { 52, 9 },
		type = "Obstacle",
	},

	Entity159 = {
		dimension = { 1, 1 },
		grid_position = { 52, 10 },
		type = "Obstacle",
	},

	Entity144 = {
		dimension = { 1, 1 },
		grid_position = { 60, 1 },
		type = "Obstacle",
	},

	Entity145 = {
		dimension = { 1, 1 },
		grid_position = { 60, 0 },
		type = "Obstacle",
	},

	Entity146 = {
		dimension = { 1, 1 },
		grid_position = { 49, 0 },
		type = "Obstacle",
	},

	Entity147 = {
		dimension = { 1, 1 },
		grid_position = { 49, 1 },
		type = "Obstacle",
	},

	Entity148 = {
		dimension = { 1, 1 },
		grid_position = { 49, 2 },
		type = "Obstacle",
	},

	Entity149 = {
		dimension = { 1, 1 },
		grid_position = { 50, 2 },
		type = "Obstacle",
	},

	Entity150 = {
		dimension = { 1, 1 },
		grid_position = { 50, 4 },
		type = "Obstacle",
	},

	Entity151 = {
		dimension = { 1, 1 },
		grid_position = { 50, 3 },
		type = "Obstacle",
	},

	Entity171 = {
		dimension = { 1, 1 },
		grid_position = { 54, 20 },
		type = "Obstacle",
	},

	Entity170 = {
		dimension = { 1, 1 },
		grid_position = { 54, 19 },
		type = "Obstacle",
	},

	Entity169 = {
		dimension = { 1, 1 },
		grid_position = { 54, 18 },
		type = "Obstacle",
	},

	Entity168 = {
		dimension = { 1, 1 },
		grid_position = { 53, 18 },
		type = "Obstacle",
	},

	Entity175 = {
		dimension = { 1, 1 },
		grid_position = { 51, 21 },
		type = "Obstacle",
	},

	Entity174 = {
		dimension = { 1, 1 },
		grid_position = { 52, 21 },
		type = "Obstacle",
	},

	Entity173 = {
		dimension = { 1, 1 },
		grid_position = { 53, 21 },
		type = "Obstacle",
	},

	Entity172 = {
		dimension = { 1, 1 },
		grid_position = { 53, 20 },
		type = "Obstacle",
	},

	Entity163 = {
		dimension = { 1, 1 },
		grid_position = { 53, 13 },
		type = "Obstacle",
	},

	Entity162 = {
		dimension = { 1, 1 },
		grid_position = { 53, 12 },
		type = "Obstacle",
	},

	Entity161 = {
		dimension = { 1, 1 },
		grid_position = { 52, 12 },
		type = "Obstacle",
	},

	Entity160 = {
		dimension = { 1, 1 },
		grid_position = { 52, 11 },
		type = "Obstacle",
	},

	Entity167 = {
		dimension = { 1, 1 },
		grid_position = { 53, 17 },
		type = "Obstacle",
	},

	Entity166 = {
		dimension = { 1, 1 },
		grid_position = { 53, 16 },
		type = "Obstacle",
	},

	Entity165 = {
		dimension = { 1, 1 },
		grid_position = { 53, 14 },
		type = "Obstacle",
	},

	Entity164 = {
		dimension = { 1, 1 },
		grid_position = { 53, 15 },
		type = "Obstacle",
	},

	Entity186 = {
		dimension = { 1, 1 },
		grid_position = { 43, 20 },
		type = "Obstacle",
	},

	Entity187 = {
		dimension = { 1, 1 },
		grid_position = { 42, 20 },
		type = "Obstacle",
	},

	Entity184 = {
		dimension = { 1, 1 },
		grid_position = { 44, 19 },
		type = "Obstacle",
	},

	Entity185 = {
		dimension = { 1, 1 },
		grid_position = { 43, 19 },
		type = "Obstacle",
	},

	Entity190 = {
		dimension = { 1, 1 },
		grid_position = { 40, 21 },
		type = "Obstacle",
	},

	Entity191 = {
		dimension = { 1, 1 },
		grid_position = { 39, 21 },
		type = "Obstacle",
	},

	Entity188 = {
		dimension = { 1, 1 },
		grid_position = { 41, 20 },
		type = "Obstacle",
	},

	Entity189 = {
		dimension = { 1, 1 },
		grid_position = { 41, 21 },
		type = "Obstacle",
	},

	Entity178 = {
		dimension = { 1, 1 },
		grid_position = { 49, 20 },
		type = "Obstacle",
	},

	Entity179 = {
		dimension = { 1, 1 },
		grid_position = { 48, 20 },
		type = "Obstacle",
	},

	Entity176 = {
		dimension = { 1, 1 },
		grid_position = { 50, 21 },
		type = "Obstacle",
	},

	Entity177 = {
		dimension = { 1, 1 },
		grid_position = { 50, 20 },
		type = "Obstacle",
	},

	Entity182 = {
		dimension = { 1, 1 },
		grid_position = { 46, 19 },
		type = "Obstacle",
	},

	Entity183 = {
		dimension = { 1, 1 },
		grid_position = { 45, 19 },
		type = "Obstacle",
	},

	Entity180 = {
		dimension = { 1, 1 },
		grid_position = { 47, 20 },
		type = "Obstacle",
	},

	Entity181 = {
		dimension = { 1, 1 },
		grid_position = { 47, 19 },
		type = "Obstacle",
	},

	Entity205 = {
		dimension = { 1, 1 },
		grid_position = { 33, 29 },
		type = "Obstacle",
	},

	Entity204 = {
		dimension = { 1, 1 },
		grid_position = { 34, 29 },
		type = "Obstacle",
	},

	Entity207 = {
		dimension = { 1, 1 },
		grid_position = { 32, 28 },
		type = "Obstacle",
	},

	Entity206 = {
		dimension = { 1, 1 },
		grid_position = { 32, 29 },
		type = "Obstacle",
	},

	Entity201 = {
		dimension = { 1, 1 },
		grid_position = { 35, 27 },
		type = "Obstacle",
	},

	Entity200 = {
		dimension = { 1, 1 },
		grid_position = { 35, 26 },
		type = "Obstacle",
	},

	Entity203 = {
		dimension = { 1, 1 },
		grid_position = { 34, 28 },
		type = "Obstacle",
	},

	Entity202 = {
		dimension = { 1, 1 },
		grid_position = { 35, 28 },
		type = "Obstacle",
	},

	Entity197 = {
		dimension = { 1, 1 },
		grid_position = { 36, 24 },
		type = "Obstacle",
	},

	Entity196 = {
		dimension = { 1, 1 },
		grid_position = { 36, 23 },
		type = "Obstacle",
	},

	Entity199 = {
		dimension = { 1, 1 },
		grid_position = { 35, 25 },
		type = "Obstacle",
	},

	Entity198 = {
		dimension = { 1, 1 },
		grid_position = { 36, 25 },
		type = "Obstacle",
	},

	Entity193 = {
		dimension = { 1, 1 },
		grid_position = { 38, 22 },
		type = "Obstacle",
	},

	Entity192 = {
		dimension = { 1, 1 },
		grid_position = { 39, 22 },
		type = "Obstacle",
	},

	Entity195 = {
		dimension = { 1, 1 },
		grid_position = { 37, 23 },
		type = "Obstacle",
	},

	Entity194 = {
		dimension = { 1, 1 },
		grid_position = { 37, 22 },
		type = "Obstacle",
	},

	Entity220 = {
		dimension = { 1, 1 },
		grid_position = { 24, 23 },
		type = "Obstacle",
	},

	Entity221 = {
		dimension = { 1, 1 },
		grid_position = { 23, 23 },
		type = "Obstacle",
	},

	Entity222 = {
		dimension = { 1, 1 },
		grid_position = { 23, 22 },
		type = "Obstacle",
	},

	Entity223 = {
		dimension = { 1, 1 },
		grid_position = { 22, 22 },
		type = "Obstacle",
	},

	Entity216 = {
		dimension = { 1, 1 },
		grid_position = { 27, 24 },
		type = "Obstacle",
	},

	Entity217 = {
		dimension = { 1, 1 },
		grid_position = { 26, 24 },
		type = "Obstacle",
	},

	Entity218 = {
		dimension = { 1, 1 },
		grid_position = { 25, 24 },
		type = "Obstacle",
	},

	Entity219 = {
		dimension = { 1, 1 },
		grid_position = { 25, 23 },
		type = "Obstacle",
	},

	Entity212 = {
		dimension = { 1, 1 },
		grid_position = { 28, 27 },
		type = "Obstacle",
	},

	Entity213 = {
		dimension = { 1, 1 },
		grid_position = { 28, 26 },
		type = "Obstacle",
	},

	Entity214 = {
		dimension = { 1, 1 },
		grid_position = { 28, 25 },
		type = "Obstacle",
	},

	Entity215 = {
		dimension = { 1, 1 },
		grid_position = { 27, 25 },
		type = "Obstacle",
	},

	Entity208 = {
		dimension = { 1, 1 },
		grid_position = { 31, 28 },
		type = "Obstacle",
	},

	Entity209 = {
		dimension = { 1, 1 },
		grid_position = { 30, 28 },
		type = "Obstacle",
	},

	Entity210 = {
		dimension = { 1, 1 },
		grid_position = { 29, 28 },
		type = "Obstacle",
	},

	Entity211 = {
		dimension = { 1, 1 },
		grid_position = { 29, 27 },
		type = "Obstacle",
	},

	Entity239 = {
		dimension = { 1, 1 },
		grid_position = { 14, 14 },
		type = "Obstacle",
	},

	Entity238 = {
		dimension = { 1, 1 },
		grid_position = { 14, 15 },
		type = "Obstacle",
	},

	Entity237 = {
		dimension = { 1, 1 },
		grid_position = { 15, 15 },
		type = "Obstacle",
	},

	Entity236 = {
		dimension = { 1, 1 },
		grid_position = { 15, 16 },
		type = "Obstacle",
	},

	Entity235 = {
		dimension = { 1, 1 },
		grid_position = { 16, 16 },
		type = "Obstacle",
	},

	Entity234 = {
		dimension = { 1, 1 },
		grid_position = { 16, 17 },
		type = "Obstacle",
	},

	Entity233 = {
		dimension = { 1, 1 },
		grid_position = { 17, 17 },
		type = "Obstacle",
	},

	Entity232 = {
		dimension = { 1, 1 },
		grid_position = { 17, 18 },
		type = "Obstacle",
	},

	Entity231 = {
		dimension = { 1, 1 },
		grid_position = { 18, 18 },
		type = "Obstacle",
	},

	Entity230 = {
		dimension = { 1, 1 },
		grid_position = { 18, 19 },
		type = "Obstacle",
	},

	Entity229 = {
		dimension = { 1, 1 },
		grid_position = { 19, 19 },
		type = "Obstacle",
	},

	Entity228 = {
		dimension = { 1, 1 },
		grid_position = { 19, 20 },
		type = "Obstacle",
	},

	Entity227 = {
		dimension = { 1, 1 },
		grid_position = { 20, 20 },
		type = "Obstacle",
	},

	Entity226 = {
		dimension = { 1, 1 },
		grid_position = { 20, 21 },
		type = "Obstacle",
	},

	Entity225 = {
		dimension = { 1, 1 },
		grid_position = { 21, 21 },
		type = "Obstacle",
	},

	Entity224 = {
		dimension = { 1, 1 },
		grid_position = { 21, 22 },
		type = "Obstacle",
	},

	Entity254 = {
		dimension = { 1, 1 },
		grid_position = { 6, 7 },
		type = "Obstacle",
	},

	Entity255 = {
		dimension = { 1, 1 },
		grid_position = { 6, 6 },
		type = "Obstacle",
	},

	Entity252 = {
		dimension = { 1, 1 },
		grid_position = { 7, 8 },
		type = "Obstacle",
	},

	Entity253 = {
		dimension = { 1, 1 },
		grid_position = { 7, 7 },
		type = "Obstacle",
	},

	Entity250 = {
		dimension = { 1, 1 },
		grid_position = { 8, 9 },
		type = "Obstacle",
	},

	Entity251 = {
		dimension = { 1, 1 },
		grid_position = { 8, 8 },
		type = "Obstacle",
	},

	Entity248 = {
		dimension = { 1, 1 },
		grid_position = { 9, 10 },
		type = "Obstacle",
	},

	Entity249 = {
		dimension = { 1, 1 },
		grid_position = { 9, 9 },
		type = "Obstacle",
	},

	Entity246 = {
		dimension = { 1, 1 },
		grid_position = { 10, 11 },
		type = "Obstacle",
	},

	Entity247 = {
		dimension = { 1, 1 },
		grid_position = { 10, 10 },
		type = "Obstacle",
	},

	Entity244 = {
		dimension = { 1, 1 },
		grid_position = { 11, 12 },
		type = "Obstacle",
	},

	Entity245 = {
		dimension = { 1, 1 },
		grid_position = { 11, 11 },
		type = "Obstacle",
	},

	Entity242 = {
		dimension = { 1, 1 },
		grid_position = { 12, 13 },
		type = "Obstacle",
	},

	Entity243 = {
		dimension = { 1, 1 },
		grid_position = { 12, 12 },
		type = "Obstacle",
	},

	Entity240 = {
		dimension = { 1, 1 },
		grid_position = { 13, 14 },
		type = "Obstacle",
	},

	Entity241 = {
		dimension = { 1, 1 },
		grid_position = { 13, 13 },
		type = "Obstacle",
	},

	Entity275 = {
		dimension = { 1, 1 },
		grid_position = { 54, 85 },
		type = "Obstacle",
	},

	Entity274 = {
		dimension = { 1, 1 },
		grid_position = { 53, 85 },
		type = "Obstacle",
	},

	Entity273 = {
		dimension = { 1, 1 },
		grid_position = { 53, 86 },
		type = "Obstacle",
	},

	Entity272 = {
		dimension = { 1, 1 },
		grid_position = { 52, 86 },
		type = "Obstacle",
	},

	Entity279 = {
		dimension = { 1, 1 },
		grid_position = { 55, 82 },
		type = "Obstacle",
	},

	Entity278 = {
		dimension = { 1, 1 },
		grid_position = { 55, 83 },
		type = "Obstacle",
	},

	Entity277 = {
		dimension = { 1, 1 },
		grid_position = { 54, 83 },
		type = "Obstacle",
	},

	Entity276 = {
		dimension = { 1, 1 },
		grid_position = { 54, 84 },
		type = "Obstacle",
	},

	Entity283 = {
		dimension = { 1, 1 },
		grid_position = { 57, 80 },
		type = "Obstacle",
	},

	Entity282 = {
		dimension = { 1, 1 },
		grid_position = { 56, 80 },
		type = "Obstacle",
	},

	Entity281 = {
		dimension = { 1, 1 },
		grid_position = { 56, 81 },
		type = "Obstacle",
	},

	Entity280 = {
		dimension = { 1, 1 },
		grid_position = { 55, 81 },
		type = "Obstacle",
	},

	Entity287 = {
		dimension = { 1, 1 },
		grid_position = { 58, 77 },
		type = "Obstacle",
	},

	Entity286 = {
		dimension = { 1, 1 },
		grid_position = { 58, 78 },
		type = "Obstacle",
	},

	Entity285 = {
		dimension = { 1, 1 },
		grid_position = { 57, 78 },
		type = "Obstacle",
	},

	Entity284 = {
		dimension = { 1, 1 },
		grid_position = { 57, 79 },
		type = "Obstacle",
	},

	Entity258 = {
		dimension = { 1, 1 },
		grid_position = { 5, 4 },
		type = "Obstacle",
	},

	Entity259 = {
		dimension = { 1, 1 },
		grid_position = { 4, 4 },
		type = "Obstacle",
	},

	Entity256 = {
		dimension = { 1, 1 },
		grid_position = { 5, 6 },
		type = "Obstacle",
	},

	Entity257 = {
		dimension = { 1, 1 },
		grid_position = { 5, 5 },
		type = "Obstacle",
	},

	Entity262 = {
		dimension = { 1, 1 },
		grid_position = { 3, 2 },
		type = "Obstacle",
	},

	Entity263 = {
		dimension = { 1, 1 },
		grid_position = { 3, 1 },
		type = "Obstacle",
	},

	Entity260 = {
		dimension = { 1, 1 },
		grid_position = { 4, 3 },
		type = "Obstacle",
	},

	Entity261 = {
		dimension = { 1, 1 },
		grid_position = { 4, 2 },
		type = "Obstacle",
	},

	Entity266 = {
		dimension = { 1, 1 },
		grid_position = { 1, 0 },
		type = "Obstacle",
	},

	Entity267 = {
		dimension = { 1, 1 },
		grid_position = { 0, 0 },
		type = "Obstacle",
	},

	Entity264 = {
		dimension = { 1, 1 },
		grid_position = { 2, 1 },
		type = "Obstacle",
	},

	Entity265 = {
		dimension = { 1, 1 },
		grid_position = { 2, 0 },
		type = "Obstacle",
	},

	Entity270 = {
		dimension = { 1, 1 },
		grid_position = { 51, 87 },
		type = "Obstacle",
	},

	Entity271 = {
		dimension = { 1, 1 },
		grid_position = { 52, 87 },
		type = "Obstacle",
	},

	Entity268 = {
		dimension = { 1, 1 },
		grid_position = { 51, 89 },
		type = "Obstacle",
	},

	Entity269 = {
		dimension = { 1, 1 },
		grid_position = { 51, 88 },
		type = "Obstacle",
	},

	Entity305 = {
		dimension = { 1, 1 },
		grid_position = { 69, 74 },
		type = "Obstacle",
	},

	Entity304 = {
		dimension = { 1, 1 },
		grid_position = { 69, 75 },
		type = "Obstacle",
	},

	Entity307 = {
		dimension = { 1, 1 },
		grid_position = { 70, 73 },
		type = "Obstacle",
	},

	Entity306 = {
		dimension = { 1, 1 },
		grid_position = { 70, 74 },
		type = "Obstacle",
	},

	Entity309 = {
		dimension = { 1, 1 },
		grid_position = { 71, 72 },
		type = "Obstacle",
	},

	Entity308 = {
		dimension = { 1, 1 },
		grid_position = { 71, 73 },
		type = "Obstacle",
	},

	Entity311 = {
		dimension = { 1, 1 },
		grid_position = { 72, 71 },
		type = "Obstacle",
	},

	Entity310 = {
		dimension = { 1, 1 },
		grid_position = { 72, 72 },
		type = "Obstacle",
	},

	Entity313 = {
		dimension = { 1, 1 },
		grid_position = { 71, 70 },
		type = "Obstacle",
	},

	Entity312 = {
		dimension = { 1, 1 },
		grid_position = { 72, 70 },
		type = "Obstacle",
	},

	Entity315 = {
		dimension = { 1, 1 },
		grid_position = { 70, 69 },
		type = "Obstacle",
	},

	Entity314 = {
		dimension = { 1, 1 },
		grid_position = { 71, 69 },
		type = "Obstacle",
	},

	Entity317 = {
		dimension = { 1, 1 },
		grid_position = { 70, 67 },
		type = "Obstacle",
	},

	Entity316 = {
		dimension = { 1, 1 },
		grid_position = { 70, 68 },
		type = "Obstacle",
	},

	Entity319 = {
		dimension = { 1, 1 },
		grid_position = { 69, 66 },
		type = "Obstacle",
	},

	Entity318 = {
		dimension = { 1, 1 },
		grid_position = { 69, 67 },
		type = "Obstacle",
	},

	Entity288 = {
		dimension = { 1, 1 },
		grid_position = { 59, 77 },
		type = "Obstacle",
	},

	Entity289 = {
		dimension = { 1, 1 },
		grid_position = { 59, 76 },
		type = "Obstacle",
	},

	Entity290 = {
		dimension = { 1, 1 },
		grid_position = { 60, 76 },
		type = "Obstacle",
	},

	Entity291 = {
		dimension = { 1, 1 },
		grid_position = { 60, 75 },
		type = "Obstacle",
	},

	Entity292 = {
		dimension = { 1, 1 },
		grid_position = { 60, 74 },
		type = "Obstacle",
	},

	Entity293 = {
		dimension = { 1, 1 },
		grid_position = { 61, 74 },
		type = "Obstacle",
	},

	Entity294 = {
		dimension = { 1, 1 },
		grid_position = { 61, 73 },
		type = "Obstacle",
	},

	Entity295 = {
		dimension = { 1, 1 },
		grid_position = { 62, 73 },
		type = "Obstacle",
	},

	Entity296 = {
		dimension = { 1, 1 },
		grid_position = { 63, 73 },
		type = "Obstacle",
	},

	Entity297 = {
		dimension = { 1, 1 },
		grid_position = { 64, 73 },
		type = "Obstacle",
	},

	Entity298 = {
		dimension = { 1, 1 },
		grid_position = { 65, 73 },
		type = "Obstacle",
	},

	Entity299 = {
		dimension = { 1, 1 },
		grid_position = { 66, 73 },
		type = "Obstacle",
	},

	Entity300 = {
		dimension = { 1, 1 },
		grid_position = { 67, 73 },
		type = "Obstacle",
	},

	Entity301 = {
		dimension = { 1, 1 },
		grid_position = { 67, 74 },
		type = "Obstacle",
	},

	Entity302 = {
		dimension = { 1, 1 },
		grid_position = { 68, 74 },
		type = "Obstacle",
	},

	Entity303 = {
		dimension = { 1, 1 },
		grid_position = { 68, 75 },
		type = "Obstacle",
	},

	Entity343 = {
		dimension = { 1, 1 },
		grid_position = { 61, 50 },
		type = "Obstacle",
	},

	Entity342 = {
		dimension = { 1, 1 },
		grid_position = { 61, 51 },
		type = "Obstacle",
	},

	Entity341 = {
		dimension = { 1, 1 },
		grid_position = { 62, 51 },
		type = "Obstacle",
	},

	Entity340 = {
		dimension = { 1, 1 },
		grid_position = { 62, 52 },
		type = "Obstacle",
	},

	Entity339 = {
		dimension = { 1, 1 },
		grid_position = { 62, 53 },
		type = "Obstacle",
	},

	Entity338 = {
		dimension = { 1, 1 },
		grid_position = { 63, 53 },
		type = "Obstacle",
	},

	Entity337 = {
		dimension = { 1, 1 },
		grid_position = { 63, 54 },
		type = "Obstacle",
	},

	Entity336 = {
		dimension = { 1, 1 },
		grid_position = { 63, 55 },
		type = "Obstacle",
	},

	Entity351 = {
		dimension = { 1, 1 },
		grid_position = { 58, 45 },
		type = "Obstacle",
	},

	Entity350 = {
		dimension = { 1, 1 },
		grid_position = { 58, 46 },
		type = "Obstacle",
	},

	Entity349 = {
		dimension = { 1, 1 },
		grid_position = { 59, 46 },
		type = "Obstacle",
	},

	Entity348 = {
		dimension = { 1, 1 },
		grid_position = { 59, 47 },
		type = "Obstacle",
	},

	Entity347 = {
		dimension = { 1, 1 },
		grid_position = { 59, 48 },
		type = "Obstacle",
	},

	Entity346 = {
		dimension = { 1, 1 },
		grid_position = { 60, 48 },
		type = "Obstacle",
	},

	Entity345 = {
		dimension = { 1, 1 },
		grid_position = { 60, 49 },
		type = "Obstacle",
	},

	Entity344 = {
		dimension = { 1, 1 },
		grid_position = { 61, 49 },
		type = "Obstacle",
	},

	Entity326 = {
		dimension = { 1, 1 },
		grid_position = { 67, 61 },
		type = "Obstacle",
	},

	Entity327 = {
		dimension = { 1, 1 },
		grid_position = { 66, 61 },
		type = "Obstacle",
	},

	Entity324 = {
		dimension = { 1, 1 },
		grid_position = { 67, 63 },
		type = "Obstacle",
	},

	Entity325 = {
		dimension = { 1, 1 },
		grid_position = { 67, 62 },
		type = "Obstacle",
	},

	Entity322 = {
		dimension = { 1, 1 },
		grid_position = { 68, 64 },
		type = "Obstacle",
	},

	Entity323 = {
		dimension = { 1, 1 },
		grid_position = { 67, 64 },
		type = "Obstacle",
	},

	Entity320 = {
		dimension = { 1, 1 },
		grid_position = { 68, 66 },
		type = "Obstacle",
	},

	Entity321 = {
		dimension = { 1, 1 },
		grid_position = { 68, 65 },
		type = "Obstacle",
	},

	Entity334 = {
		dimension = { 1, 1 },
		grid_position = { 63, 57 },
		type = "Obstacle",
	},

	Entity335 = {
		dimension = { 1, 1 },
		grid_position = { 63, 56 },
		type = "Obstacle",
	},

	Entity332 = {
		dimension = { 1, 1 },
		grid_position = { 64, 58 },
		type = "Obstacle",
	},

	Entity333 = {
		dimension = { 1, 1 },
		grid_position = { 64, 57 },
		type = "Obstacle",
	},

	Entity330 = {
		dimension = { 1, 1 },
		grid_position = { 65, 59 },
		type = "Obstacle",
	},

	Entity331 = {
		dimension = { 1, 1 },
		grid_position = { 64, 59 },
		type = "Obstacle",
	},

	Entity328 = {
		dimension = { 1, 1 },
		grid_position = { 66, 60 },
		type = "Obstacle",
	},

	Entity329 = {
		dimension = { 1, 1 },
		grid_position = { 65, 60 },
		type = "Obstacle",
	},

	Entity373 = {
		dimension = { 1, 1 },
		grid_position = { 47, 48 },
		type = "Obstacle",
	},

	Entity372 = {
		dimension = { 1, 1 },
		grid_position = { 48, 48 },
		type = "Obstacle",
	},

	Entity375 = {
		dimension = { 1, 1 },
		grid_position = { 46, 49 },
		type = "Obstacle",
	},

	Entity374 = {
		dimension = { 1, 1 },
		grid_position = { 47, 49 },
		type = "Obstacle",
	},

	Entity369 = {
		dimension = { 1, 1 },
		grid_position = { 49, 46 },
		type = "Obstacle",
	},

	Entity368 = {
		dimension = { 1, 1 },
		grid_position = { 50, 46 },
		type = "Obstacle",
	},

	Entity371 = {
		dimension = { 1, 1 },
		grid_position = { 48, 47 },
		type = "Obstacle",
	},

	Entity370 = {
		dimension = { 1, 1 },
		grid_position = { 49, 47 },
		type = "Obstacle",
	},

	Entity381 = {
		dimension = { 1, 1 },
		grid_position = { 43, 52 },
		type = "Obstacle",
	},

	Entity380 = {
		dimension = { 1, 1 },
		grid_position = { 44, 52 },
		type = "Obstacle",
	},

	Entity383 = {
		dimension = { 1, 1 },
		grid_position = { 42, 53 },
		type = "Obstacle",
	},

	Entity382 = {
		dimension = { 1, 1 },
		grid_position = { 43, 53 },
		type = "Obstacle",
	},

	Entity377 = {
		dimension = { 1, 1 },
		grid_position = { 45, 50 },
		type = "Obstacle",
	},

	Entity376 = {
		dimension = { 1, 1 },
		grid_position = { 46, 50 },
		type = "Obstacle",
	},

	Entity379 = {
		dimension = { 1, 1 },
		grid_position = { 44, 51 },
		type = "Obstacle",
	},

	Entity378 = {
		dimension = { 1, 1 },
		grid_position = { 45, 51 },
		type = "Obstacle",
	},

	Entity356 = {
		dimension = { 1, 1 },
		grid_position = { 56, 42 },
		type = "Obstacle",
	},

	Entity357 = {
		dimension = { 1, 1 },
		grid_position = { 56, 41 },
		type = "Obstacle",
	},

	Entity358 = {
		dimension = { 1, 1 },
		grid_position = { 55, 41 },
		type = "Obstacle",
	},

	Entity359 = {
		dimension = { 1, 1 },
		grid_position = { 54, 41 },
		type = "Obstacle",
	},

	Entity352 = {
		dimension = { 1, 1 },
		grid_position = { 58, 44 },
		type = "Obstacle",
	},

	Entity353 = {
		dimension = { 1, 1 },
		grid_position = { 58, 43 },
		type = "Obstacle",
	},

	Entity354 = {
		dimension = { 1, 1 },
		grid_position = { 57, 43 },
		type = "Obstacle",
	},

	Entity355 = {
		dimension = { 1, 1 },
		grid_position = { 57, 42 },
		type = "Obstacle",
	},

	Entity364 = {
		dimension = { 1, 1 },
		grid_position = { 52, 44 },
		type = "Obstacle",
	},

	Entity365 = {
		dimension = { 1, 1 },
		grid_position = { 51, 44 },
		type = "Obstacle",
	},

	Entity366 = {
		dimension = { 1, 1 },
		grid_position = { 51, 45 },
		type = "Obstacle",
	},

	Entity367 = {
		dimension = { 1, 1 },
		grid_position = { 50, 45 },
		type = "Obstacle",
	},

	Entity360 = {
		dimension = { 1, 1 },
		grid_position = { 54, 42 },
		type = "Obstacle",
	},

	Entity361 = {
		dimension = { 1, 1 },
		grid_position = { 53, 42 },
		type = "Obstacle",
	},

	Entity362 = {
		dimension = { 1, 1 },
		grid_position = { 53, 43 },
		type = "Obstacle",
	},

	Entity363 = {
		dimension = { 1, 1 },
		grid_position = { 52, 43 },
		type = "Obstacle",
	},

	Entity410 = {
		dimension = { 1, 1 },
		grid_position = { 33, 67 },
		type = "Obstacle",
	},

	Entity411 = {
		dimension = { 1, 1 },
		grid_position = { 33, 68 },
		type = "Obstacle",
	},

	Entity408 = {
		dimension = { 1, 1 },
		grid_position = { 32, 66 },
		type = "Obstacle",
	},

	Entity409 = {
		dimension = { 1, 1 },
		grid_position = { 32, 67 },
		type = "Obstacle",
	},

	Entity414 = {
		dimension = { 1, 1 },
		grid_position = { 34, 70 },
		type = "Obstacle",
	},

	Entity415 = {
		dimension = { 1, 1 },
		grid_position = { 34, 71 },
		type = "Obstacle",
	},

	Entity412 = {
		dimension = { 1, 1 },
		grid_position = { 33, 69 },
		type = "Obstacle",
	},

	Entity413 = {
		dimension = { 1, 1 },
		grid_position = { 34, 69 },
		type = "Obstacle",
	},

	Entity402 = {
		dimension = { 1, 1 },
		grid_position = { 33, 63 },
		type = "Obstacle",
	},

	Entity403 = {
		dimension = { 1, 1 },
		grid_position = { 32, 63 },
		type = "Obstacle",
	},

	Entity400 = {
		dimension = { 1, 1 },
		grid_position = { 34, 62 },
		type = "Obstacle",
	},

	Entity401 = {
		dimension = { 1, 1 },
		grid_position = { 33, 62 },
		type = "Obstacle",
	},

	Entity406 = {
		dimension = { 1, 1 },
		grid_position = { 31, 65 },
		type = "Obstacle",
	},

	Entity407 = {
		dimension = { 1, 1 },
		grid_position = { 31, 66 },
		type = "Obstacle",
	},

	Entity404 = {
		dimension = { 1, 1 },
		grid_position = { 32, 64 },
		type = "Obstacle",
	},

	Entity405 = {
		dimension = { 1, 1 },
		grid_position = { 31, 64 },
		type = "Obstacle",
	},

	Entity395 = {
		dimension = { 1, 1 },
		grid_position = { 36, 59 },
		type = "Obstacle",
	},

	Entity394 = {
		dimension = { 1, 1 },
		grid_position = { 37, 59 },
		type = "Obstacle",
	},

	Entity393 = {
		dimension = { 1, 1 },
		grid_position = { 37, 58 },
		type = "Obstacle",
	},

	Entity392 = {
		dimension = { 1, 1 },
		grid_position = { 38, 58 },
		type = "Obstacle",
	},

	Entity399 = {
		dimension = { 1, 1 },
		grid_position = { 34, 61 },
		type = "Obstacle",
	},

	Entity398 = {
		dimension = { 1, 1 },
		grid_position = { 35, 61 },
		type = "Obstacle",
	},

	Entity397 = {
		dimension = { 1, 1 },
		grid_position = { 35, 60 },
		type = "Obstacle",
	},

	Entity396 = {
		dimension = { 1, 1 },
		grid_position = { 36, 60 },
		type = "Obstacle",
	},

	Entity387 = {
		dimension = { 1, 1 },
		grid_position = { 40, 55 },
		type = "Obstacle",
	},

	Entity386 = {
		dimension = { 1, 1 },
		grid_position = { 41, 55 },
		type = "Obstacle",
	},

	Entity385 = {
		dimension = { 1, 1 },
		grid_position = { 41, 54 },
		type = "Obstacle",
	},

	Entity384 = {
		dimension = { 1, 1 },
		grid_position = { 42, 54 },
		type = "Obstacle",
	},

	Entity391 = {
		dimension = { 1, 1 },
		grid_position = { 38, 57 },
		type = "Obstacle",
	},

	Entity390 = {
		dimension = { 1, 1 },
		grid_position = { 39, 57 },
		type = "Obstacle",
	},

	Entity389 = {
		dimension = { 1, 1 },
		grid_position = { 39, 56 },
		type = "Obstacle",
	},

	Entity388 = {
		dimension = { 1, 1 },
		grid_position = { 40, 56 },
		type = "Obstacle",
	},

	Entity440 = {
		dimension = { 1, 1 },
		grid_position = { 38, 86 },
		type = "Obstacle",
	},

	Entity441 = {
		dimension = { 1, 1 },
		grid_position = { 37, 86 },
		type = "Obstacle",
	},

	Entity442 = {
		dimension = { 1, 1 },
		grid_position = { 37, 87 },
		type = "Obstacle",
	},

	Entity443 = {
		dimension = { 1, 1 },
		grid_position = { 37, 88 },
		type = "Obstacle",
	},

	Entity444 = {
		dimension = { 1, 1 },
		grid_position = { 37, 89 },
		type = "Obstacle",
	},

	DoorStage2Trigger = {
		dimension = { 3, 10 },
		grid_position = { 30, 64 },
		type = "DoorStage2Trigger",
		triggerFunction = "mission1DoorTrigger",
	},

	Entity432 = {
		dimension = { 1, 1 },
		grid_position = { 39, 79 },
		type = "Obstacle",
	},

	Entity433 = {
		dimension = { 1, 1 },
		grid_position = { 39, 80 },
		type = "Obstacle",
	},

	Entity434 = {
		dimension = { 1, 1 },
		grid_position = { 39, 81 },
		type = "Obstacle",
	},

	Entity435 = {
		dimension = { 1, 1 },
		grid_position = { 39, 82 },
		type = "Obstacle",
	},

	Entity436 = {
		dimension = { 1, 1 },
		grid_position = { 38, 82 },
		type = "Obstacle",
	},

	Entity437 = {
		dimension = { 1, 1 },
		grid_position = { 38, 83 },
		type = "Obstacle",
	},

	Entity438 = {
		dimension = { 1, 1 },
		grid_position = { 38, 84 },
		type = "Obstacle",
	},

	Entity439 = {
		dimension = { 1, 1 },
		grid_position = { 38, 85 },
		type = "Obstacle",
	},

	Entity425 = {
		dimension = { 1, 1 },
		grid_position = { 41, 74 },
		type = "Obstacle",
	},

	Entity424 = {
		dimension = { 1, 1 },
		grid_position = { 40, 74 },
		type = "Obstacle",
	},

	Entity427 = {
		dimension = { 1, 1 },
		grid_position = { 41, 76 },
		type = "Obstacle",
	},

	Entity426 = {
		dimension = { 1, 1 },
		grid_position = { 41, 75 },
		type = "Obstacle",
	},

	Entity429 = {
		dimension = { 1, 1 },
		grid_position = { 41, 78 },
		type = "Obstacle",
	},

	Entity428 = {
		dimension = { 1, 1 },
		grid_position = { 41, 77 },
		type = "Obstacle",
	},

	Entity431 = {
		dimension = { 1, 1 },
		grid_position = { 40, 79 },
		type = "Obstacle",
	},

	Entity430 = {
		dimension = { 1, 1 },
		grid_position = { 40, 78 },
		type = "Obstacle",
	},

	Entity417 = {
		dimension = { 1, 1 },
		grid_position = { 35, 72 },
		type = "Obstacle",
	},

	Entity416 = {
		dimension = { 1, 1 },
		grid_position = { 35, 71 },
		type = "Obstacle",
	},

	Entity419 = {
		dimension = { 1, 1 },
		grid_position = { 37, 72 },
		type = "Obstacle",
	},

	Entity418 = {
		dimension = { 1, 1 },
		grid_position = { 36, 72 },
		type = "Obstacle",
	},

	Entity421 = {
		dimension = { 1, 1 },
		grid_position = { 38, 73 },
		type = "Obstacle",
	},

	Entity420 = {
		dimension = { 1, 1 },
		grid_position = { 37, 73 },
		type = "Obstacle",
	},

	Entity423 = {
		dimension = { 1, 1 },
		grid_position = { 39, 74 },
		type = "Obstacle",
	},

	Entity422 = {
		dimension = { 1, 1 },
		grid_position = { 38, 74 },
		type = "Obstacle",
	},

	Entity478 = {
		dimension = { 1, 1 },
		grid_position = { 19, 67 },
		type = "Obstacle",
	},

	Entity479 = {
		dimension = { 1, 1 },
		grid_position = { 19, 68 },
		type = "Obstacle",
	},

	Entity476 = {
		dimension = { 1, 1 },
		grid_position = { 0, 58 },
		type = "Obstacle",
	},

	Entity477 = {
		dimension = { 1, 1 },
		grid_position = { 0, 57 },
		type = "Obstacle",
	},

	Entity474 = {
		dimension = { 1, 1 },
		grid_position = { 2, 58 },
		type = "Obstacle",
	},

	Entity475 = {
		dimension = { 1, 1 },
		grid_position = { 1, 58 },
		type = "Obstacle",
	},

	Entity472 = {
		dimension = { 1, 1 },
		grid_position = { 4, 58 },
		type = "Obstacle",
	},

	Entity473 = {
		dimension = { 1, 1 },
		grid_position = { 3, 58 },
		type = "Obstacle",
	},

	Entity470 = {
		dimension = { 1, 1 },
		grid_position = { 6, 58 },
		type = "Obstacle",
	},

	Entity471 = {
		dimension = { 1, 1 },
		grid_position = { 5, 58 },
		type = "Obstacle",
	},

	Entity468 = {
		dimension = { 1, 1 },
		grid_position = { 7, 59 },
		type = "Obstacle",
	},

	Entity469 = {
		dimension = { 1, 1 },
		grid_position = { 6, 59 },
		type = "Obstacle",
	},

	Entity466 = {
		dimension = { 1, 1 },
		grid_position = { 9, 59 },
		type = "Obstacle",
	},

	Entity467 = {
		dimension = { 1, 1 },
		grid_position = { 8, 59 },
		type = "Obstacle",
	},

	Entity464 = {
		dimension = { 1, 1 },
		grid_position = { 11, 59 },
		type = "Obstacle",
	},

	Entity465 = {
		dimension = { 1, 1 },
		grid_position = { 10, 59 },
		type = "Obstacle",
	},

	Entity463 = {
		dimension = { 1, 1 },
		grid_position = { 11, 60 },
		type = "Obstacle",
	},

	Entity462 = {
		dimension = { 1, 1 },
		grid_position = { 12, 60 },
		type = "Obstacle",
	},

	Entity461 = {
		dimension = { 1, 1 },
		grid_position = { 13, 60 },
		type = "Obstacle",
	},

	Entity460 = {
		dimension = { 1, 1 },
		grid_position = { 14, 60 },
		type = "Obstacle",
	},

	Entity459 = {
		dimension = { 1, 1 },
		grid_position = { 15, 60 },
		type = "Obstacle",
	},

	Entity458 = {
		dimension = { 1, 1 },
		grid_position = { 16, 60 },
		type = "Obstacle",
	},

	Entity457 = {
		dimension = { 1, 1 },
		grid_position = { 17, 60 },
		type = "Obstacle",
	},

	Entity456 = {
		dimension = { 1, 1 },
		grid_position = { 17, 61 },
		type = "Obstacle",
	},

	Entity455 = {
		dimension = { 1, 1 },
		grid_position = { 18, 61 },
		type = "Obstacle",
	},

	Entity454 = {
		dimension = { 1, 1 },
		grid_position = { 18, 62 },
		type = "Obstacle",
	},

	Entity453 = {
		dimension = { 1, 1 },
		grid_position = { 18, 63 },
		type = "Obstacle",
	},

	Entity452 = {
		dimension = { 1, 1 },
		grid_position = { 19, 63 },
		type = "Obstacle",
	},

	Entity451 = {
		dimension = { 1, 1 },
		grid_position = { 19, 65 },
		type = "Obstacle",
	},

	Entity450 = {
		dimension = { 1, 1 },
		grid_position = { 19, 64 },
		type = "Obstacle",
	},

	Entity449 = {
		dimension = { 1, 1 },
		grid_position = { 20, 65 },
		type = "Obstacle",
	},

	Entity448 = {
		dimension = { 1, 1 },
		grid_position = { 20, 66 },
		type = "Obstacle",
	},

	EnemyEnergyGenerator2 = {
		dimension = { 5, 5 },
		grid_position = { 87, 87 },
		type = "EnemyEnergyGenerator",
		deathFunction = "destroyGenerator2",
	},

	EnemyEnergyGenerator1 = {
		dimension = { 5, 5 },
		grid_position = { 6, 53 },
		type = "EnemyEnergyGenerator",
		deathFunction = "destroyGenerator1",
	},

	Entity504 = {
		dimension = { 1, 1 },
		grid_position = { 0, 74 },
		type = "Obstacle",
	},

	Entity500 = {
		dimension = { 1, 1 },
		grid_position = { 3, 73 },
		type = "Obstacle",
	},

	Entity501 = {
		dimension = { 1, 1 },
		grid_position = { 2, 73 },
		type = "Obstacle",
	},

	Entity502 = {
		dimension = { 1, 1 },
		grid_position = { 1, 73 },
		type = "Obstacle",
	},

	Entity503 = {
		dimension = { 1, 1 },
		grid_position = { 1, 74 },
		type = "Obstacle",
	},

	Entity496 = {
		dimension = { 1, 1 },
		grid_position = { 6, 72 },
		type = "Obstacle",
	},

	Entity497 = {
		dimension = { 1, 1 },
		grid_position = { 5, 72 },
		type = "Obstacle",
	},

	Entity498 = {
		dimension = { 1, 1 },
		grid_position = { 4, 72 },
		type = "Obstacle",
	},

	Entity499 = {
		dimension = { 1, 1 },
		grid_position = { 4, 73 },
		type = "Obstacle",
	},

	Entity493 = {
		dimension = { 1, 1 },
		grid_position = { 9, 72 },
		type = "Obstacle",
	},

	Entity492 = {
		dimension = { 1, 1 },
		grid_position = { 9, 71 },
		type = "Obstacle",
	},

	Entity495 = {
		dimension = { 1, 1 },
		grid_position = { 7, 72 },
		type = "Obstacle",
	},

	Entity494 = {
		dimension = { 1, 1 },
		grid_position = { 8, 72 },
		type = "Obstacle",
	},

	Entity489 = {
		dimension = { 1, 1 },
		grid_position = { 12, 71 },
		type = "Obstacle",
	},

	Entity488 = {
		dimension = { 1, 1 },
		grid_position = { 13, 71 },
		type = "Obstacle",
	},

	Entity491 = {
		dimension = { 1, 1 },
		grid_position = { 10, 71 },
		type = "Obstacle",
	},

	Entity490 = {
		dimension = { 1, 1 },
		grid_position = { 11, 71 },
		type = "Obstacle",
	},

	Entity485 = {
		dimension = { 1, 1 },
		grid_position = { 16, 71 },
		type = "Obstacle",
	},

	Entity484 = {
		dimension = { 1, 1 },
		grid_position = { 17, 70 },
		type = "Obstacle",
	},

	Entity487 = {
		dimension = { 1, 1 },
		grid_position = { 14, 71 },
		type = "Obstacle",
	},

	Entity486 = {
		dimension = { 1, 1 },
		grid_position = { 15, 71 },
		type = "Obstacle",
	},

	Entity481 = {
		dimension = { 1, 1 },
		grid_position = { 18, 69 },
		type = "Obstacle",
	},

	Entity480 = {
		dimension = { 1, 1 },
		grid_position = { 19, 69 },
		type = "Obstacle",
	},

	Entity483 = {
		dimension = { 1, 1 },
		grid_position = { 17, 71 },
		type = "Obstacle",
	},

	Entity482 = {
		dimension = { 1, 1 },
		grid_position = { 18, 70 },
		type = "Obstacle",
	},

	Entity550 = {
		dimension = { 1, 1 },
		grid_position = { 40, 36 },
		type = "Turret",
	},

	Entity551 = {
		dimension = { 1, 1 },
		grid_position = { 38, 35 },
		type = "Turret",
	},

	Entity548 = {
		dimension = { 1, 1 },
		grid_position = { 44, 36 },
		type = "Turret",
	},

	Entity549 = {
		dimension = { 1, 1 },
		grid_position = { 42, 36 },
		type = "Turret",
	},

	Entity546 = {
		dimension = { 1, 1 },
		grid_position = { 48, 36 },
		type = "Turret",
	},

	Entity547 = {
		dimension = { 1, 1 },
		grid_position = { 46, 36 },
		type = "Turret",
	},

	Entity544 = {
		dimension = { 1, 1 },
		grid_position = { 52, 33 },
		type = "Turret",
	},

	Entity545 = {
		dimension = { 1, 1 },
		grid_position = { 50, 35 },
		type = "Turret",
	},

	Entity558 = {
		dimension = { 1, 1 },
		grid_position = { 6, 86 },
		type = "Enemy",
	},

	Entity559 = {
		dimension = { 1, 1 },
		grid_position = { 8, 85 },
		type = "Enemy",
	},

	Entity556 = {
		dimension = { 1, 1 },
		grid_position = { 4, 83 },
		type = "Enemy",
	},

	Entity557 = {
		dimension = { 1, 1 },
		grid_position = { 3, 81 },
		type = "Enemy",
	},

	Entity554 = {
		dimension = { 1, 1 },
		grid_position = { 35, 29 },
		type = "Turret",
	},

	Entity555 = {
		dimension = { 1, 1 },
		grid_position = { 2, 83 },
		type = "Enemy",
	},

	Entity552 = {
		dimension = { 1, 1 },
		grid_position = { 36, 33 },
		type = "Turret",
	},

	Entity553 = {
		dimension = { 1, 1 },
		grid_position = { 35, 31 },
		type = "Turret",
	},

	Entity567 = {
		dimension = { 1, 1 },
		grid_position = { 9, 46 },
		type = "Enemy",
	},

	Entity566 = {
		dimension = { 1, 1 },
		grid_position = { 10, 47 },
		type = "Enemy",
	},

	Entity565 = {
		dimension = { 1, 1 },
		grid_position = { 11, 48 },
		type = "Enemy",
	},

	Entity564 = {
		dimension = { 1, 1 },
		grid_position = { 11, 50 },
		type = "Enemy",
	},

	Entity563 = {
		dimension = { 1, 1 },
		grid_position = { 8, 48 },
		type = "Enemy",
	},

	Entity562 = {
		dimension = { 1, 1 },
		grid_position = { 9, 50 },
		type = "Enemy",
	},

	Entity561 = {
		dimension = { 1, 1 },
		grid_position = { 9, 52 },
		type = "Enemy",
	},

	Entity560 = {
		dimension = { 1, 1 },
		grid_position = { 8, 87 },
		type = "Enemy",
	},

	Entity575 = {
		dimension = { 1, 1 },
		grid_position = { 30, 60 },
		type = "Enemy",
	},

	Entity574 = {
		dimension = { 1, 1 },
		grid_position = { 30, 59 },
		type = "Enemy",
	},

	Entity573 = {
		dimension = { 1, 1 },
		grid_position = { 27, 58 },
		type = "Enemy",
	},

	Entity572 = {
		dimension = { 1, 1 },
		grid_position = { 26, 60 },
		type = "Enemy",
	},

	Entity571 = {
		dimension = { 1, 1 },
		grid_position = { 24, 58 },
		type = "Enemy",
	},

	Entity570 = {
		dimension = { 1, 1 },
		grid_position = { 21, 60 },
		type = "Enemy",
	},

	Entity569 = {
		dimension = { 1, 1 },
		grid_position = { 23, 60 },
		type = "Enemy",
	},

	Entity568 = {
		dimension = { 1, 1 },
		grid_position = { 11, 52 },
		type = "Enemy",
	},

	Entity541 = {
		dimension = { 1, 1 },
		grid_position = { 52, 27 },
		type = "Turret",
	},

	Entity540 = {
		dimension = { 1, 1 },
		grid_position = { 52, 25 },
		type = "Turret",
	},

	Entity543 = {
		dimension = { 1, 1 },
		grid_position = { 52, 31 },
		type = "Turret",
	},

	Entity542 = {
		dimension = { 1, 1 },
		grid_position = { 52, 29 },
		type = "Turret",
	},

	EnemyDoor = {
		dimension = { 2, 10 },
		grid_position = { 30, 66 },
		type = "EnemyDoor",
	},

	CentroInformatico = {
		dimension = { 5, 5 },
		grid_position = { 47, 31 },
		type = "CentroMando",
	},

	Entity539 = {
		dimension = { 1, 1 },
		grid_position = { 52, 23 },
		type = "Turret",
	},

	EnemyBoss = {
		dimension = { 1, 1 },
		grid_position = { 3, 86 },
		type = "EnemyBoss",
		deathFunction = "mission1End",
	},

	Entity576 = {
		dimension = { 1, 1 },
		grid_position = { 32, 57 },
		type = "Enemy",
	},

	Entity577 = {
		dimension = { 1, 1 },
		grid_position = { 85, 81 },
		type = "Enemy",
	},

	Entity578 = {
		dimension = { 1, 1 },
		grid_position = { 84, 79 },
		type = "Enemy",
	},

	Entity579 = {
		dimension = { 1, 1 },
		grid_position = { 83, 81 },
		type = "Enemy",
	},

	Entity580 = {
		dimension = { 1, 1 },
		grid_position = { 82, 79 },
		type = "Enemy",
	},

	Entity581 = {
		dimension = { 1, 1 },
		grid_position = { 81, 81 },
		type = "Enemy",
	},

	Entity582 = {
		dimension = { 1, 1 },
		grid_position = { 80, 80 },
		type = "Enemy",
	},

	Entity583 = {
		dimension = { 1, 1 },
		grid_position = { 80, 83 },
		type = "Enemy",
	},

	Entity584 = {
		dimension = { 1, 1 },
		grid_position = { 79, 84 },
		type = "Enemy",
	},

	Entity585 = {
		dimension = { 1, 1 },
		grid_position = { 78, 82 },
		type = "Enemy",
	},

	Entity586 = {
		dimension = { 1, 1 },
		grid_position = { 80, 85 },
		type = "Enemy",
	},

	Entity587 = {
		dimension = { 1, 1 },
		grid_position = { 78, 86 },
		type = "Enemy",
	},

	Entity588 = {
		dimension = { 1, 1 },
		grid_position = { 80, 87 },
		type = "Enemy",
	},

}