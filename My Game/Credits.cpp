#include "Credits.h"


Credits::Credits(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	loadTextures(); // Loads textures

	// Loads fonts
	anurati.loadFromFile("font/Anurati.ttf");
	pixels.loadFromFile("font/04B03.ttf");

	setUpBackground(); // Sets up background objects
	setUpTitle(); // Sets up title objects
	setUpCreditsBox(); // Sets up credits box objects
	
	// Sets up text to press enter
	pressEnterText.setFont(pixels);
	pressEnterText.setCharacterSize(60);
	pressEnterText.setPosition(150, window->getSize().y - 100);
	pressEnterText.setString("PRESS ENTER TO PLAY AGAIN");
	pressEnterText.setFillColor(sf::Color::Yellow);
	pressEnterText.setOutlineColor(sf::Color::Black);
	pressEnterText.setOutlineThickness(2);

	// Initialises variables
	gameState = State::CREDITS; // Sets game state to default to Credits
	creditsView.reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)); // Resets the view
	animTimer = 0;
	isTransparent = false;
}

Credits::~Credits()
{
}


// Handles all input
void Credits::handleInput(Controller &controller, AudioManager &audioManager)
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
		audioManager.getMusic()->stop(); // Stops music for next screen
		gameState = State::RESET;
	}

	else
	{
		gameState = State::CREDITS; // Stay on Credits screen
	}
}

void Credits::update(float dt, AudioManager &audioManager)
{

	if (audioManager.getMusic()->getStatus() == sf::SoundSource::Paused)
	{
		audioManager.playMusicbyName("credits"); // Play credits music
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
void Credits::render()
{
	beginDraw();

	window->setView(creditsView);
	window->draw(background);
	window->draw(city);
	window->draw(city2);
	window->draw(titleShadowBackText);
	window->draw(titleShadowMiddleText);
	window->draw(titleText);
	window->draw(creditsBox);
	window->draw(creditsText);
	window->draw(pressEnterText);

	endDraw();
}

// Loads all textures
void Credits::loadTextures()
{
	backgroundTexture.loadFromFile("gfx/background/Skyline.png");
	cityTexture.loadFromFile("gfx/background/Buildings.png");
	creditsBoxTexture.loadFromFile("gfx/menu/ControlsBox.png");
}

// Sets up background objects
void Credits::setUpBackground()
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
void Credits::setUpTitle()
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

// Sets up credits box objects
void Credits::setUpCreditsBox()
{
	creditsBox.setTexture(&creditsBoxTexture);
	creditsBox.setSize(sf::Vector2f(141 * 3, 79 * 3));
	creditsBox.setPosition((window->getSize().x / 2) - 210, window->getSize().y / 2 - 90);

	creditsText.setFont(pixels);
	creditsText.setCharacterSize(28);
	creditsText.setPosition((window->getSize().x / 2) - 198, window->getSize().y / 2 - 60);
	creditsText.setFillColor(sf::Color::Yellow);
	creditsText.setOutlineColor(sf::Color::Black);
	creditsText.setOutlineThickness(2);

	// Displays credits
	creditsText.setString(" THANK YOU FOR PLAYING!! \n\n Coding by Shannon Craig \n   Assets by Luis Zuno. \n     Music by DOS-88. \n Sounds by PMSFX & GDM.");
}

// Gets the game state
State Credits::getState()
{
	return gameState;
}

// Clears the window for drawing
void Credits::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Draws the buffer to the window
void Credits::endDraw()
{
	window->display();
}