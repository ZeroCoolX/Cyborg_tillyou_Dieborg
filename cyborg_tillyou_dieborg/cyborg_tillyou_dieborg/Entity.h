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
	int m_state;

	// position
	float m_x, m_y;
	int m_direction;
	
	// physical mass
	bool m_solid = true; // can things pass through me, default to everything true
	bool m_collideWithSolids = true;
	
	// state
	bool m_active = true; // entity turned [on] or off
	string m_type = "entity";
	
	// movement
	bool m_moving; // is the entity moving
	float m_moveAngle;
	float m_moveSpeed;
	float m_maxMoveSpeed;
	float m_pushbackAngle;
	float m_pushbackAmount;
	float m_moveLerp = 4;
	// possible deprecated and can be removed
	float m_totalXMove, m_totalYMove;

	// collision
	SDL_Rect m_collisionBox; // Box describing the size of the collider
	SDL_Rect m_lastCollisionBox; // Last position of our collision box
	int m_collisionBoxWidth, m_collisionBoxHeight;
	float m_collisionBoxYOffset; // From my entities y value, where should I sit this collisionBox

	AnimationSet* m_animSet; // All possible animations for entity
	Animation* m_currentAnim; // Currently used animation
	Frame* m_currentFrame;
	float m_frameTimer; // Helps animate frame to frame

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
	static void remove_all_entities(list<Entity*> *entityList, bool deleteEntities);
};

#endif // !ENTITIY
