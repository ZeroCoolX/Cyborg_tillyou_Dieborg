#include "LivingEntity.h"


void LivingEntity::update_hit_box()
{
	// Dependent on frame data inside: udemyCyborg.fdset
	// Assume damage is 0
	m_damage = 0;
	
	GroupBox* hitBoxes = (GroupBox*)GroupBuilder::find_group_by_name(HITBOX_NAME, m_currentFrame->m_frameData);
	if (hitBoxes != NULL && hitBoxes->number_of_data_in_group() > 0) {
		// This frame has a hitbox!
		// Ignore anything aside from the first hitbox in the list purposely
		SDL_Rect hitBox = hitBoxes->m_data.front();
		// where entity currently is + hitbox location
		m_damageAreaHitBox.x = (x - m_currentFrame->m_offset.x) + hitBox.x;
		m_damageAreaHitBox.y = (y - m_currentFrame->m_offset.y) + hitBox.y;
		m_damageAreaHitBox.w = hitBox.w;
		m_damageAreaHitBox.h = hitBox.h;
	}
}

void LivingEntity::update_invincible_timer()
{
}

void LivingEntity::draw()
{
}
