#pragma once

#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Controller.h"


class Controls
{

public:

	Controls(sf::RenderWindow* hwnd, Input* in);
	~Controls();

	void handleInput(AudioManager &audioManager, Controller &controller); // Handles input for controls class
	void update(float dt); // Updates controls class
	void render(); // Renders everything to the window
	State getState(); // Returns the game state


private:

	// ---------- Private Functions ---------- \\

	void loadTextures(); // Loads controls object textures
	void setUpBackground(); // Sets up background objects
	void setUpControlsBox(); // Sets up controls box objects


	// ---------- Variables ---------- \\

	// Default functions for rendering to the screen.
	void beginDraw(); // Clears the screen for rendering
	void endDraw(); // Displays everything from the buffer


	// Default variables for controls class.
	sf::RenderWindow* window; // Pointer to the window
	Input* input; // Pointer to the input

	// Controls textures
	sf::Texture backgroundTexture;
	sf::Texture cityTexture;
	sf::Texture controlsBoxTexture;

	sf::Font pixels; // Font for text in controls box

	// Background objects
	GameObject background;
	GameObject city;
	GameObject city2;

	GameObject controlsBox; // Controls box object

	// Controls text
	sf::Text pressEnterText;
	sf::Text controlsText;

	// Game state
	State gameState;

	// View for controls state
	sf::View controlsView;

	float animTimer; // Timer used in text animating
	bool isTransparent; // If text is transparent
};