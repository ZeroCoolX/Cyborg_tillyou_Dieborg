#include "Hero.h"

// ANIMATIONS
// movement
const string Hero::HERO_ANIM_UP = "up";
const string Hero::HERO_ANIM_DOWN = "down";
const string Hero::HERO_ANIM_LEFT = "left";
const string Hero::HERO_ANIM_RIGHT = "right";
// idle
const string Hero::HERO_ANIM_IDLE_UP = "idleUp";
const string Hero::HERO_ANIM_IDLE_DOWN = "idleDown";
const string Hero::HERO_ANIM_IDLE_LEFT = "idleLeft";
const string Hero::HERO_ANIM_IDLE_RIGHT = "idleRight";
// slash
const string Hero::HERO_SLASH_ANIM_UP = "slashUp";
const string Hero::HERO_SLASH_ANIM_DOWN = "slashDown";
const string Hero::HERO_SLASH_ANIM_LEFT = "slashLeft";
const string Hero::HERO_SLASH_ANIM_RIGHT = "slashRight";
// dash
const string Hero::HERO_DASH_ANIM_UP = "dashUp";
const string Hero::HERO_DASH_ANIM_DOWN = "dashDown";
const string Hero::HERO_DASH_ANIM_LEFT = "dashLeft";
const string Hero::HERO_DASH_ANIM_RIGHT = "dashRight";
// death
const string Hero::HERO_DIE = "die";

// STATES
const int Hero::HERO_STATE_IDLE = 0, Hero::HERO_STATE_MOVE = 1, Hero::HERO_STATE_SLASH = 2, Hero::HERO_STATE_DASH = 3, Hero::HERO_STATE_DEAD = 4;


Hero::Hero(AnimationSet * animSet)
{
	m_animSet = animSet;
	m_type = TYPE;

	// Default setups
	m_x = Globals::screenWidth / 2;
	m_y = Globals::screenHeight / 2;
	m_moveSpeed = 0;
	m_maxMoveSpeed = 80;
	m_health = m_maxHealth = 20;
	m_damage = 0;
	m_collisionBoxWidth = 20;
	m_collisionBoxHeight = 24;
	m_collisionBoxYOffset = -20;

	m_direction = DIR_DOWN;
	
	change_animation(HERO_STATE_IDLE, true);
	update_collision_box();
}

void Hero::update()
{
	// Check if dead
	if (m_health < 1 && m_state != HERO_STATE_DEAD) {
		change_animation(HERO_STATE_DEAD, true);
		m_moving = false;
		die();
	}
	// Set collision box to where they are
	update_collision_box();
	// Move them
	update_movement();
	// Check if we collided during movment and move appropriately
	update_collisions();

	update_hit_box();
	update_damages();

	update_animation();
	update_invincible_timer();
}

void Hero::slash()
{
	if (!can_play_special_animation()) {
		return;
	}
	m_moving = false;
	m_frameTimer = 0;
	change_animation(HERO_STATE_SLASH, true);
	// TODO: add attack sound
}

void Hero::dash()
{
	if (!can_play_special_animation()) {
		return;
	}
	m_moving = false;
	m_frameTimer = 0;

	// push the hero in the direction they're traveling
	m_pushbackAngle = m_moveAngle;
	m_pushbackAmount = 300;
	m_invincibleTimer = 0.1;

	change_animation(HERO_STATE_DASH, true);
	// TODO: add dash sound
}

void Hero::die()
{
	m_moving = false;
	change_animation(HERO_STATE_DEAD, true);
}

void Hero::revive()
{
	m_health = m_maxHealth;
	change_animation(HERO_STATE_IDLE, true);
	m_moving = false;
	m_x = Globals::screenWidth / 2;
	m_y = Globals::screenHeight / 2;
	m_pushbackAmount = 0;
}

// This is god aweful - refactor this to use a map....
// using a map would make this 4-5 lines......terrible...take a lap
void Hero::change_animation(int newState, bool resetFrameToBeginning)
{
	m_state = newState;

	if (m_state == HERO_STATE_IDLE) {
		if(m_direction == DIR_DOWN){
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_IDLE_DOWN);
		}
		else if (m_direction == DIR_UP) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_IDLE_UP);
		}
		else if (m_direction == DIR_LEFT) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_IDLE_LEFT);
		}
		else if (m_direction == DIR_RIGHT) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_IDLE_RIGHT);
		}
	}
	else if (m_state == HERO_STATE_MOVE) {
		if (m_direction == DIR_DOWN) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_DOWN);
		}
		else if (m_direction == DIR_UP) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_UP);
		}
		else if (m_direction == DIR_LEFT) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_LEFT);
		}
		else if (m_direction == DIR_RIGHT) {
			m_currentAnim = m_animSet->get_animation(HERO_ANIM_RIGHT);
		}
	}
	else if (m_state == HERO_STATE_SLASH) {
		if (m_direction == DIR_DOWN) {
			m_currentAnim = m_animSet->get_animation(HERO_SLASH_ANIM_DOWN);
		}
		else if (m_direction == DIR_UP) {
			m_currentAnim = m_animSet->get_animation(HERO_SLASH_ANIM_UP);
		}
		else if (m_direction == DIR_LEFT) {
			m_currentAnim = m_animSet->get_animation(HERO_SLASH_ANIM_LEFT);
		}
		else if (m_direction == DIR_RIGHT) {
			m_currentAnim = m_animSet->get_animation(HERO_SLASH_ANIM_RIGHT);
		}
	}
	else if (m_state == HERO_STATE_DASH) {
		if (m_direction == DIR_DOWN) {
			m_currentAnim = m_animSet->get_animation(HERO_DASH_ANIM_DOWN);
		}
		else if (m_direction == DIR_UP) {
			m_currentAnim = m_animSet->get_animation(HERO_DASH_ANIM_UP);
		}
		else if (m_direction == DIR_LEFT) {
			m_currentAnim = m_animSet->get_animation(HERO_DASH_ANIM_LEFT);
		}
		else if (m_direction == DIR_RIGHT) {
			m_currentAnim = m_animSet->get_animation(HERO_DASH_ANIM_RIGHT);
		}
	}
	else if (m_state == HERO_STATE_DEAD) {
		m_currentAnim = m_animSet->get_animation(HERO_DIE);
	}

	if (resetFrameToBeginning) {
		m_currentFrame = m_currentAnim->get_frame(0);
	}
	else {
		m_currentFrame = m_currentAnim->get_frame(m_currentFrame->m_frameNumber);
	}
}

void Hero::update_animation()
{
	if (m_currentFrame == NULL || m_currentAnim == NULL) {
		return;
	}

	if (m_state == HERO_STATE_MOVE && !m_moving) {
		change_animation(HERO_STATE_IDLE, true);
	}
	if (m_state != HERO_STATE_MOVE && m_moving) {
		change_animation(HERO_STATE_MOVE, true);
	}

	m_frameTimer += TimeController::s_timeController.m_deltaTimeInSeconds;
	// Need to change frames
	if (m_frameTimer >= m_currentFrame->m_duration) {
		if (m_currentFrame->m_frameNumber == m_currentAnim->get_end_frame_number()) {
			// Account for non looping animations
			if (m_state == HERO_STATE_SLASH || m_state == HERO_STATE_DASH) {
				// Change back to moving
				change_animation(HERO_STATE_MOVE, true);
			}
			else if (m_state == HERO_STATE_DEAD && m_health > 0) {
				change_animation(HERO_STATE_MOVE, true);
			}
			else {
				m_currentFrame = m_currentAnim->get_frame(0);
			}
		}
		else {
			m_currentFrame = m_currentAnim->get_next_frame(m_currentFrame);
		}
		m_frameTimer = 0;
	}
}

void Hero::update_damages()
{
	if (m_active && m_health > 0 && m_invincibleTimer <= 0) {
		for (auto entityIterator = Entity::entities.begin(); entityIterator != Entity::entities.end(); ++entityIterator) {
			// TODO: swap hardcoded "enemy" with constant
			if ((*entityIterator)->m_active && (*entityIterator)->m_type == "enemy") {
				// we know enemies are living entities so cast it appropriately
				LivingEntity* enemy = (LivingEntity*)(*entityIterator);
				if (enemy->m_damage > 0 && Entity::check_collides_with(m_collisionBox, enemy->m_damageAreaHitBox)) {
					m_health -= enemy->m_damage;

					// Are we still alive?
					if (m_health > 0) {
						m_invincibleTimer = 0.3;
						// TODO: play getting hit sound here
					}

					m_pushbackAngle = Entity::angle_between_two_entities((*entityIterator), this);
					m_pushbackAmount = 200;
				}
			}
		}
	}
}

bool Hero::can_play_special_animation()
{
	return (m_health > 0 && (m_state == HERO_STATE_MOVE || m_state == HERO_STATE_IDLE));
}
