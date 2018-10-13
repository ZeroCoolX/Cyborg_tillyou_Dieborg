#include "Wall.h"


Wall::Wall(AnimationSet* animSet)
{
	m_animSet = animSet;

	// Default setup
	m_solid = true;
	m_collisionBoxWidth = 32;
	m_collisionBoxHeight = 32;
	m_collisionBoxYOffset = -16;

	update_collision_box();
	change_animation(0, false);
}

void Wall::update()
{
	update_collision_box();

	if (m_currentFrame == NULL || m_currentAnim == NULL) {
		return;
	}

	m_frameTimer += TimeController::s_timeController.m_deltaTimeInSeconds;
	if (m_frameTimer >= m_currentFrame->m_duration) {
		m_currentFrame = m_currentAnim->get_next_frame(m_currentFrame);
		m_frameTimer = 0;
	}
}

void Wall::change_animation(int newState, bool resetFrameToStart)
{
	m_currentAnim = m_animSet->get_animation(WALL_ANIMATION_NAME);
	m_currentFrame = m_currentAnim->get_frame(0);
}
