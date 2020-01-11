#pragma once

#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Controller.h"


class Title
{

public:

	Title(sf::RenderWindow* hwnd, Input* in);
	~Title();

	void handleInput(Controller &controller, AudioManager &audioManager); // Handles input for pause class
	void update(float dt, AudioManager &audioManager); // Updates pause class
	void render(); // Renders everything to the window
	State getState(); // Returns the game state


private:

	// ---------- Private Functions ---------- \\

	void setUpBackground(); // Sets up background objects
	void setUpTitle(); // Sets up title objects


	// ---------- Variables ---------- \\

	// Default functions for rendering to the screen.
	void beginDraw(); // Clears the screen for rendering
	void endDraw(); // Displays everything from the buffer

	// Default variables for title class.
	sf::RenderWindow* window; // Pointer to the window
	Input* input; // Pointer to the input

	// Title textures
	sf::Texture backgroundTexture;
	sf::Texture cityTexture;

	// Title fonts
	sf::Font anurati;
	sf::Font pixels;

	// Background objects
	GameObject background;
	GameObject city;
	GameObject city2;

	// All text
	sf::Text titleText;
	sf::Text titleShadowMiddleText;
	sf::Text titleShadowBackText;
	sf::Text pressEnterText;

	State gameState; // Game state
	sf::View titleView; // View for title state
	float animTimer; // Timer used in text animating
	bool isTransparent; // If text is transparent
};