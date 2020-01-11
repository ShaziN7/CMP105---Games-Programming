#include "Controls.h"


Controls::Controls(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	loadTextures(); // Loads textures
	pixels.loadFromFile("font/04B03.ttf"); // Loads font

	setUpBackground(); // Sets up background objects
	setUpControlsBox(); // Sets up controls box objects

	// Sets up text to press enter
	pressEnterText.setFont(pixels);
	pressEnterText.setCharacterSize(60);
	pressEnterText.setPosition((window->getSize().x / 2 - 186), window->getSize().y - 100);
	pressEnterText.setString("PRESS ENTER");
	pressEnterText.setFillColor(sf::Color::Yellow);
	pressEnterText.setOutlineColor(sf::Color::Black);
	pressEnterText.setOutlineThickness(2);

	// Initialises variables
	gameState = State::CONTROLS; // Sets game state to default to Controls
	controlsView.reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)); // Resets the view
	animTimer = 0;
	isTransparent = false;
}

Controls::~Controls()
{
}


// Handles all input
void Controls::handleInput(AudioManager &audioManager, Controller &controller)
{
	controller.updateState(); // Updates controller button state

	// Closes window on Escape pressed or Back on the controller pressed
	if (input->isKeyDown(sf::Keyboard::Escape) || controller.getControllerState() & ControllerState::BACK)
	{
		window->close();
	}

	// Changes state on Enter key pressed or Start on the controller pressed
	if (input->isKeyDown(sf::Keyboard::Enter) || controller.getControllerState() & ControllerState::START)
	{
		audioManager.playSoundbyName("enter"); // Play enter sound

		input->setKeyUp(sf::Keyboard::Enter);
		controller.setControllerState(ControllerState::NONE);
		audioManager.stopAllMusic(); // Stops music for next screen
		gameState = State::LEVEL;
	}

	else
	{
		gameState = State::CONTROLS; // Stay on Controls screen
	}
}

void Controls::update(float dt)
{
	// Moves city objects to give an infinite scrolling effect

	city.move(city.getVelocity() * dt);
	city2.move(city2.getVelocity() * dt);

	if (city.getPosition().x + city.getSize().x <= 0)
	{
		city.setPosition(window->getSize().x, city.getPosition().y);
	}

	if (city2.getPosition().x + city2.getSize().x <= 0)
	{
		city2.setPosition(window->getSize().x, city2.getPosition().y);
	}


	animTimer += dt; // Starts animation timer

	if (animTimer >= 0.75)
	{
		// If text is not transparent, make it transparent and reset the timer
		if (!isTransparent)
		{
			pressEnterText.setFillColor(sf::Color::Transparent);
			pressEnterText.setOutlineColor(sf::Color::Transparent);
			animTimer = 0;
			isTransparent = true;
		}

		// If text is transparent, make it not transparent and reset the timer
		else if (isTransparent)
		{
			pressEnterText.setFillColor(sf::Color::Yellow);
			pressEnterText.setOutlineColor(sf::Color::Black);
			animTimer = 0;
			isTransparent = false;
		}
	}
}

// Render everything to the window
void Controls::render()
{
	beginDraw();

	window->setView(controlsView);
	window->draw(background);
	window->draw(city);
	window->draw(city2);
	window->draw(controlsBox);
	window->draw(controlsText);
	window->draw(pressEnterText);

	endDraw();
}

// Loads all textures
void Controls::loadTextures()
{
	backgroundTexture.loadFromFile("gfx/background/Skyline.png");
	cityTexture.loadFromFile("gfx/background/Buildings.png");
	controlsBoxTexture.loadFromFile("gfx/menu/ControlsBox.png");
}

// Sets up background objects
void Controls::setUpBackground()
{
	background.setTexture(&backgroundTexture);
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setPosition(0, 0);

	city.setTexture(&cityTexture);
	city.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	city.setPosition(0, 0);
	city.setVelocity(-50, 0);

	city2.setTexture(&cityTexture);
	city2.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	city2.setPosition(window->getSize().x, 0);
	city2.setVelocity(-50, 0);
}

// Sets up controls box
void Controls::setUpControlsBox()
{
	controlsBox.setTexture(&controlsBoxTexture);
	controlsBox.setSize(sf::Vector2f(141 * 3, 79 * 3));
	controlsBox.setPosition((window->getSize().x / 2) - 210, window->getSize().y / 2 - 200);

	controlsText.setFont(pixels);
	controlsText.setCharacterSize(28);
	controlsText.setPosition((window->getSize().x / 2) - 176, window->getSize().y / 2 - 190);
	controlsText.setFillColor(sf::Color::Yellow);
	controlsText.setOutlineColor(sf::Color::Black);
	controlsText.setOutlineThickness(2);

	// Displays controls
	controlsText.setString("        CONTROLS \n\n    Move with WASD \n    Press J to Jump \n    Press K to Shoot \n Press Space to Pause \n    Press Esc to Quit");
}

// Gets the game state
State Controls::getState()
{
	return gameState;
}

// Clears the window for drawing
void Controls::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Draws the buffer to the window
void Controls::endDraw()
{
	window->display();
}