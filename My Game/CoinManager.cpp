#include "CoinManager.h"


CoinManager::CoinManager()
{
	// Loads coin texture
	coinTexture.loadFromFile("gfx/misc/CoinSheet.png");

	// Initialises a vector to hold the coin objects
	for (int i = 0; i < 10; i++)
	{
		coins.push_back(Coin());
		coins[i].setAlive(false);
		coins[i].setTexture(&coinTexture);
		coins[i].setSize(sf::Vector2f(149 / 3, 149 / 3));
		coins[i].setCollisionBox(sf::FloatRect(0, 0, 149 / 3, 149 / 3));
		/*coins[i].setColliderType(ColliderType::COIN);*/
	}

	// Manually sets the spawn point of each coin in the level
	coins[0].setSpawnPoint(sf::Vector2f(230, 960));
	coins[1].setSpawnPoint(sf::Vector2f(600, 260));
	coins[2].setSpawnPoint(sf::Vector2f(1700, 600));
	coins[3].setSpawnPoint(sf::Vector2f(3300, 70));
	coins[4].setSpawnPoint(sf::Vector2f(3640, 700));
	coins[5].setSpawnPoint(sf::Vector2f(4154, 200));
	coins[6].setSpawnPoint(sf::Vector2f(5128, 540));
	coins[7].setSpawnPoint(sf::Vector2f(5450, 400));
	coins[8].setSpawnPoint(sf::Vector2f(1500, 220));
	coins[9].setSpawnPoint(sf::Vector2f(2700, 160));
}

CoinManager::~CoinManager()
{
}


// Spawns coins
void CoinManager::spawn()
{
	for (int i = 0; i < coins.size(); i++)
	{
		// If coins are not alive
		if (!coins[i].isAlive())
		{
			coins[i].setAlive(true); // Spawn coin
			coins[i].setPosition(coins[i].getSpawnPoint()); // Spawn at spawn point
		}
	}
}

void CoinManager::update(float dt, Player &player, AudioManager &audioManager)
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins[i].isAlive())
		{
			coins[i].update(dt); // Animates alive coins
		}
	}

	collision(dt, player, audioManager); // Checks for collisions between coins and the player
}

void CoinManager::collision(float dt, Player &player, AudioManager &audioManager)
{
	for (int i = 0; i < coins.size(); i++)
	{
		// If coin is alive
		if (coins[i].isAlive())
		{
			// If player is alive
			if (player.isAlive())
			{
				// Checks if bullet and player are colliding
				if (Collision::checkBoundingBox(&coins[i], &player))
				{
					coins[i].collisionResponse(&player, audioManager); // If colliding, runs coin collision response
					player.collisionResponse(&coins[i]); // If colliding, runs player collision response
				}
			}
		}
	}
}

void CoinManager::render(sf::RenderWindow* window, sf::View* view)
{
	for (int i = 0; i < coins.size(); i++)
	{
		// If coin is alive
		if (coins[i].isAlive())
		{
			// If coin is visible on screen
			if (coins[i].getVisible(*view))
			{
				window->draw(coins[i]); // Render coin to screen
			}
		}
	}
}