#include "TurretManager.h"


TurretManager::TurretManager()
{
	// Loads turret texture
	turretTexture.loadFromFile("gfx/misc/EnemySheet.png");

	// Initialises a vector to hold the turret objects
	for (int i = 0; i < 5; i++)
	{
		turrets.push_back(Turret());
		turrets[i].setAlive(false);
		turrets[i].setTexture(&turretTexture);
		turrets[i].setCollider(true);
		turrets[i].setSize(sf::Vector2f(25 * 2, 23 * 2));
		turrets[i].setCollisionBox(sf::FloatRect(0, 0, 25 * 2, 23 * 2));
		turrets[i].setColliderType(ColliderType::ENEMY);
	}

	// Manually sets spawn points for each turret
	turrets[0].setSpawnPoint(sf::Vector2f(110, 794));
	turrets[1].setSpawnPoint(sf::Vector2f(1050, 434));
	turrets[2].setSpawnPoint(sf::Vector2f(1910, 712));
	turrets[3].setSpawnPoint(sf::Vector2f(3640, 792));
	turrets[4].setSpawnPoint(sf::Vector2f(5128, 552));
}

TurretManager::~TurretManager()
{
}


// Spawns turrets
void TurretManager::spawn()
{
	for (int i = 0; i < turrets.size(); i++)
	{
		// If turrets are not alive
		if (!turrets[i].isAlive())
		{
			turrets[i].setAlive(true); // Spawns turret
			turrets[i].setPosition(turrets[i].getSpawnPoint()); // Spawns at turret's spawn point
		}
	}
}

void TurretManager::update(float dt, Player &player, AudioManager &audioManager)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		if (turrets[i].isAlive())
		{
			turrets[i].update(dt, audioManager); // Moves and animates alive turrets
		}
	}

	collision(dt, player, audioManager); // Checks for collisions
}

// Checks for collisions between the turrets and player
void TurretManager::collision(float dt, Player &player, AudioManager &audioManager)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		// If turret is alive
		if (turrets[i].isAlive())
		{
			// If turret is a collider
			if (turrets[i].isCollider())
			{
				// If player is alive
				if (player.isAlive())
				{
					// Checks if turret and player are colliding
					if (Collision::checkBoundingBox(&turrets[i], &player))
					{
						player.collisionResponse(&turrets[i], dt, audioManager); // If colliding, runs player collision response
					}
				}
			}
		}
	}
}

// Renders turrets to screen
void TurretManager::render(sf::RenderWindow* window, sf::View* view)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		// If turret is alive
		if (turrets[i].isAlive())
		{
			// If turret is visible on screen
			if (turrets[i].getVisible(*view))
			{
				window->draw(turrets[i]); // Render turret to screen
			}
		}
	}
}

// Resets the turrets for new game
void TurretManager::resetTurrets()
{
	for (int i = 0; i < 5; i++)
	{
		turrets[i].resetAnimation();
		turrets[i].setAlive(true);
		turrets[i].setCollider(true);
	}
}

std::vector<Turret>* TurretManager::getTurretVector()
{
	return &turrets; // Returns the turret vector
}