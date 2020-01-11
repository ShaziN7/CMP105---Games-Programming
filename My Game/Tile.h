#pragma once

#include "Framework/GameObject.h"
#include "States.h"


class Tile : public GameObject
{

public:

	Tile();
	~Tile();

	ColliderType getColliderType(); // Gets collider type
	void setColliderType(ColliderType); // Sets collider type


private:

	ColliderType colliderType; // Type of collider of the tile
};