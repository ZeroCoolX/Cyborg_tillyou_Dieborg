#include "Game.h"



Game::Game()
{
	string resPath = get_resource_path();
	m_backgroundImage = load_texture(resPath + "map.png", Globals::renderer);

	// Holds a list of group types.
	// The list describes the types of groups of data frames can have
	list<DataGroupType> dataGroupTypes;

	// What data can a frame have?
	// collisionBoxes (deprecated)
	DataGroupType collBoxType;
	collBoxType.m_groupName = "collisionBox";
	collBoxType.m_dataType = DataGroupType::DATATYPE_BOX;
	dataGroupTypes.push_back(collBoxType);

	// hitBoxes
	DataGroupType hitBoxType;
	hitBoxType.m_groupName = "hitBox";
	hitBoxType.m_dataType = DataGroupType::DATATYPE_BOX;
	dataGroupTypes.push_back(hitBoxType);

	// damage
	DataGroupType dmgType;
	dmgType.m_groupName = "damage";
	dmgType.m_dataType = DataGroupType::DATATYPE_NUMBER;
	dataGroupTypes.push_back(dmgType);

	m_heroAnimSet = new AnimationSet();
	m_heroAnimSet->load_animation_set("udemyCyborg.fdset", dataGroupTypes, true, 0, true);

	m_wallAnimSet = new AnimationSet();
	m_wallAnimSet->load_animation_set("wall.fdset", dataGroupTypes);

	// build hero entity
	m_hero = new Hero(m_heroAnimSet);
	m_hero->m_invincibleTimer = 0;
	m_hero->m_x = Globals::screenWidth / 2;
	m_hero->m_y = Globals::screenHeight / 2;

	// Tell keyboard input to manage hero
	m_heroInput.m_hero = m_hero;

	Entity::entities.push_back(m_hero);

	// Generate walls around the borders of the screen
	for (int i = 0; i < Globals::screenWidth / WALL_SPRITE_SIZE; ++i) {
		// fill in top
		Wall* newWall = new Wall(m_wallAnimSet);
		newWall->m_x = i * WALL_SPRITE_SIZE + (WALL_SPRITE_SIZE / 2);
		newWall->m_y = WALL_SPRITE_SIZE / 2;
		m_walls.push_back(newWall);
		Entity::entities.push_back(newWall);

		// fill in bottom
		newWall = new Wall(m_wallAnimSet);
		newWall->m_x = i * WALL_SPRITE_SIZE + (WALL_SPRITE_SIZE / 2);
		newWall->m_y = Globals::screenHeight - (WALL_SPRITE_SIZE / 2);
		m_walls.push_back(newWall);
		Entity::entities.push_back(newWall);
	}

	for (int i = 1; i < Globals::screenHeight / WALL_SPRITE_SIZE - 1; ++i) {
		// fill in left
		Wall* newWall = new Wall(m_wallAnimSet);
		newWall->m_x = WALL_SPRITE_SIZE / 2;
		newWall->m_y = i * WALL_SPRITE_SIZE + (WALL_SPRITE_SIZE / 2);
		m_walls.push_back(newWall);
		Entity::entities.push_back(newWall);

		// fill in right
		newWall = new Wall(m_wallAnimSet);
		newWall->m_x = Globals::screenWidth - (WALL_SPRITE_SIZE / 2);
		newWall->m_y = i * WALL_SPRITE_SIZE + (WALL_SPRITE_SIZE / 2);
		m_walls.push_back(newWall);
		Entity::entities.push_back(newWall);
	}

}


Game::~Game()
{
	cleanup(m_backgroundImage);
	Entity::remove_all_entities(&Entity::entities, false);

	delete m_heroAnimSet;
	delete m_wallAnimSet;
	delete m_hero;

	Entity::remove_all_entities(&m_walls, true);
}

void Game::update()
{
	bool quit = false;
	SDL_Event e;

	// Setup my time controller before the game starts
	TimeController::s_timeController.reset();
	
	while (!quit) {
		TimeController::s_timeController.update_time();
		
		Entity::remove_inactive_entities(&Entity::entities, false);

		// Check for any events that might have happened
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				// which button was pressed in this event
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					quit = true;
					break;
				case SDL_SCANCODE_SPACE: // handy for testing
					m_hero->revive();
					break;
				}
			}
			// Let the KeyboardInput class handle everything else
			m_heroInput.update(&e);
		}

		for (auto entityIterator = Entity::entities.begin(); entityIterator != Entity::entities.end(); ++entityIterator) {
			(*entityIterator)->update();
		}

		// draw all entities
		draw();
	}
}

void Game::draw()
{
	// Clear the screen with flat grey
	SDL_SetRenderDrawColor(Globals::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Globals::renderer);

	// Draw the background
	render_texture(m_backgroundImage, Globals::renderer, 0, 0);

	// sort all entities based on Y depth
	Entity::entities.sort(Entity::entity_compare);

	// Draw all of the entities
	for (auto entityIterator = Entity::entities.begin(); entityIterator != Entity::entities.end(); ++entityIterator) {
		(*entityIterator)->draw();
	}

	// after we're done drawing/rendering show it to the world
	SDL_RenderPresent(Globals::renderer);
}
