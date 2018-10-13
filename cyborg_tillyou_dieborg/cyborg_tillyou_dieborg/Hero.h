#ifndef HERO_H
#define HERO_H

#include "Globals.h"
#include "LivingEntity.h"

class Hero : public LivingEntity {
public:
	const string TYPE = "hero";

// ANIMATIONS
	// movement
	static const string HERO_ANIM_UP;
	static const string HERO_ANIM_DOWN;
	static const string HERO_ANIM_LEFT;
	static const string HERO_ANIM_RIGHT;
	// idle
	static const string HERO_ANIM_IDLE_UP;
	static const string HERO_ANIM_IDLE_DOWN;
	static const string HERO_ANIM_IDLE_LEFT;
	static const string HERO_ANIM_IDLE_RIGHT;
	// slash
	static const string HERO_SLASH_ANIM_UP;
	static const string HERO_SLASH_ANIM_DOWN;
	static const string HERO_SLASH_ANIM_LEFT;
	static const string HERO_SLASH_ANIM_RIGHT;
	// dash
	static const string HERO_DASH_ANIM_UP;
	static const string HERO_DASH_ANIM_DOWN;
	static const string HERO_DASH_ANIM_LEFT;
	static const string HERO_DASH_ANIM_RIGHT;
	// death
	static const string HERO_DIE;

// STATES
	static const int HERO_STATE_IDLE, HERO_STATE_MOVE, HERO_STATE_SLASH, HERO_STATE_DASH, HERO_STATE_DEAD;

public:
	Hero(AnimationSet *animSet);
	void update();
	void slash();
	void dash();
	void die();
	void revive();
	void change_animation(int newState, bool resetFrameToBeginning);
	void update_animation();
	void update_damages();

private:
	bool can_play_special_animation();
};

#endif // !HERO_H
