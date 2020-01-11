#pragma once

#include "Enemy.h"


class Turret: public Enemy
{

public:

	Turret();
	~Turret();

	void update(float dt, AudioManager &audioManager); // Updates the turret
	void collisionResponse(GameObject* collider); // If there is a collision
	void resetAnimation(); // Resets the turret's animation
	void shouldAnimate(bool a); // If turret should animate


private:

	Animation spin; // Spin animation
	Animation explode; // Explode animation
	Animation* currentAnimation; // Pointer pointing to what animation should play
	float deathTimer; // Timer to keep the explosion playing before the turret dies
};