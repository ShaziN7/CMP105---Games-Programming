#pragma once

#include "Framework/GameObject.h"
#include "Framework/AudioManager.h"
#include "Framework/Animation.h"
#include "Enemy.h"
#include "States.h"


class Enemy: public GameObject
{

public:

	Enemy();
	~Enemy();

	sf::Vector2f getSpawnPoint(); // Gets enemy spawn point
	void setSpawnPoint(sf::Vector2f sp); // Sets enemy spawn point
	void setColliderType(ColliderType ct); // Sets enemy collider type


protected:

	sf::Vector2f spawnPoint; // Where the enemy should spawn
	ColliderType colliderType; // What type of collider the enemy is
};