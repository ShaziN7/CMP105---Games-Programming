#pragma once

#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Controller.h"


class Credits
{

public:

	Credits(sf::RenderWindow * hwnd, Input * in);
	~Credits();

	void handleInput(Controller &controller, AudioManager &audioManager); // Handles input for credits class
	void update(float dt, AudioManager &audioManager); // Updates credits class
	void render(); // Renders everything to the window
	State getState(); // Returns the game state


private:

	// ---------- Private Functions ---------- \\

	void loadTextures(); // Loads credits object textures
	void setUpBackground(); // Sets up background objects
	void setUpTitle(); // Sets up title objects
	void setUpCreditsBox(); // Sets up credits box objects


	// ---------- Variables ---------- \\

	// Default functions for rendering to the screen.
	void beginDraw(); // Clears the screen for rendering
	void endDraw(); // Displays everything from the buffer


	// Default variables for credits class.
	sf::RenderWindow* window; // Pointer to the window
	Input* input; // Pointer to the input

	// Credits textures
	sf::Texture backgroundTexture;
	sf::Texture cityTexture;
	sf::Texture creditsBoxTexture;

	// Credits fonts
	sf::Font anurati; // Font for title
	sf::Font pixels; // Font for credits text

	// Background objects
	GameObject background;
	GameObject city;
	GameObject city2;

	GameObject creditsBox; // Credits box object

	// All text
	sf::Text titleText;
	sf::Text titleShadowMiddleText;
	sf::Text titleShadowBackText;
	sf::Text pressEnterText;
	sf::Text creditsText;

	State gameState; // Game state
	sf::View creditsView; // View for credits state
	float animTimer; // Timer used in text animating
	bool isTransparent; // If text is transparent
};