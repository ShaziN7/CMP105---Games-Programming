#include "Level.h"


Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// Reset view to default
	view.reset(sf::FloatRect(0, 220, window->getSize().x, window->getSize().y));

	setUpPlayer(); // Set up player object
	setUpScoreBox(); // Set up score box

	// Spawn objects
	turretManager.spawn();
	droneManager.spawn();
	coinManager.spawn();
	backgroundManager.setUp(window);

	quit = false; // Initialise quit variable#
}

Level::~Level()
{
}


// Handles user input
void Level::handleInput(float dt, AudioManager &audioManager, Controller &controller)
{
	controller.updateState(); // Updates controller button state

	player.handleInput(dt, controller, audioManager); // Handle user input for player

	// Quit to menu on Escape pressed
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		if (audioManager.getSound("exit")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("exit"); // Play exit sound
		}

		audioManager.getMusic()->pause(); // Pause music

		input->setKeyUp(sf::Keyboard::Escape);
		quit = true; // Quit to menu
		gameState = State::RESET;
	}

	// Spawn a bullet
	else if (input->isKeyDown(sf::Keyboard::K) || controller.getControllerState() & ControllerState::X)
	{
		bulletManager.spawn(dt, audioManager, player);
	}

	// Pause the game
	else if (input->isKeyDown(sf::Keyboard::Space) || controller.getControllerState() & ControllerState::START)
	{
		if (audioManager.getSound("pausebutton")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("pausebutton"); // Play pause sound
		}

		input->setKeyUp(sf::Keyboard::Space);
		controller.setControllerState(ControllerState::NONE);
		audioManager.getMusic()->pause(); // Pauses music for next screen
		gameState = State::PAUSE;
	}

	// This runs the credits - Uncomment to activate!
	/*else if (input->isKeyDown(sf::Keyboard::C))
	{
		input->setKeyUp(sf::Keyboard::C);
		quit = true;
		audioManager.stopAllSounds();
		audioManager.getMusic()->pause();
		gameState = State::CREDITS;
	}*/

	else
	{
		gameState = State::LEVEL; // Stay on Level screen
	}
}

// Update game objects
void Level::update(float dt, AudioManager &audioManager, Controller &controller, GameDifficulty &difficulty)
{
	if (audioManager.getMusic()->getStatus() == sf::SoundSource::Stopped)
	{
		audioManager.playMusicbyName("level"); // Play level music
	}

	gameDifficulty = difficulty; // Set game difficulty to what player chose

	// Update controller state
	sf::Joystick::update();
	controller.updateState();


	// If player is alive, update player object
	if (player.isAlive())
	{
		player.update(dt, audioManager);
	}

	// If player is not alive, reset game
	else
	{
		gameState = State::RESET;
	}

	updateManagers(dt, audioManager, controller); // Updates all object managers
	
	// Update player's score and death text
	std::string playerScore = std::to_string(player.getScore());
	std::string deaths = std::to_string(player.getDeaths());

	scoreText.setString("Coins: " + playerScore + " <     > " + "Deaths: " + deaths);
	
	updateView(dt); // Updates view depending on player's position
	
	// If player has reached end of level, change game state to credits
	if (player.getPosition().x >= 5700)
	{
		quit = true;
		audioManager.stopAllSounds();
		audioManager.getMusic()->pause();
		gameState = State::CREDITS;
	}
}

// Render level
void Level::render()
{
	beginDraw();

	window->setView(view);
	backgroundManager.render(window);
	vehicleManager.render(window, &view);
	tileManager.render(window, player);
	propManager.render(window, &view);
	coinManager.render(window, &view);
	bulletManager.render(window, &view);
	turretManager.render(window, &view);
	droneManager.render(window, &view);
	window->draw(player);
	window->draw(scoreBox);
	window->draw(scoreText);

	endDraw();
}

// Sets up the player object
void Level::setUpPlayer()
{
	player.setInput(input); // Sets player input

	playerTexture.loadFromFile("gfx/player/PlayerSpritesheet.png"); // Loads player textures

	player.setTexture(&playerTexture);
	player.setSize(sf::Vector2f(71 * 2, 67 * 2));
	player.setPosition(0, 900);
	player.setCollisionBox(sf::FloatRect(50, 30, player.getSize().x / 3, player.getSize().y - 30));
	player.setAlive(true);
	player.setCollider(true);
}

// Sets up the score box
void Level::setUpScoreBox()
{
	scoreBoxTexture.loadFromFile("gfx/gui/ScoreBox.png"); // Loads score box texture

	scoreBox.setTexture(&scoreBoxTexture);
	scoreBox.setSize(sf::Vector2f(800 / 1.5, 100 / 1.5));
	scoreBox.setPosition(view.getCenter().x - 266, view.getCenter().y - 348);

	if (!pixels.loadFromFile("font/04B03.ttf"))
	{
		std::cout << "Error loading font 04B03." << std::endl;
	}

	// Sets up score text
	scoreText.setFont(pixels);
	scoreText.setPosition(scoreBox.getPosition().x + 60, scoreBox.getPosition().y + 10);
	scoreText.setCharacterSize(30);
	scoreText.setStyle(sf::Text::Style::Underlined);
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setOutlineColor(sf::Color::Magenta);
	scoreText.setOutlineThickness(0.5);
}

// Updates the object managers
void Level::updateManagers(float dt, AudioManager &audioManager, Controller &controller)
{
	turretPointer = turretManager.getTurretVector(); // Gets pointer for turret vector
	dronePointer = droneManager.getDroneVector(); // Gets pointer for drone vector

	turretManager.update(dt, player, audioManager);
	droneManager.update(dt, player, audioManager);
	bulletManager.update(dt, player, turretPointer, dronePointer, audioManager, gameDifficulty);
	tileManager.update(player, dt, controller, audioManager);
	coinManager.update(dt, player, audioManager);
	vehicleManager.update(dt);
	propManager.update(dt);
}

// Updates view depending on player's position
// Lets player get close to right hand side so they don't see too much of what is coming
void Level::updateView(float dt)
{
	// Move view right
	if (player.getPosition().x >= view.getCenter().x + 200 && view.getCenter().x + (view.getSize().x / 2) < 5700)
	{
		view.move(400 * dt, 0);
		backgroundManager.moveWithView('r', dt);
		scoreBox.move(400 * dt, 0);
		scoreText.move(400 * dt, 0);
	}

	// Move view left
	else if (player.getPosition().x <= view.getCenter().x - 200 && view.getCenter().x - (view.getSize().x / 2) > 0)
	{
		view.move(-400 * dt, 0);
		backgroundManager.moveWithView('l', dt);
		scoreBox.move(-400 * dt, 0);
		scoreText.move(-400 * dt, 0);
	}

	// Move view down
	if (player.getPosition().y >= view.getCenter().y + 100 && view.getCenter().y + (view.getSize().y / 2) < 1120)
	{
		view.move(0, 400 * dt);
		backgroundManager.moveWithView('d', dt);
		scoreBox.move(0, 400 * dt);
		scoreText.move(0, 400 * dt);
	}

	// Move view up
	if (player.getPosition().y <= view.getCenter().y && view.getCenter().y - (view.getSize().y / 2) > 0)
	{
		view.move(0, -400 * dt);
		backgroundManager.moveWithView('u', dt);
		scoreBox.move(0, -400 * dt);
		scoreText.move(0, -400 * dt);
	}
}

// Resets level for new game
void Level::resetLevel()
{
	player.setPosition(0, 900);
	player.setAlive(true);

	// Reset objects
	player.resetPlayer(quit);
	droneManager.resetDrones();
	turretManager.resetTurrets();
	
	// Spawn objects
	turretManager.spawn();
	droneManager.spawn();
	coinManager.spawn();
	backgroundManager.setUp(window);

	// Initialises variables
	view.reset(sf::FloatRect(0, 220, window->getSize().x, window->getSize().y));

	setUpScoreBox(); // Sets up the score box

	// Quit to title screen
	if (quit)
	{
		quit = false;
		gameState = State::TITLE;
	}

	// If player has died, restart level
	else
	{
		gameState = State::LEVEL;
	}
}

// Returns the game state
State Level::getState()
{
	return gameState;
}

// Clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}