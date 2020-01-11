#include "Vehicle.h"


Vehicle::Vehicle()
{
	// Initialises variables
	elapsedTime = 0;
	threshold = 0;
}

Vehicle::~Vehicle()
{
}


void Vehicle::update(float dt)
{
	elapsedTime += dt; // Starts elapsed time timer

	// If elapsed time is higher than threshold, move vehicle
	if (elapsedTime > threshold)
	{
		move(velocity*dt);
		
		// If vehicle hits the left target, reset timer and stop vehicle moving
		if (direction == 'l' && getPosition().x <= -600)
		{
			elapsedTime = 0.f;
			setPosition(6000 + getSize().x, getPosition().y);
		}

		// If vehicle hits the right target, reset timer and stop vehicle moving
		else if (direction == 'r' && getPosition().x >= 6000)
		{
			elapsedTime = 0.f;
			setPosition(0 - getSize().x, getPosition().y);
		}
	}
}

// Sets vehicle direction
void Vehicle::setDirection(char d)
{
	direction = d;
}

// Sets vehicle threshold
void Vehicle::setThreshold(float t)
{
	threshold = t;
}