#pragma once

#include "Framework/GameObject.h"


class Vehicle: public GameObject
{

public:

	Vehicle();
	~Vehicle();

	void update(float dt); // Updates vehicle
	void setDirection(char); // Sets vehicle direction
	void setThreshold(float); // Sets vehicle threshold
	

private:

	char direction; // Direction that vehicle is going
	float elapsedTime; // Timer counting time between vehicle moving
	float threshold; // Time that vehicle should move
};