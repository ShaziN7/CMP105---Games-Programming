#pragma once

#include "Tile.h"
#include "Coin.h"
#include "Controller.h"


class Player: public GameObject
{

public:

	Player();
	~Player();

	void handleInput(float dt, Controller &controller, AudioManager &audioManager); // Handles all player input
	void update(float dt, AudioManager &audioManager); // Updates player
	void collisionResponse(Tile* collider, float dt, Tile* aboveTile, Tile* belowTile, Controller &controller, AudioManager &audioManager); // If there is a collision between player and tiles
	void collisionResponse(Coin* collider); // If there is a collision between player and coins
	void collisionResponse(GameObject* collider, float dt, AudioManager &audioManager); // If there is a collision between player and enemies or bullets
	void resetPlayer(bool quit); // Resets the player for a new game
	PlayerState getPlayerState(); // Returns the player's state
	PlayerDirection getPlayerDirection(); // Returns the player's direction
	int getScore(); // Returns the player's score
	int getDeaths(); // Returns the number of deaths
	
	
private:

	// ---------- Private Functions ---------- \\

	void setUpAnimations(); // Sets up the player animations
	void animations(); // Animates the correct animations
	void spawnAnimation(); // Plays the spawn animation
	void directions(); // Deals with what way player is facing and moving
	bool isAnyKeyPressed(); // Checks if any key is being pressed


	// ---------- Variables ---------- \\

	// The player animations
	Animation run;
	Animation idle;
	Animation crouch;
	Animation climb;
	Animation shoot;
	Animation runShoot;
	Animation jump;
	Animation hurt;
	Animation* currentAnimation;

	PlayerState playerState; // State changes depending on what player is doing
	PlayerDirection playerDirection; // Which direction to move and face

	float animTimer; // How long to wait before playing animation
	const float scale = 200.f; // So everything happens at the same scale
	const float gravity = 8.f * scale; // Constant gravity pull
	int score; // Player's score
	int deaths; // Player's deaths
	bool ladderCollision; // If player is colliding with a ladder
	bool isColliding; // If player is colliding
	bool applyGravity; // Whether to apply gravity
	bool hasSpawned; // If player has spawned already
	float respawnTimer; // Time between player respawning to give time for sound to play
};