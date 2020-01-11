#pragma once

#include <iostream>

#include "Framework/Animation.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Turret.h"
#include "Drone.h"


enum class BulletType {PLAYER, ENEMY}; // Keeps track of if the bullet was fired by the player or the enemy


class Bullet: public GameObject
{

public:

	Bullet();
	~Bullet();

	void update(float dt); // Updates the bullet
	void collisionResponse(GameObject* collider); // If there is a collision
	BulletType getBulletType(); // Returns the type of bullet
	void setBulletType(BulletType bt); // Sets the type of bullet


private:

	Animation shot; // The default bullet firing animation
	Animation shotHit; // The animation for when the bullet has hit something
	Animation* currentAnimation; // A pointer pointing to which animation is currently to play

	float animTimer; // A timer to make sure the animation plays before the bullet dies
	BulletType bulletType; // If the bullet is from the player or enemy
};