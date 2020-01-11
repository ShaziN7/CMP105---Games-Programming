#pragma once

#include "Framework/Collision.h"
#include "Coin.h"
#include "Player.h"


class CoinManager
{

public:

	CoinManager();
	~CoinManager();

	void spawn(); // Spawns coins
	void update(float dt, Player &player, AudioManager &audioManager); // Updates coins
	void render(sf::RenderWindow* window, sf::View* view); // Renders coins
	

private:

	// ---------- Private Functions ---------- \\

	void collision(float dt, Player &player, AudioManager &audioManager); // Checks for collisions between coins and the player


	// ---------- Variables ---------- \\

	sf::Texture coinTexture; // The coin texture
	std::vector<Coin> coins; // A vector containing all the coin objects
};