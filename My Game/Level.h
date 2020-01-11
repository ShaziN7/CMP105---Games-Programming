#pragma once

#include "Framework/GameState.h"
#include "Player.h"
#include "BulletManager.h"
#include "TurretManager.h"
#include "DroneManager.h"
#include "TileManager.h"
#include "VehicleManager.h"
#include "PropManager.h"
#include "CoinManager.h"
#include "BackgroundManager.h"



class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt, AudioManager &audioManager, Controller &controller); // Handles input for level class
	void update(float dt, AudioManager &audioManager, Controller &controller, GameDifficulty &difficulty); // Updates level class
	void render(); // Renders everything to the window
	void resetLevel(); // Resets level for new game
	State getState(); // Returns the game state


private:

	// ---------- Private Functions ---------- \\

	void setUpPlayer(); // Sets up the player object
	void setUpScoreBox(); // Sets up the score box
	void updateManagers(float dt, AudioManager &audioManager, Controller &controller); // Updates the object managers
	void updateView(float dt); // Updates view depending on player's position


	// ---------- Variables ---------- \\

	// Default functions for rendering to the screen.
	void beginDraw(); // Clears the screen for rendering
	void endDraw(); // Displays everything from the buffer

	// Default variables for level class.
	sf::RenderWindow* window; // Pointer to the window
	Input* input; // Pointer to the input

	// Level textures
	sf::Texture playerTexture; // Texture for player character
	sf::Texture scoreBoxTexture; // Texture for score box

	// For score
	GameObject scoreBox;
	sf::Font pixels; // Font for score text
	sf::Text scoreText; // Text for displaying score

	Player player; // Player object

	// Manager objects
	BulletManager bulletManager;
	TurretManager turretManager;
	DroneManager droneManager;
	TileManager tileManager;
	VehicleManager vehicleManager;
	PropManager propManager;
	CoinManager coinManager;
	BackgroundManager backgroundManager;

	// Vector pointers	
	std::vector<Turret>* turretPointer;
	std::vector<Drone>* dronePointer;
	
	GameDifficulty gameDifficulty; // What difficulty game is playing on
	State gameState; // Game state
	sf::View view; // View for level state
	bool quit; // If game should quit to menu
};