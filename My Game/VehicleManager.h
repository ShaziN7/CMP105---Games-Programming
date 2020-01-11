#pragma once

#include "Vehicle.h"


class VehicleManager
{

public:

	VehicleManager();
	~VehicleManager();

	void update(float dt); // Updates vehicles
	void render(sf::RenderWindow* window, sf::View* view); // Renders vehicles to window
	


private:

	// ---------- Private Functions ---------- \\

	void loadTextures(); // Loads vehicle textures
	void setUpCars();
	void setUpBikes();
	void setUpTrucks();
	void setUpPolice();


	// ---------- Variables ---------- \\

	// Vehicle textures
	sf::Texture carTexture;
	sf::Texture bikeTexture;
	sf::Texture truckTexture;
	sf::Texture policeTexture;

	std::vector<Vehicle> vehicles; // Vector containing all of the vehicle objects
};