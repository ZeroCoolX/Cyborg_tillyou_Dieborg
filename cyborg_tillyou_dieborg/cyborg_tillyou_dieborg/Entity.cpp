#include "Entity.h"
#include <math.h>

const int Entity::DIR_UP=0, DIR_DOWN=1, DIR_LEFT=2, DIR_RIGHT=3, DIR_NONE=-1;

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::update(){}// override me to do something useful

void Entity::draw()
{
	if (currentFrame != NULL && active) {
		currentFrame->draw(animSet->spriteSheet, x, y);
	}

	// draw collision box
	if (solid && Globals::debugging) {
		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &collisionBox);
	}
}

void Entity::move(float angle)
{
	moving = true;
	moveSpeed = maxMoveSpeed;
	moveAngle = angle;

	int newDirection = angle_to_direction(moveAngle);
	// if direction changed update current animation
	if (direction != newDirection) {
		direction = newDirection;
		change_animation(state, false);
	}
}

void Entity::update_movement()
{
	update_collision_box();
	// store collision box before we move
	lastCollisionBox = collisionBox;

	// reset total moves
	totalXMove = 0;
	totalYMove = 0;

	if (moveSpeed > 0) {
		float moveDist = moveSpeed*TimeController::timeController.deltaTimeInSeconds*moveLerp;
		if (moveDist > 0) {
			float xMove = moveDist* (cos(moveAngle * Globals::PI / 180));
			float yMove = moveDist* (sin(moveAngle * Globals::PI / 180));

			x += xMove;
			y += yMove;

			totalXMove = xMove;
			totalYMove = yMove;

			if (!moving) {
				moveSpeed -= moveDist;
			}
		}
	}

	if (pushbackAmount > 0) {
		float pushbackDist = pushbackAmount*TimeController::timeController.deltaTimeInSeconds*moveLerp;
		if (pushbackDist > 0) {
			float xMove = pushbackDist* (cos(pushbackAngle * Globals::PI / 180));
			float yMove = pushbackDist* (sin(pushbackAngle * Globals::PI / 180));

			x += xMove;
			y += yMove;

			totalXMove += xMove;
			totalYMove += yMove;
			pushbackAmount -= pushbackDist;
		}
		else {
			pushbackAmount = 0;
		}
	}
	// now that we've moved, move the collision box up to where we are now
	update_collision_box();
	// To help with collision checking, union collisionCox with lastCollisionBox
	SDL_UnionRect(&collisionBox, &lastCollisionBox, &collisionBox);
}

void Entity::update_collision_box()
{
}

void Entity::update_collisions()
{
}

float Entity::distance_between_two_rects(SDL_Rect & r1, SDL_Rect & r2)
{
	return 0.0f;
}

float Entity::distance_between_two_entities(Entity * e1, Entity * e2)
{
	return 0.0f;
}

float Entity::angle_between_two_entities(Entity * e1, Entity * e2)
{
	return 0.0f;
}

bool Entity::check_collides_with(SDL_Rect cbox, SDL_Rect otherCBox)
{
	return false;
}

int Entity::angle_to_direction(float angle)
{
	return 0;
}

float Entity::angle_between_two_points(float e1X, float e1Y, float e2X, float e2Y)
{
	return 0.0f;
}

float Entity::angle_between_two_rects(SDL_Rect & r1, SDL_Rect & r2)
{
	return 0.0f;
}

bool Entity::entity_compare(const Entity * const & entity, const Entity * const & otherEntity)
{
	return false;
}

void Entity::remove_inactive_entities(list<Entity*>* entityList, bool deleteEntities)
{
}

void Entity::remove_all_entities(list<Entity*>* entityList)
{
}
