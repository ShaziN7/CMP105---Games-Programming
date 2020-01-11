#pragma once

#include "Enemy.h"
#include "Framework/Vector.h"


class Drone: public Enemy
{

public:

	Drone();
	~Drone();

	void update(float dt, AudioManager &audioManager); // Updates the drone
	void collisionResponse(GameObject* collider); // If there is a collision
	void resetAnimation(); // Resets the drone's animation
	void setIsHit(bool h); // Sets if the drone has been hit
	void setHorizDirection(char); // Sets which direction the drone should move
	void setLeftTarget(int); // Sets the drones left target
	void setRightTarget(int); // Sets the drones right target
	void setAnimTimer(int); // Sets the animation timer
	void setDeathTimer(int); // Sets the death timer
	void setMoving(bool); // Sets if the drone is moving


private:

	Animation turn; // The turning animation of the drone
	Animation explode; // The explosion animation
	Animation* currentAnimation; // Pointer pointing to which animation should play

	char horizDirection; // Which direction the drone should move
	float animTimer; // Timer to control how long the animation should play
	float deathTimer; // Timer to keep the explosion playing before the drone dies
	int leftTarget; // Where the drone should move to if going left
	int rightTarget; // Where the drone should move to if going right
	sf::Vector2f direction; // The direction of the drone to be used in the vector
	sf::Vector2f target; // Where the drone is moving to
	const float speed = 100.f; // The speed of the drone
	bool moving; // If the drone is moving
	bool isHit; // If the drone has been hit
};