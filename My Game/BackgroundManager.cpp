#include "BackgroundManager.h"


BackgroundManager::BackgroundManager()
{
	// Loads background textures
	skylineTexture.loadFromFile("gfx/background/Skyline.png");
	buildingsTexture.loadFromFile("gfx/background/Buildings.png");
	nearBuildingsTexture.loadFromFile("gfx/background/NearBuildings.png");

	// Initialises a vector to hold the background objects
	for (int i = 0; i < 5; i++)
	{
		backgrounds.push_back(Background());
	}
}

BackgroundManager::~BackgroundManager()
{
}


void BackgroundManager::setUp(sf::RenderWindow* window)
{
	// Sets up each background object to display properly on the screen

	backgrounds[0].setTexture(&skylineTexture);
	backgrounds[0].setSize(sf::Vector2f(window->getSize().x + 210, window->getSize().y + 210));
	backgrounds[0].setPosition(0, 220);

	backgrounds[1].setTexture(&buildingsTexture);
	backgrounds[1].setSize(sf::Vector2f(window->getSize().x + 210, window->getSize().y + 210));
	backgrounds[1].setPosition(0, 220);

	backgrounds[2].setTexture(&buildingsTexture);
	backgrounds[2].setSize(sf::Vector2f(window->getSize().x + 210, window->getSize().y + 210));
	backgrounds[2].setPosition(backgrounds[1].getPosition().x + backgrounds[1].getSize().x, 220);

	backgrounds[3].setTexture(&nearBuildingsTexture);
	backgrounds[3].setSize(sf::Vector2f(1009 * 3, 224 * 3));
	backgrounds[3].setPosition(20, 450);

	backgrounds[4].setTexture(&nearBuildingsTexture);
	backgrounds[4].setSize(sf::Vector2f(1009 * 2.5, 224 * 2.5));
	backgrounds[4].setPosition(backgrounds[3].getPosition().x + backgrounds[3].getSize().x, 450);
}

void BackgroundManager::moveWithView(char direction, float dt)
{
	// Moves background whichever way the view is moving
	// Each object moves at different speeds to give a parallax effect

	if (direction == 'r')
	{
		backgrounds[0].move(400 * dt, 0);
		backgrounds[1].move(370 * dt, 0);
		backgrounds[2].move(370 * dt, 0);
		backgrounds[3].move(340 * dt, 0);
		backgrounds[4].move(340 * dt, 0);
	}

	else if (direction == 'l')
	{
		backgrounds[0].move(-400 * dt, 0);
		backgrounds[1].move(-370 * dt, 0);
		backgrounds[2].move(-370 * dt, 0);
		backgrounds[3].move(-340 * dt, 0);
		backgrounds[4].move(-340 * dt, 0);
	}

	else if (direction == 'd')
	{
		backgrounds[0].move(0, 400 * dt);
		backgrounds[1].move(0, 400 * dt);
		backgrounds[2].move(0, 400 * dt);
		backgrounds[3].move(0, 400 * dt);
		backgrounds[4].move(0, 400 * dt);
	}

	else if (direction == 'u')
	{
		backgrounds[0].move(0, -400 * dt);
		backgrounds[1].move(0, -400 * dt);
		backgrounds[2].move(0, -400 * dt);
		backgrounds[3].move(0, -400 * dt);
		backgrounds[4].move(0, -400 * dt);
	}
}

void BackgroundManager::render(sf::RenderWindow* window)
{
	// Renders each background object

	for (int i = 0; i < backgrounds.size(); i++)
	{
			window->draw(backgrounds[i]);
	}
}