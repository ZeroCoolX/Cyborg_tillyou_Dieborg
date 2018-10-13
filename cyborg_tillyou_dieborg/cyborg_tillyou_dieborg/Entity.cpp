#include "Entity.h"

const int Entity::DIR_UP=0, Entity::DIR_DOWN=1, Entity::DIR_LEFT=2, Entity::DIR_RIGHT=3, Entity::DIR_NONE=-1;

list<Entity*> Entity::entities;

/* VIRTUAL FUNCTIONS */

void Entity::update(){}// override me to do something useful

void Entity::draw()
{
	if (m_currentFrame != NULL && m_active) {
		m_currentFrame->draw(m_animSet->m_spriteSheet, x, y);
	}

	// draw collision box
	if (m_solid && Globals::debugging) {
		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &m_collisionBox);
	}
}

void Entity::move(float angle)
{
	m_moving = true;
	m_moveSpeed = m_maxMoveSpeed;
	m_moveAngle = angle;

	int newDirection = angle_to_direction(m_moveAngle);
	// if direction changed update current animation
	if (m_direction != newDirection) {
		m_direction = newDirection;
		change_animation(m_state, false);
	}
}

void Entity::update_movement()
{
	update_collision_box();
	// store collision box before we move
	m_lastCollisionBox = m_collisionBox;

	// reset total moves
	m_totalXMove = 0;
	m_totalYMove = 0;

	if (m_moveSpeed > 0) {
		float moveDist = m_moveSpeed*TimeController::s_timeController.m_deltaTimeInSeconds*m_moveLerp;
		if (moveDist > 0) {
			float xMove = moveDist* (cos(m_moveAngle * Globals::PI / 180));
			float yMove = moveDist* (sin(m_moveAngle * Globals::PI / 180));

			x += xMove;
			y += yMove;

			m_totalXMove = xMove;
			m_totalYMove = yMove;

			if (!m_moving) {
				m_moveSpeed -= moveDist;
			}
		}
	}

	if (m_pushbackAmount > 0) {
		float pushbackDist = m_pushbackAmount*TimeController::s_timeController.m_deltaTimeInSeconds*m_moveLerp;
		if (pushbackDist > 0) {
			float xMove = pushbackDist* (cos(m_pushbackAngle * Globals::PI / 180));
			float yMove = pushbackDist* (sin(m_pushbackAngle * Globals::PI / 180));

			x += xMove;
			y += yMove;

			m_totalXMove += xMove;
			m_totalYMove += yMove;
			m_pushbackAmount -= pushbackDist;
		}
		else {
			m_pushbackAmount = 0;
		}
	}
	// now that we've moved, move the collision box up to where we are now
	update_collision_box();
	// To help with collision checking, union collisionCox with lastCollisionBox
	SDL_UnionRect(&m_collisionBox, &m_lastCollisionBox, &m_collisionBox);
}

void Entity::update_collision_box()
{
	// center collision box 
	m_collisionBox.x = x - m_collisionBox.w / 2;
	m_collisionBox.y = y + m_collisionBoxYOffset;
	m_collisionBox.w = m_collisionBoxWidth;
	m_collisionBox.h = m_collisionBoxHeight;
}

void Entity::update_collisions()
{
	// Don't want to check for collisions if standing still - just implementation for now
	if (m_active && m_collideWithSolids && (m_moveSpeed > 0 || m_pushbackAmount > 0)) {
		// List of potential collisions
		// this->collisionBox = union of where they were before and where they are now
		list<Entity*> collisions;
		for (auto entity = Entity::entities.begin(); entity != Entity::entities.end(); ++entity) {
			if ((*entity)->m_active  // must be active
				&& (*entity)->m_type != this->m_type // don't collide with same types (wall on wall or enemy on enemy)
				&& (*entity)->m_solid // must be solid to collide
				&& Entity::check_collides_with(m_collisionBox, (*entity)->m_collisionBox)) // colliders overlap 
			{
				collisions.push_back((*entity));
			}
		}
		// if we have anything in the collisions list we have to check them properly
		if (collisions.size() > 0) {
			update_collision_box();

			// Multisample check for collisions from where we started to where we are planning to move to
			// Calculate sample distance we are going to travel between checks
			float boxTravelChunk = 0;
			if (m_collisionBox.w < m_collisionBox.h) {
				boxTravelChunk = m_collisionBox.w / 4;
			}else{
				boxTravelChunk = m_collisionBox.h / 4;
			}

			// Use sampleBox to check for collisions from start point to end point moving at boxTravelChunk each sample
			SDL_Rect sampleBox = m_lastCollisionBox;
			float movementAngle = Entity::angle_between_two_rects(m_lastCollisionBox, m_collisionBox);

			bool foundCollision = false;
			while (!foundCollision) {
				SDL_Rect intersection;
				for (auto entity = collisions.begin(); entity != collisions.end(); ++entity) {
					if (SDL_IntersectRect(&sampleBox, &((*entity)->m_collisionBox), &intersection)) {
						// This indicates there was a collision - update!
						foundCollision = true;
						m_moveSpeed = 0;
						m_moving = false;
						// Update pushback basically the reverse angle 
						m_pushbackAngle = angle_between_two_entities((*entity), this);
						
						if (intersection.w < intersection.h) {
							// Check coming from left or right
							if (m_lastCollisionBox.x + m_lastCollisionBox.w / 2 < (*entity)->m_collisionBox.x + (*entity)->m_collisionBox.w / 2) {
								// came from left, move left for pushback
								sampleBox.x -= intersection.w;
							}
							else {
								// came from right, move right for pushback
								sampleBox.x += intersection.w;
							}
						}
						else {
							if (m_lastCollisionBox.y + m_lastCollisionBox.h / 2 < (*entity)->m_collisionBox.y + (*entity)->m_collisionBox.h / 2) {
								// came from up, move up for pushback
								sampleBox.y -= intersection.h;
							}
							else {
								// came from down, move down for pushback
								sampleBox.y += intersection.h;
							}
						}
					}
				}
				if (foundCollision || (sampleBox.x == m_collisionBox.x && sampleBox.y == m_collisionBox.y)) {
					break;
				}

				// Move sample box to next check spot
				if (distance_between_two_rects(sampleBox, m_collisionBox) > boxTravelChunk) {
					float xMove = boxTravelChunk*(cos(movementAngle*Globals::PI / 180));
					float yMove = boxTravelChunk*(sin(movementAngle*Globals::PI / 180));

					sampleBox.x += xMove;
					sampleBox.y += yMove;
				}
				else {
					sampleBox = m_collisionBox;
				}
			}
			if (foundCollision) {
				// move our entity to where the sample box ended up
				m_pushbackAmount = m_pushbackAmount / 2;
				x = sampleBox.x + sampleBox.w / 2;
				y = sampleBox.y - m_collisionBoxYOffset;
			}
			update_collision_box();
		}
	}
}

/* HELPER FUNCTIONS */
float Entity::distance_between_two_rects(SDL_Rect & r1, SDL_Rect & r2)
{
	SDL_Point p1, p2;
	p1.x = r1.x + r1.w / 2; // center x value of first rect
	p1.y = r1.y + r1.h / 2; // center y value of first rect

	p2.x = r2.x + r2.w / 2; // center x value of second rect
	p2.y = r2.y + r2.h / 2; // center y value of second rect

	// d = (x2 - x1)^2 + (y2 - y1)^2
	float dist = abs(sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
	return dist;
}

float Entity::distance_between_two_entities(Entity* e1, Entity* e2)
{
	return abs(sqrt(pow(e1->x - e1->x, 2) + pow(e2->y - e2->y, 2)));
}

float Entity::angle_between_two_entities(Entity* e1, Entity* e2)
{
	float dx, dy;
	float x1 = e1->x, y1 = e1->y, x2 = e2->x, y2 = e2->y;
	
	dx = x2 - x1;
	dy = y2 - y1;

	// angle in radians converted to degrees
	return atan2(dy, dx) * 180 / Globals::PI;
}

bool Entity::check_collides_with(SDL_Rect cbox, SDL_Rect otherCBox)
{
	return SDL_IntersectRect(&cbox, &otherCBox, nullptr);// don't care about storing the result - just checking if it intersects
	// other possibilities for collision is if a rectangle is inside another rectangle
}

// Convert 360 degree angle into const DIR
int Entity::angle_to_direction(float angle)
{
	if ((angle >= 0 && angle <= 45) || angle >= 315 && angle <= 360) {
		return DIR_RIGHT;
	}
	else if(angle > 45 && angle <= 135){
		return DIR_UP;
	}
	else if (angle > 135 && angle <= 225) {
		return DIR_LEFT;
	}
	else {
		return DIR_DOWN;
	}
}

float Entity::angle_between_two_points(float px1, float py1, float px2, float py2)
{
	float dx = px2 - px1;
	float dy = py2 - py1;
	return atan2(dx, dy) * 180 / Globals::PI;
}

float Entity::angle_between_two_rects(SDL_Rect& r1, SDL_Rect& r2)
{
	// center of first rectangle
	float px1 = r1.x + (r1.w / 2);
	float py1 = r1.y + (r1.h / 2);
	// center of second rectangle
	float px2 = r2.x + (r2.w / 2);
	float py2 = r2.y + (r2.h / 2);

	return angle_between_two_points(px1, py1, px2, py2);
}

// Compares if entity is > otherEntity based off Y value
bool Entity::entity_compare(const Entity* const& entity, const Entity* const& otherEntity)
{
	if (entity != 0 && otherEntity != 0) {
		return (entity->y < otherEntity->y);
	}
	else {
		// two empty entities
		return false;
	}

}

void Entity::remove_inactive_entities(list<Entity*>* entityList, bool deleteEntities)
{
	for (auto entityIterator = entityList->begin(); entityIterator != entityList->end();/*might be able to put ++ back in....*/) {
		if (!(*entityIterator)->m_active) {
			if (deleteEntities) {
				delete (*entityIterator);
			}
			entityIterator = entityList->erase(entityIterator);
		}
		else {
			++entityIterator;
		}
	}
}

void Entity::remove_all_entities(list<Entity*>* entityList, bool deleteEntities)
{
	for (auto entityIterator = entityList->begin(); entityIterator != entityList->end();/*might be able to put ++ back in....*/) {
		if (deleteEntities) {
				delete (*entityIterator);
		}
		entityIterator = entityList->erase(entityIterator);
	}
}
