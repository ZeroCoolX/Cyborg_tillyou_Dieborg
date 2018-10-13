#ifndef ENTITY
#define ENTITY

#include "Globals.h"
#include "TimeController.h"
#include "AnimationSet.h"

// ABSTRACT CLASS
class Entity {
public:
	// reference constants for direction
	static const int DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_NONE;

	// quick lable to see what the entity is up to
	int state;

	// position
	float x, y;
	int direction;
	
	// physical mass
	bool solid = true; // can things pass through me, default to everything true
	bool collideWithSolids = true;
	
	// state
	bool active = true; // entity turned [on] or off
	string type = "entity";
	
	// movement
	bool moving; // is the entity moving
	float moveAngle;
	float moveSpeed;
	float maxMoveSpeed;
	float pushbackAngle;
	float pushbackAmount;
	float moveLerp = 4;
	// possible deprecated and can be removed
	float totalXMove, totalYMove;

	// collision
	SDL_Rect collisionBox; // Box describing the size of the collider
	SDL_Rect lastCollisionBox; // Last position of our collision box
	int collisionBoxWidth, collisionBoxHeight;
	float collisionBoxYOffset; // From my entities y value, where should I sit this collisionBox

	AnimationSet* animSet; // All possible animations for entity
	Animation* currentAnim; // Currently used animation
	Frame* currentFrame;
	float frameTimer; // Helps animate frame to frame

public:
// VIRTUAL FUNCTIONS
	virtual void update();
	virtual void draw();
	virtual void move(float angle);
	virtual void update_movement();
	virtual void update_collision_box();
	virtual void change_animation(int newState, bool resetFrameToStart) = 0; // abstract and MUST be overridden
	virtual void update_collisions(); // How we bump into stuff in the world

// HELPER FUNCTIONS
	static float distance_between_two_rects(SDL_Rect& r1, SDL_Rect& r2);
	static float distance_between_two_entities(Entity* e1, Entity* e2);
	static float angle_between_two_entities(Entity* e1, Entity* e2);
	static bool check_collides_with(SDL_Rect cbox, SDL_Rect otherCBox);
	static int angle_to_direction(float angle);
	static float angle_between_two_points(float e1X, float e1Y, float e2X, float e2Y);
	static float angle_between_two_rects(SDL_Rect& r1, SDL_Rect& r2);

public:
	static list<Entity*> entities;
	static bool entity_compare(const Entity* const& entity, const Entity* const& otherEntity); // const pointer pointing to a const Entity (compare by Y)
	static void remove_inactive_entities(list<Entity*> *entityList, bool deleteEntities);
	static void remove_all_entities(list<Entity*> *entityList);
};

#endif // !ENTITIY
