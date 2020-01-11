#include "BulletManager.h"


BulletManager::BulletManager()
{
	// Loads bullet texture
	bulletTexture.loadFromFile("gfx/misc/AllShotSheet.png");

	// Initialises a vector to hold the bullet objects
	for (int i = 0; i < 20; i++)
	{
		bullets.push_back(Bullet());
		bullets[i].setAlive(false);
		bullets[i].setTexture(&bulletTexture);
		bullets[i].setSize(sf::Vector2f(30, 22));
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, 30, 22));

		if (i < 10)
		{
			bullets[i].setBulletType(BulletType::PLAYER); // Sets first 10 bullets to be player bullets
		}

		else
		{
			bullets[i].setBulletType(BulletType::ENEMY); // Sets the rest of the bullets to be enemy bullets
			bullets[i].setFillColor(sf::Color::Green); // Makes enemy bullets green to stand out from player's
		}
	}

	playerBulletTimer = 0.5; // Timer to space out player bullets
	enemyBulletTimer = 0; // Timer to space out enemy bullets
}

BulletManager::~BulletManager()
{
}

// Spawns player bullets
void BulletManager::spawn(float dt, AudioManager &audioManager, Player &player)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If the bullets are player bullets
		if (bullets[i].getBulletType() == BulletType::PLAYER)
		{
			// If bullets are not alive
			if (!bullets[i].isAlive())
			{
				playerBulletTimer += dt; // Start bullet timer

				if (playerBulletTimer >= 0.5 && player.getPlayerState() != PlayerState::CLIMBING) // Don't allow player to shoot while climbing
				{
					bullets[i].setAlive(true); // Spawn bullet
					bullets[i].setPosition(playerSpawnPoint); // Spawn at the player
					playerBulletTimer = 0; // Reset timer for next bullet
					audioManager.playSoundbyName("shoot"); // Play shoot sound

					if (player.getPlayerDirection() == PlayerDirection::LEFT)
					{
						bullets[i].setVelocity(-500, 0); // If player is facing left, shoot bullet left
					}

					else
					{
						bullets[i].setVelocity(500, 0); // If player is facing right, shoot bullet right
					}
				}

				return;
			}
		}
	}
}

// Spawns enemy bullets
void BulletManager::spawn(float dt, AudioManager &audioManager, Player &player, Turret &turret, GameDifficulty &gameDifficulty)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If the bullets are enemy bullets
		if (bullets[i].getBulletType() == BulletType::ENEMY)
		{
			// If bullets are not alive
			if (!bullets[i].isAlive())
			{
				enemyBulletTimer += dt; // Start bullet timer

				// Checks if difficulty is hard or medium, timers differ. No enemy bullets on easy
				if (gameDifficulty == GameDifficulty::HARD && enemyBulletTimer >= 1.2f || gameDifficulty == GameDifficulty::MEDIUM && enemyBulletTimer >= 3.f)
				{
					bullets[i].setAlive(true); // Spawn bullet
					bullets[i].setPosition(enemySpawnPoint); // Spawn at the enemy
					enemyBulletTimer = 0; // Reset timer for next bullet
					audioManager.playSoundbyName("enemyshoot"); // Play enemy shoot sound

					if (turret.getPosition().x < player.getPosition().x)
					{
						bullets[i].setVelocity(500, 0); // If turret is to left of player, shoot right
					}

					else if (turret.getPosition().x > player.getPosition().x)
					{
						bullets[i].setVelocity(-500, 0); // If turret is to right of player, shoot left
					}
				}

				return;
			}
		}
	}
}

void BulletManager::update(float dt, Player &player, std::vector<Turret>* turret, std::vector<Drone>* drone, AudioManager &audioManager, GameDifficulty &gameDifficulty)
{
	updatePlayerSpawn(player); // Updates where player bullets should spawn
	updateEnemySpawn(dt, player, turret, audioManager, gameDifficulty); // Updates where enemy bullets should spawn

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].update(dt); // Moves and animates alive bullets
		}
	}

	collision(dt, turret); // Checks for collisions between the bullets and turrets
	collision(dt, drone); // Checks for collisions between the bullets and drones
	collision(dt, player, gameDifficulty, audioManager); // Checks for collisions between the bullets and the player

	deathCheck(player); // Checks if bullets should be dead
}

void BulletManager::updatePlayerSpawn(Player &player)
{
	// If player is facing left, set spawns to the left
	if (player.getPlayerDirection() == PlayerDirection::LEFT)
	{
		playerSpawnPoint = sf::Vector2f(player.getPosition().x, player.getPosition().y + 48);

		if (player.getPlayerState() == PlayerState::RUNSHOOTING)
		{
			playerSpawnPoint.x = playerSpawnPoint.x - 70;
		}

	}

	// If player is facing right, set spawns to the right
	else
	{
		playerSpawnPoint = sf::Vector2f(player.getPosition().x + player.getSize().x - 40, player.getPosition().y + 48);

		if (player.getPlayerState() == PlayerState::RUNSHOOTING)
		{
			playerSpawnPoint.x = playerSpawnPoint.x + 70;
		}
	}

	// If player is crouching, set spawn further down
	if (player.getPlayerState() == PlayerState::CROUCHING)
	{
		playerSpawnPoint.y += 34;
	}
}

void BulletManager::updateEnemySpawn(float dt, Player &player, std::vector<Turret>* turret, AudioManager &audioManager, GameDifficulty &gameDifficulty)
{
	// Only runs if difficulty is hard or medium
	if (gameDifficulty == GameDifficulty::HARD || gameDifficulty == GameDifficulty::MEDIUM)
	{
		for (int i = 0; i < turret->size(); i++)
		{
			// If turret is alive
			if ((*turret)[i].isAlive())
			{
				// Checks if player is in a certain radius to the turret
				if ((abs((*turret)[i].getPosition().x - player.getPosition().x) <= 500)
					&& (player.getPosition().y + player.getSize().y >= (*turret)[i].getPosition().y && player.getPosition().y <= (*turret)[i].getPosition().y + (*turret)[i].getSize().y))
				{
					(*turret)[i].shouldAnimate(false); // Stop animating turret so it stops and shoots
					enemySpawnPoint = (*turret)[i].getPosition(); // Sets spawn point to that turret
					spawn(dt, audioManager, player, (*turret)[i], gameDifficulty); // Spawns enemy bullets
				}

				else
				{
					(*turret)[i].shouldAnimate(true); // Makes sure turret is animating
				}

			}
		}
	}
}

// Checks for collisions between bullets and turrets
void BulletManager::collision(float dt, std::vector<Turret>* turrets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If bullet is alive
		if (bullets[i].isAlive())
		{
			// If bullet is a player bullet
			if (bullets[i].getBulletType() == BulletType::PLAYER)
			{
				for (int j = 0; j < turrets->size(); j++)
				{
					// If turret is alive
					if ((*turrets)[j].isAlive())
					{
						// Checks if bullet and turret are colliding
						if (Collision::checkBoundingBox(&bullets[i], &turrets->at(j)))
						{
							bullets[i].collisionResponse(&(*turrets)[j]); // If colliding, runs bullet collision response
							(*turrets)[j].collisionResponse(NULL); // If colliding, runs turret collision response. NULL because this is the only collision response.
						}
					}
				}
			}
		}
	}
}

// Checks for collisions between bullets and drones
void BulletManager::collision(float dt, std::vector<Drone>* drones)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If bullet is alive
		if (bullets[i].isAlive())
		{
			if (bullets[i].getBulletType() == BulletType::PLAYER)
			{
				for (int j = 0; j < drones->size(); j++)
				{
					// If drone is alive
					if ((*drones)[j].isAlive())
					{
						// Checks if bullet and drone are colliding
						if (Collision::checkBoundingBox(&bullets[i], &drones->at(j)))
						{
							bullets[i].collisionResponse(&(*drones)[j]); // If colliding, runs bullet collision response
							(*drones)[j].collisionResponse(NULL); // If colliding, runs drone collision response
						}
					}
				}
			}
		}
	}
}

// Checks for collisions between bullets and the player
void BulletManager::collision(float dt, Player &player, GameDifficulty &gameDifficulty, AudioManager &audioManager)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If bullet is alive
		if (bullets[i].isAlive())
		{
			// If bullet is an enemy bullet
			if (bullets[i].getBulletType() == BulletType::ENEMY)
			{
				// If difficulty is hard or medium
				if (gameDifficulty == GameDifficulty::HARD || gameDifficulty == GameDifficulty::MEDIUM)
				{
					// Checks if bullet and player are colliding
					if (Collision::checkBoundingBox(&bullets[i], &player))
					{
						bullets[i].collisionResponse(&player); // If colliding, runs bullet collision response
						player.collisionResponse(&bullets[i], dt, audioManager); // If colliding, runs player collision response
					}
				}
			}
		}
	}
}


void BulletManager::deathCheck(Player &player)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If bullet is alive
		if (bullets[i].isAlive())
		{
			// If bullet gets so far away from the player or goes out of screen, it dies
			if (bullets[i].getPosition().x >= player.getPosition().x + 500 || bullets[i].getPosition().x <= player.getPosition().x - 500 || bullets[i].getPosition().x <= 0)
			{
				bullets[i].setAlive(false); // Kill bullet
			}
		}
	}
}

void BulletManager::render(sf::RenderWindow* window, sf::View* view)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If bullet is alive
		if (bullets[i].isAlive())
		{
			// If bullet is visible on screen
			if (bullets[i].getVisible(*view))
			{
				window->draw(bullets[i]); // Render bullet to screen
			}
		}
	}
}