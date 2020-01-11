#include "Pause.h"


Pause::Pause(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	loadTextures(); // Loads textures

	// Loads fonts
	anurati.loadFromFile("font/Anurati.ttf");
	pixels.loadFromFile("font/04B03.ttf");

	setUpBackground(); // Sets up background objects
	setUpTitle(); // Sets up title objects
	setUpControlsBox(); // Sets up controls box objects

	// Sets up pause text
	pauseText.setFont(pixels);
	pauseText.setCharacterSize(50);
	pauseText.setPosition((window->getSize().x / 2 - 320), window->getSize().y - 150);
	pauseText.setString("      GAME PAUSED \n PRESS SPACE TO RESUME");
	pauseText.setFillColor(sf::Color::Yellow);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(2);

	// Initialises variables
	gameState = State::PAUSE; // Sets game state to default to Pause
	pauseView.reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)); // Resets the view
	animTimer = 0;
	isTransparent = false;
}

Pause::~Pause()
{
}


// Handles all input
void Pause::handleInput(Controller &controller, AudioManager &audioManager)
{
	controller.updateState(); // Updates controller button state

	// Closes window on Escape pressed or Back on the controller pressed
	if (input->isKeyDown(sf::Keyboard::Escape) || controller.getControllerState() & ControllerState::BACK)
	{
		window->close();
	}

	// Changes state on Space key pressed or Start on the controller pressed
	if (input->isKeyDown(sf::Keyboard::Space) || controller.getControllerState() & ControllerState::START)
	{
		if (audioManager.getSound("unpause")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("unpause"); // Play unpause sound
		}

		input->setKeyUp(sf::Keyboard::Space);
		controller.setControllerState(ControllerState::NONE);
		audioManager.getMusic()->stop(); // Stops music for next screen
		gameState = State::LEVEL;
	}

	else
	{
		gameState = State::PAUSE; // Stay on Pause screen
	}
}

void Pause::update(float dt, AudioManager &audioManager)
{
	if (audioManager.getMusic()->getStatus() == sf::SoundSource::Paused)
	{
		audioManager.playMusicbyName("pause"); // Play pause music
	}

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
			pauseText.setFillColor(sf::Color::Transparent);
			pauseText.setOutlineColor(sf::Color::Transparent);
			animTimer = 0;
			isTransparent = true;
		}

		// If text is transparent, make it not transparent and reset the timer
		else if (isTransparent)
		{
			pauseText.setFillColor(sf::Color::Yellow);
			pauseText.setOutlineColor(sf::Color::Black);
			animTimer = 0;
			isTransparent = false;
		}
	}
}

// Render everything to the window
void Pause::render()
{
	beginDraw();

	window->setView(pauseView);
	window->draw(background);
	window->draw(city);
	window->draw(city2);
	window->draw(titleShadowBackText);
	window->draw(titleShadowMiddleText);
	window->draw(titleText);
	window->draw(controlsBox);
	window->draw(controlsText);
	window->draw(pauseText);

	endDraw();
}

// Loads all textures
void Pause::loadTextures()
{
	backgroundTexture.loadFromFile("gfx/background/Skyline.png");
	cityTexture.loadFromFile("gfx/background/Buildings.png");
	controlsBoxTexture.loadFromFile("gfx/menu/ControlsBox.png");
}

// Sets up background objects
void Pause::setUpBackground()
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

// Sets up title objects
void Pause::setUpTitle()
{
	titleText.setFont(anurati);
	titleText.setCharacterSize(60);
	titleText.setLetterSpacing(10);
	titleText.setPosition((window->getSize().x / 2) - 380, window->getSize().y / 2 - 200);
	titleText.setString("CYBER CITY");
	titleText.setFillColor(sf::Color::White);

	titleShadowMiddleText.setFont(anurati);
	titleShadowMiddleText.setCharacterSize(60);
	titleShadowMiddleText.setLetterSpacing(10);
	titleShadowMiddleText.setPosition(titleText.getPosition().x - 2, titleText.getPosition().y + 2);
	titleShadowMiddleText.setString("CYBER CITY");
	titleShadowMiddleText.setFillColor(sf::Color::Magenta);

	titleShadowBackText.setFont(anurati);
	titleShadowBackText.setCharacterSize(60);
	titleShadowBackText.setLetterSpacing(10);
	titleShadowBackText.setPosition(titleShadowMiddleText.getPosition().x - 2, titleShadowMiddleText.getPosition().y + 2);
	titleShadowBackText.setString("CYBER CITY");
	titleShadowBackText.setFillColor(sf::Color::Cyan);
}

// Sets up controls box objects
void Pause::setUpControlsBox()
{
	controlsBox.setTexture(&controlsBoxTexture);
	controlsBox.setSize(sf::Vector2f(141 * 3, 79 * 3));
	controlsBox.setPosition((window->getSize().x / 2) - 210, window->getSize().y / 2 - 90);

	controlsText.setFont(pixels);
	controlsText.setCharacterSize(28);
	controlsText.setPosition((window->getSize().x / 2) - 176, window->getSize().y / 2 - 80);
	controlsText.setFillColor(sf::Color::Yellow);
	controlsText.setOutlineColor(sf::Color::Black);
	controlsText.setOutlineThickness(2);

	// Displays controls
	controlsText.setString("        CONTROLS \n\n    Move with WASD \n    Press J to Jump \n    Press K to Shoot \n Press Space to Pause \n    Press Esc to Quit");
}

// Gets the game state
State Pause::getState()
{
	return gameState;
}

// Clears the window for drawing
void Pause::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Draws the buffer to the window
void Pause::endDraw()
{
	window->display();
}