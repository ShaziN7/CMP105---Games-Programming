#pragma once

#include "Background.h"


class BackgroundManager
{

public:
	
	BackgroundManager();
	~BackgroundManager();

	void setUp(sf::RenderWindow* window); // Sets up background objects
	void moveWithView(char direction, float dt); // Moves background objects
	void render(sf::RenderWindow* window); // Renders background objects


private:

	// Background Textures
	sf::Texture skylineTexture;
	sf::Texture buildingsTexture;
	sf::Texture nearBuildingsTexture;

	std::vector<Background> backgrounds; // Vector holding background objects
};