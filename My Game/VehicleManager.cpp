#include "VehicleManager.h"


VehicleManager::VehicleManager()
{
	// Loads the vehicle textures
	loadTextures();

	// Sets up vehicle vector
	for (int i = 0; i < 8; i++)
	{
		vehicles.push_back(Vehicle());
		vehicles[i].setAlive(false);
	}

	// Manually sets up vehicle objects
	setUpCars();
	setUpBikes();
	setUpTrucks();
	setUpPolice();
}

VehicleManager::~VehicleManager()
{
}


// Updates all vehicles
void VehicleManager::update(float dt)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
			vehicles[i].update(dt); // Moves and animates vehicle
	}
}

// Checks if vehicles are visible on screen and if so renders them
void VehicleManager::render(sf::RenderWindow* window, sf::View* view)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i].getVisible(*view))
		{
			window->draw(vehicles[i]);
		}
	}
}

// Loads all vehicle textures
void VehicleManager::loadTextures()
{
	carTexture.loadFromFile("gfx/vehicles/v-red.png");
	policeTexture.loadFromFile("gfx/vehicles/v-police.png");
	truckTexture.loadFromFile("gfx/vehicles/v-truck.png");
	bikeTexture.loadFromFile("gfx/vehicles/v-yellow.png");
}

// Sets up all car objects
void VehicleManager::setUpCars()
{
	vehicles[0].setTexture(&carTexture);
	vehicles[0].setSize(sf::Vector2f(96 * 2, 61 * 2));
	vehicles[0].setPosition(0 - vehicles[0].getSize().x, 1020);
	vehicles[0].scale(-1, 1); // Flips the sprite
	vehicles[0].setDirection('r'); // Sets direction to right
	vehicles[0].setVelocity(1000, 0);
	vehicles[0].setThreshold(3.f); // Time in between spawning

	vehicles[1].setTexture(&carTexture);
	vehicles[1].setSize(sf::Vector2f(96 * 2, 61 * 2));
	vehicles[1].setPosition(0 - vehicles[1].getSize().x, 100);
	vehicles[1].scale(-1, 1); // Flips the sprite
	vehicles[1].setDirection('r'); // Sets direction to right
	vehicles[1].setVelocity(800, 0);
	vehicles[1].setThreshold(3.f); // Time in between spawning
}

// Sets up all bike objects
void VehicleManager::setUpBikes()
{
	vehicles[2].setTexture(&bikeTexture);
	vehicles[2].setSize(sf::Vector2f(93 * 2, 60 * 2));
	vehicles[2].setPosition(0 - vehicles[2].getSize().x, 760);
	vehicles[2].scale(-1, 1); // Flips the sprite
	vehicles[2].setDirection('r'); // Sets direction to right
	vehicles[2].setVelocity(1400, 0);
	vehicles[2].setThreshold(2.f); // Time in between spawning

	vehicles[3].setTexture(&bikeTexture);
	vehicles[3].setSize(sf::Vector2f(93 * 2, 60 * 2));
	vehicles[3].setPosition(0 - vehicles[3].getSize().x, 200);
	vehicles[3].scale(-1, 1); // Flips the sprite
	vehicles[3].setDirection('r'); // Sets direction to right
	vehicles[3].setVelocity(1500, 0);
	vehicles[3].setThreshold(4.f); // Time in between spawning
}

// Sets up all truck objects
void VehicleManager::setUpTrucks()
{
	vehicles[4].setTexture(&truckTexture);
	vehicles[4].setSize(sf::Vector2f(257 * 2, 104 * 2));
	vehicles[4].setPosition(6000, 710);
	vehicles[4].setDirection('l'); // Sets direction to left
	vehicles[4].setVelocity(-600, 0);
	vehicles[4].setThreshold(10.f); // Time in between spawning

	vehicles[5].setTexture(&truckTexture);
	vehicles[5].setSize(sf::Vector2f(257 * 2, 104 * 2));
	vehicles[5].setPosition(6000, 284);
	vehicles[5].setDirection('l'); // Sets direction to left
	vehicles[5].setVelocity(-600, 0);
	vehicles[5].setThreshold(7.f); // Time in between spawning
}

// Sets up all police objects
void VehicleManager::setUpPolice()
{
	vehicles[6].setTexture(&policeTexture);
	vehicles[6].setSize(sf::Vector2f(163 * 2, 60 * 2));
	vehicles[6].setPosition(6000, 340);
	vehicles[6].setDirection('l'); // Sets direction to left
	vehicles[6].setVelocity(-900, 0);
	vehicles[6].setThreshold(5.f); // Time in between spawning

	vehicles[7].setTexture(&policeTexture);
	vehicles[7].setSize(sf::Vector2f(163 * 2, 60 * 2));
	vehicles[7].setPosition(6000, 20);
	vehicles[7].setDirection('l'); // Sets direction to left
	vehicles[7].setVelocity(-1000, 0);
	vehicles[7].setThreshold(3.f); // Time in between spawning
}