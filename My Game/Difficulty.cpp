#include "Difficulty.h"


Difficulty::Difficulty(sf::RenderWindow * hwnd, Input * in)
{
	window = hwnd;
	input = in;

	// Loads textures
	backgroundTexture.loadFromFile("gfx/background/Skyline.png");
	cityTexture.loadFromFile("gfx/background/Buildings.png");

	// Loads fonts
	anurati.loadFromFile("font/Anurati.ttf");
	pixels.loadFromFile("font/04B03.ttf");

	setUpBackground(); // Sets up background objects
	setUpTitle(); // Sets up title objects
	setUpDifficultyText(); // Sets up difficulty text

	// Initialises variables
	gameState = State::DIFFICULTY; // Sets game state to default to Difficulty
	difficultyView.reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)); // Resets the view
	animTimer = 0;
	isTransparent = false;
}

Difficulty::~Difficulty()
{
}


// Handles all input
void Difficulty::handleInput(Controller &controller, AudioManager &audioManager)
{
	controller.updateState(); // Updates controller button state

	// Closes window on Escape pressed or Back on the controller pressed
	if (input->isKeyDown(sf::Keyboard::Escape) || controller.getControllerState() & ControllerState::BACK)
	{
		window->close();
	}

	// Changes which difficulty is highlighted
	if (input->isKeyDown(sf::Keyboard::Right) || input->isKeyDown(sf::Keyboard::D) || controller.getControllerState() & ControllerState::RIGHT)
	{
		audioManager.playSoundbyName("dirbutton"); // Play direction sound

		input->setKeyUp(sf::Keyboard::Right);
		input->setKeyUp(sf::Keyboard::D);
		controller.setControllerState(ControllerState::NONE);

		if (hardText.getStyle() == sf::Text::Style::Underlined)
		{
			hardText.setStyle(sf::Text::Style::Regular);
			mediumText.setStyle(sf::Text::Style::Underlined);
		}

		else if (mediumText.getStyle() == sf::Text::Style::Underlined)
		{
			mediumText.setStyle(sf::Text::Style::Regular);
			easyText.setStyle(sf::Text::Style::Underlined);
		}
	}

	// Changes which difficulty is highlighted
	else if (input->isKeyDown(sf::Keyboard::Left) || input->isKeyDown(sf::Keyboard::A) || controller.getControllerState() & ControllerState::LEFT)
	{
		audioManager.playSoundbyName("dirbutton"); // Play direction sound

		input->setKeyUp(sf::Keyboard::Left);
		input->setKeyUp(sf::Keyboard::A);
		controller.setControllerState(ControllerState::NONE);

		if (easyText.getStyle() == sf::Text::Style::Underlined)
		{
			easyText.setStyle(sf::Text::Style::Regular);
			mediumText.setStyle(sf::Text::Style::Underlined);
		}

		else if (mediumText.getStyle() == sf::Text::Style::Underlined)
		{
			mediumText.setStyle(sf::Text::Style::Regular);
			hardText.setStyle(sf::Text::Style::Underlined);
		}
	}

	// Set difficulty highlighted on Enter key pressed or Start on the controller pressed
	if (input->isKeyDown(sf::Keyboard::Enter) || controller.getControllerState() & ControllerState::A)
	{
		if (audioManager.getSound("enter")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("enter"); // Play enter sound
		}

		if (hardText.getStyle() == sf::Text::Style::Underlined)
		{
			gameDifficulty = GameDifficulty::HARD;
			input->setKeyUp(sf::Keyboard::Enter);
			controller.setControllerState(ControllerState::NONE);
			gameState = State::CONTROLS;
		}

		else if (mediumText.getStyle() == sf::Text::Style::Underlined)
		{
			gameDifficulty = GameDifficulty::MEDIUM;
			input->setKeyUp(sf::Keyboard::Enter);
			controller.setControllerState(ControllerState::NONE);
			gameState = State::CONTROLS;
		}

		else if (easyText.getStyle() == sf::Text::Style::Underlined)
		{
			gameDifficulty = GameDifficulty::EASY;
			input->setKeyUp(sf::Keyboard::Enter);
			controller.setControllerState(ControllerState::NONE);
			gameState = State::CONTROLS;
		}
	}

	else
	{
		gameState = State::DIFFICULTY; // Stay on Difficulty screen
	}
}

void Difficulty::update(float dt)
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

	if (animTimer >= 0.5)
	{
		// If text highlighted is not transparent, make it transparent and reset the timer
		if (!isTransparent)
		{
			if (hardText.getStyle() == sf::Text::Style::Underlined)
			{
				hardText.setFillColor(sf::Color::Transparent);
				hardText.setOutlineColor(sf::Color::Transparent);
				animTimer = 0;
				isTransparent = true;
			}

			else if (mediumText.getStyle() == sf::Text::Style::Underlined)
			{
				mediumText.setFillColor(sf::Color::Transparent);
				mediumText.setOutlineColor(sf::Color::Transparent);
				animTimer = 0;
				isTransparent = true;
			}

			else if (easyText.getStyle() == sf::Text::Style::Underlined)
			{
				easyText.setFillColor(sf::Color::Transparent);
				easyText.setOutlineColor(sf::Color::Transparent);
				animTimer = 0;
				isTransparent = true;
			}
		}

		// If text highlighted is transparent, make it not transparent and reset the timer
		else if (isTransparent)
		{
			if (hardText.getStyle() == sf::Text::Style::Underlined || hardText.getFillColor() == sf::Color::Transparent)
			{
				hardText.setFillColor(sf::Color::Yellow);
				hardText.setOutlineColor(sf::Color::Black);
				animTimer = 0;
				isTransparent = false;
			}

			if (mediumText.getStyle() == sf::Text::Style::Underlined || mediumText.getFillColor() == sf::Color::Transparent)
			{
				mediumText.setFillColor(sf::Color::Yellow);
				mediumText.setOutlineColor(sf::Color::Black);
				animTimer = 0;
				isTransparent = false;
			}

			if (easyText.getStyle() == sf::Text::Style::Underlined || easyText.getFillColor() == sf::Color::Transparent)
			{
				easyText.setFillColor(sf::Color::Yellow);
				easyText.setOutlineColor(sf::Color::Black);
				animTimer = 0;
				isTransparent = false;
			}
		}
	}
}

// Render everything to the window
void Difficulty::render()
{
	beginDraw();

	window->setView(difficultyView);
	window->draw(background);
	window->draw(city);
	window->draw(city2);
	window->draw(titleShadowBackText);
	window->draw(titleShadowMiddleText);
	window->draw(titleText);
	window->draw(hardText);
	window->draw(mediumText);
	window->draw(easyText);

	endDraw();
}

// Sets up background objects
void Difficulty::setUpBackground()
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
void Difficulty::setUpTitle()
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

// Sets up difficulty text
void Difficulty::setUpDifficultyText()
{
	hardText.setFont(pixels);
	hardText.setCharacterSize(60);
	hardText.setPosition(110, window->getSize().y - 100);
	hardText.setString("HARD");
	hardText.setFillColor(sf::Color::Yellow);
	hardText.setOutlineColor(sf::Color::Black);
	hardText.setOutlineThickness(2);
	hardText.setStyle(sf::Text::Style::Underlined);

	mediumText.setFont(pixels);
	mediumText.setCharacterSize(60);
	mediumText.setPosition(466, window->getSize().y - 100);
	mediumText.setString("MEDIUM");
	mediumText.setFillColor(sf::Color::Yellow);
	mediumText.setOutlineColor(sf::Color::Black);
	mediumText.setOutlineThickness(2);

	easyText.setFont(pixels);
	easyText.setCharacterSize(60);
	easyText.setPosition((window->getSize().x - 246), window->getSize().y - 100);
	easyText.setString("EASY");
	easyText.setFillColor(sf::Color::Yellow);
	easyText.setOutlineColor(sf::Color::Black);
	easyText.setOutlineThickness(2);
}

// Gets the game difficulty
GameDifficulty Difficulty::getGameDifficulty()
{
	return gameDifficulty;
}

// Gets the game state
State Difficulty::getState()
{
	return gameState;
}

// Clears the window for drawing
void Difficulty::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Draws the buffer to the window
void Difficulty::endDraw()
{
	window->display();
}