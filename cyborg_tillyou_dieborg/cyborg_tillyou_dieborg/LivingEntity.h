#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "Entity.h"

// ABSTRACT CLASS
class LivingEntity : public Entity {
public:
	const string HITBOX_NAME = "hitBox";

	int m_health, m_maxHealth;
	int m_damage = 0;
	SDL_Rect m_damageAreaHitBox; // similar to collision box but describes damaging area

	float m_invincibleTimer = 0;

// VIRTUAL FUNCTIONS
	virtual void update_hit_box();
	virtual void update_damages() = 0; // Defines how we get damages by other things
	virtual void die() = 0; // up to implementations to decide how they die
	virtual void update_invincible_timer();

// OVERRIDDEN FUNCTIONS
	void draw();
};

#endif // !LIVINGENTITY_H
