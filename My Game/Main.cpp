// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "Title.h"
#include "Controls.h"
#include "Difficulty.h"
#include "Pause.h"
#include "Credits.h"
#include "Framework/GameState.h"
#include "States.h"
#include "Framework/AudioManager.h"
#include <SFML/Window/Joystick.hpp>


int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1152, 672), "My Game");

	// Initialise input and level objects.
	Input input;
	Title title(&window, &input);
	Difficulty difficulty(&window, &input);
	Controls controls(&window, &input);
	Level level(&window, &input);
	Pause pause(&window, &input);
	Credits credits(&window, &input);

	// Initialise state
	State gameState = State::TITLE;

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	//Initialise audio
	AudioManager audioManager;

	audioManager.addMusic("sfx/MenuMusic.ogg", "title"); // Menu music
	audioManager.addMusic("sfx/LevelMusic.ogg", "level"); // Level music
	audioManager.addMusic("sfx/PauseMusic.ogg", "pause"); // Pause music
	audioManager.addMusic("sfx/CreditsMusic.ogg", "credits"); // Credits music

	audioManager.addSound("sfx/Walk.ogg", "run"); // Run sound
	audioManager.addSound("sfx/PlayerShoot.ogg", "shoot"); // Player shoot sound
	audioManager.addSound("sfx/Jump.ogg", "jump"); // Jump sound
	audioManager.addSound("sfx/Climb.ogg", "climb"); // Climb sound
	audioManager.addSound("sfx/Coin.ogg", "coin"); // Coin sound
	audioManager.addSound("sfx/DroneDie.ogg", "drone"); // Drone die sound
	audioManager.addSound("sfx/TurretDie.ogg", "turret"); // Turret die sound
	audioManager.addSound("sfx/EnemyShoot.ogg", "enemyshoot"); // Enemy shoot sound
	audioManager.addSound("sfx/EnemyImpact.ogg", "enemy"); // Enemy shot sound
	audioManager.addSound("sfx/PlayerCollide.ogg", "collide"); // Player collision sound
	audioManager.addSound("sfx/PlayerFall.ogg", "fall"); // Player fall sound
	audioManager.addSound("sfx/PauseButton.ogg", "pausebutton"); // Pause button sound
	audioManager.addSound("sfx/UnpauseButton.ogg", "unpause"); // Unpause sound
	audioManager.addSound("sfx/DirectionButton.ogg", "dirbutton"); // Direction menu sound
	audioManager.addSound("sfx/EnterButton.ogg", "enter"); // Enter menu sound
	audioManager.addSound("sfx/ExitButton.ogg", "exit"); // Exit sound

	audioManager.getSound("run")->setVolume(100);
	

	// Initialise controller
	Controller controller;

	// Initialise game difficulty
	GameDifficulty gameDifficulty;


	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Makes sure delta time doesn't go too high
		if (deltaTime > 0.15f)
		{
			deltaTime = 0.15f;
		}


		// Call game loop based on current game state

		switch (gameState)
		{
			case (State::TITLE):
			{
				title.handleInput(controller, audioManager);
				title.update(deltaTime, audioManager);
				title.render();
				gameState = title.getState();
				break;
			}

			case (State::DIFFICULTY):
			{
				difficulty.handleInput(controller, audioManager);
				difficulty.update(deltaTime);
				difficulty.render();
				gameDifficulty = difficulty.getGameDifficulty();
				gameState = difficulty.getState();
				break;
			}

			case (State::CONTROLS):
			{
				controls.handleInput(audioManager, controller);
				controls.update(deltaTime);
				controls.render();
				gameState = controls.getState();
				break;
			}

			case (State::LEVEL):
			{
				level.handleInput(deltaTime, audioManager, controller);
				level.update(deltaTime, audioManager, controller, gameDifficulty);
				level.render();
				gameState = level.getState();
				break;
			}

			case(State::PAUSE):
			{
				pause.handleInput(controller, audioManager);
				pause.update(deltaTime, audioManager);
				pause.render();
				gameState = pause.getState();
				break;
			}

			case(State::CREDITS):
			{
				credits.handleInput(controller, audioManager);
				credits.update(deltaTime, audioManager);
				credits.render();
				gameState = credits.getState();
				break;
			}

			case(State::RESET):
			{
				level.resetLevel();
				gameState = level.getState();
				break;
			}

		}

	}
}