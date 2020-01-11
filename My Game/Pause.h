#pragma once

#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Controller.h"


class Pause
{

public:

	Pause(sf::RenderWindow* hwnd, Input* in);
	~Pause();

	void handleInput(Controller &controller, AudioManager &audioManager); // Handles input for pause class
	void update(float dt, AudioManager &audioManager); // Updates pause class
	void render(); // Renders everything to the window
	State getState(); // Returns the game state


private:

	// ---------- Private Functions ---------- \\

	void loadTextures(); // Loads pause object textures
	void setUpBackground(); // Sets up background objects
	void setUpTitle(); // Sets up title objects
	void setUpControlsBox(); // Sets up credits box objects


	// ---------- Variables ---------- \\

	// Default functions for rendering to the screen.
	void beginDraw(); // Clears the screen for rendering
	void endDraw(); // Displays everything from the buffer

	// Default variables for pause class.
	sf::RenderWindow* window; // Pointer to the window
	Input* input; // Pointer to the input

	// Pause textures
	sf::Texture backgroundTexture;
	sf::Texture cityTexture;
	sf::Texture controlsBoxTexture;

	// Pause fonts
	sf::Font anurati;
	sf::Font pixels;

	// Background objects
	GameObject background;
	GameObject city;
	GameObject city2;

	GameObject controlsBox; // Controls box object

	// All text
	sf::Text titleText;
	sf::Text titleShadowMiddleText;
	sf::Text titleShadowBackText;
	sf::Text pauseText;
	sf::Text controlsText;

	State gameState; // Game state
	sf::View pauseView; // View for pause state
	float animTimer; // Timer used in text animating
	bool isTransparent; // If text is transparent
};