#pragma once

#include "Framework/Collision.h"
#include "Turret.h"
#include "Player.h"


class TurretManager
{

public:

	TurretManager();
	~TurretManager();

	void spawn(); // Spawns turrets
	void update(float dt, Player &player, AudioManager &audioManager); // Updates drones
	void render(sf::RenderWindow* window, sf::View* view); // Renders turrets to screen
	void resetTurrets(); // Resets the turrets for new game
	std::vector<Turret>* getTurretVector(); // Returns the turret vector
	

private:

	// ---------- Private Functions ---------- \\

	void collision(float dt, Player &player, AudioManager &audioManager); // Checks for collisions between turrets and player

	// ---------- Variables ---------- \\

	sf::Texture turretTexture; // The turret texture
	std::vector<Turret> turrets; // Vector holding all the turret objects
};