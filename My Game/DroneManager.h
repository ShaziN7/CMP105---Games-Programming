#pragma once

#include "Framework/Collision.h"
#include "Drone.h"
#include "Player.h"


class DroneManager
{

public:

	DroneManager();
	~DroneManager();

	void spawn(); // Spawns drones
	void update(float dt, Player &player, AudioManager &audioManager); // Updates drones
	void render(sf::RenderWindow* window, sf::View* view); // Renders drones to screen
	void resetDrones(); // Resets the drones for new game
	std::vector<Drone>* getDroneVector(); // Returns the drone vector


private:

	// ---------- Private Functions ---------- \\

	void collision(float dt, Player &player, AudioManager &audioManager); // Checks for collisions between drones and player


	// ---------- Variables ---------- \\

	sf::Texture droneTexture; // The drone texture
	std::vector<Drone> drones; // Vector holding all the drone objects
};