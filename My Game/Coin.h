#pragma once

#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/AudioManager.h"


class Coin: public GameObject
{

public:

	Coin();
	~Coin();

	void update(float dt); // Updates the coin
	void collisionResponse(GameObject* collider, AudioManager &audioManager); // If there is a collision
	void setSpawnPoint(sf::Vector2f sp); // Sets the spawn point
	sf::Vector2f getSpawnPoint(); // Returns the spawn point


private:

	Animation spin; // Animation for the coin spinning
	sf::Vector2f spawnPoint; // Spawn point of the coin
};