#pragma once

#include "Bullet.h"
#include "Player.h"


class BulletManager
{

public:

	BulletManager();
	~BulletManager();

	void spawn(float dt, AudioManager &audioManager, Player &player); // Spawns player bullets
	void update(float dt, Player &player, std::vector<Turret>* turret, std::vector<Drone>* drone, AudioManager &audioManager, GameDifficulty &gameDifficulty);
	void render(sf::RenderWindow* window, sf::View* view); // Renders bullets to screen


private:

	// ---------- Private Functions ---------- \\

	void spawn(float dt, AudioManager &audioManager, Player &player, Turret &turret, GameDifficulty &gameDifficulty); // Spawns enemy bullets
	void updatePlayerSpawn(Player &player); // Updates player spawn
	void updateEnemySpawn(float dt, Player &player, std::vector<Turret>* turret, AudioManager &audioManager, GameDifficulty &gameDifficulty); // Updates enemy spawn
	void collision(float dt, std::vector<Turret>* turrets); // Checks for collisions between bullets and turrets
	void collision(float dt, std::vector<Drone>* drones); // Checks for collisions between bullets and drones
	void collision(float dt, Player &player, GameDifficulty &gameDifficulty, AudioManager &audioManager); // Checks for collisions between bullets and the player
	void deathCheck(Player &player); // Checks if bullets should be dead


	// ---------- Variables ---------- \\

	sf::Texture bulletTexture; // The bullet texture
	std::vector<Bullet> bullets; // Vector holding all bullets
	sf::Vector2f playerSpawnPoint; // Where player bullets should spawn
	sf::Vector2f enemySpawnPoint; // Where enemy bullets should spawn
	float playerBulletTimer; // Timer to space out the player's bullets
	float enemyBulletTimer; // Timer to space out the enemy's bullets
};