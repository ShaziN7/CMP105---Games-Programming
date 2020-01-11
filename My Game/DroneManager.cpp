#include "DroneManager.h"


DroneManager::DroneManager()
{
	// Loads drone texture
	droneTexture.loadFromFile("gfx/misc/EnemySheet.png");

	// Initialises a vector to hold the drone objects
	for (int i = 0; i < 4; i++)
	{
		drones.push_back(Drone());
		drones[i].setAlive(false);
		drones[i].setTexture(&droneTexture);
		drones[i].setCollider(true);
		drones[i].setSize(sf::Vector2f(55 * 2, 52 * 2));
		drones[i].setCollisionBox(sf::FloatRect(14, 0, 76, 52 * 2));
		drones[i].setColliderType(ColliderType::ENEMY);
	}

	// Manually sets values for each drone

	drones[0].setSpawnPoint(sf::Vector2f(450, 310));
	drones[0].setLeftTarget(450);
	drones[0].setRightTarget(880);
	drones[0].setHorizDirection('r');

	drones[1].setSpawnPoint(sf::Vector2f(1900, 220));
	drones[1].setLeftTarget(1570);
	drones[1].setRightTarget(1900);
	drones[1].setHorizDirection('l');

	drones[2].setSpawnPoint(sf::Vector2f(1900, 420));
	drones[2].setLeftTarget(1570);
	drones[2].setRightTarget(1900);
	drones[2].setHorizDirection('l');

	drones[3].setSpawnPoint(sf::Vector2f(4040, 200));
	drones[3].setLeftTarget(4040);
	drones[3].setRightTarget(4300);
	drones[3].setHorizDirection('r');
}

DroneManager::~DroneManager()
{
}


// Spawns drones
void DroneManager::spawn()
{
	for (int i = 0; i < drones.size(); i++)
	{
		// If drones are not alive
		if (!drones[i].isAlive())
		{
			drones[i].setAlive(true); // Spawn drone
			drones[i].setPosition(drones[i].getSpawnPoint()); // Spawn at drone's spawn point
		}
	}
}

void DroneManager::update(float dt, Player &player, AudioManager &audioManager)
{
	for (int i = 0; i < drones.size(); i++)
	{
		if (drones[i].isAlive())
		{
			drones[i].update(dt, audioManager); // Moves and animates alive drones
		}
	}

	collision(dt, player, audioManager); // Checks for collisions
}

// Checks for collisions between the drones and player
void DroneManager::collision(float dt, Player &player, AudioManager &audioManager)
{
	for (int i = 0; i < drones.size(); i++)
	{
		// If drone is alive
		if (drones[i].isAlive())
		{
			// If drone is a collider
			if (drones[i].isCollider())
			{
				// If player is alive
				if (player.isAlive())
				{
					// Checks if drone and player are colliding
					if (Collision::checkBoundingBox(&drones[i], &player))
					{
						player.collisionResponse(&drones[i], dt, audioManager); // If colliding, runs player collision response
					}
				}
			}

		}
	}
}

// Renders drones to screen
void DroneManager::render(sf::RenderWindow* window, sf::View* view)
{
	for (int i = 0; i < drones.size(); i++)
	{
		// If drone is alive
		if (drones[i].isAlive())
		{
			// If drone is visible on screen
			if (drones[i].getVisible(*view))
			{
				window->draw(drones[i]); // Render drone to screen
			}
		}
	}	
}

// Resets the drones for new game
void DroneManager::resetDrones()
{
	for (int i = 0; i < drones.size(); i++)
	{
		drones[i].resetAnimation();
		drones[i].setAlive(false);
		drones[i].setAnimTimer(0);
		drones[i].setDeathTimer(0);
		drones[i].setIsHit(false);
		drones[i].setCollider(true);
		drones[i].setMoving(true);
	}

	// Manually sets values for each drone

	drones[0].setHorizDirection('r');
	drones[1].setHorizDirection('l');
	drones[2].setHorizDirection('l');
	drones[3].setHorizDirection('r');
}

std::vector<Drone>* DroneManager::getDroneVector()
{
	return &drones; // Returns the drone vector
}