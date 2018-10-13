#include "LivingEntity.h"


void LivingEntity::update_hit_box()
{
	// Dependent on frame data inside: udemyCyborg.fdset
	// Assume damage is 0
	m_damage = 0;
	
	GroupBox* hitBoxes = (GroupBox*)GroupBuilder::find_group_by_name(HITBOX_GROUP_NAME, m_currentFrame->m_frameData);
	if (hitBoxes != NULL && hitBoxes->number_of_data_in_group() > 0) {
		// read hitbox data and update
		SDL_Rect hitBox = hitBoxes->m_data.front();
		m_damageAreaHitBox.x = (x - m_currentFrame->m_offset.x) + hitBox.x;
		m_damageAreaHitBox.y = (y - m_currentFrame->m_offset.y) + hitBox.y;
		m_damageAreaHitBox.w = hitBox.w;
		m_damageAreaHitBox.h = hitBox.h;

		// read damage data and update
		GroupNumber* damages = (GroupNumber*)GroupBuilder::find_group_by_name(DAMAGE_GROUP_NAME, m_currentFrame->m_frameData);
		if (damages != NULL && damages->number_of_data_in_group() > 0) {
			m_damage = damages->m_data.front();
		}
	}
}

void LivingEntity::update_invincible_timer()
{
	if (m_invincibleTimer > 0) {
		m_invincibleTimer -= TimeController::s_timeController.m_deltaTimeInSeconds;
	}
}

// OVERRIDEN FUNCTIONS
void LivingEntity::draw()
{
	if (m_currentFrame != NULL && m_active) {
		m_currentFrame->draw(m_animSet->m_spriteSheet, x, y);
	}

	// draw collision box
	if (m_solid && Globals::debugging) {
		SDL_SetRenderDrawColor(Globals::renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &m_lastCollisionBox);

		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &m_collisionBox);

		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &m_damageAreaHitBox);
	}
}
