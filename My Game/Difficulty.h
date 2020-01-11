#pragma once

#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Controller.h"


class Difficulty
{

public:

	Difficulty(sf::RenderWindow* hwnd, Input* in);
	~Difficulty();

	void handleInput(Controller &controller, AudioManager &audioManager); // Handles input for difficulty class
	void update(float dt); // Updates credits class
	void render(); // Renders everything to the window
	GameDifficulty getGameDifficulty();
	State getState(); // Returns the game state
	

private:

	// ---------- Private Functions ---------- \\

	void setUpBackground(); // Sets up background objects
	void setUpTitle(); // Sets up title objects
	void setUpDifficultyText(); // Sets up difficulty text


	// ---------- Variables ---------- \\

	// Default functions for rendering to the screen.
	void beginDraw(); // Clears the screen for rendering
	void endDraw(); // Displays everything from the buffer
	

	// Default variables for difficulty class.
	sf::RenderWindow* window; // Pointer to the window
	Input* input; // Pointer to the input

	// Difficulty textures
	sf::Texture backgroundTexture;
	sf::Texture cityTexture;

	// Difficulty fonts	
	sf::Font anurati; // Font for title
	sf::Font pixels; // Font for difficulty text
	
	// Background objects
	GameObject background;
	GameObject city;
	GameObject city2;

	// Title text
	sf::Text titleText;
	sf::Text titleShadowMiddleText;
	sf::Text titleShadowBackText;

	// Difficulty text
	sf::Text hardText;
	sf::Text mediumText;
	sf::Text easyText;

	GameDifficulty gameDifficulty; // Game difficulty
	State gameState; // Game state
	sf::View difficultyView; // View for difficulty state
	float animTimer; // Timer used in text animating
	bool isTransparent; // If text is transparent
};