#include "Coin.h"


Coin::Coin()
{
	// Sets up Spin animation

	spin.addFrame(sf::IntRect(0, 0, 149, 149));
	spin.addFrame(sf::IntRect(149, 0, 149, 149));
	spin.addFrame(sf::IntRect(298, 0, 149, 149));
	spin.addFrame(sf::IntRect(447, 0, 149, 149));
	spin.addFrame(sf::IntRect(596, 0, 149, 149));
	spin.addFrame(sf::IntRect(745, 0, 149, 149));
	spin.addFrame(sf::IntRect(894, 0, 149, 149));
	spin.addFrame(sf::IntRect(1043, 0, 149, 149));
	spin.addFrame(sf::IntRect(1192, 0, 149, 149));
	spin.setFrameSpeed(0.1f);
}

Coin::~Coin()
{
}


void Coin::update(float dt)
{
	// Animates Spin animation

	spin.animate(dt);
	setTextureRect(spin.getCurrentFrame());
}

void Coin::collisionResponse(GameObject* collider, AudioManager &audioManager)
{
	// If player has collided with coin, set coin to be dead

	audioManager.playSoundbyName("coin"); // Play coin sound
	setAlive(false); 
}

void Coin::setSpawnPoint(sf::Vector2f sp)
{
	spawnPoint = sp;
}

sf::Vector2f Coin::getSpawnPoint()
{
	return spawnPoint;
}