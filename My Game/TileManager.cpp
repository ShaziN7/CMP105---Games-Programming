#include "TileManager.h"


TileManager::TileManager()
{
	// Loads the tile textures
	loadTextures();

	// Sets up tiles vector
	for (int i = 0; i < 108; i++)
	{
		tile.setSize(sf::Vector2f(40, 40));
		tile.setCollisionBox(0, 0, 40, 40);
		tile.setCollider(false);
		tiles.push_back(tile);
	}

	// Sets up tiles
	setUpLadders(); // Sets up ladder tiles
	setUpPlatforms(); // Sets up platform tiles
	setUpEmptyTiles(); // Sets up empty tiles
	setUpBricks(); // Sets up brick tiles
	setUpWindows(); // Sets up window tiles
	setUpWalls(); // Sets up wall tiles
	setUpPropTiles(); // Sets up prop tiles

	// Sets up each building
	setUpBuildingOne(); // Sets up tiles for building 1
	setUpBuildingTwo(); // Sets up tiles for building 2
	setUpBuildingThree(); // Sets up tiles for building 3
	setUpBuildingFour(); // Sets up tiles for building 4
	setUpBuildingFive(); // Sets up tiles for building 5
	setUpBuildingSix(); // Sets up tiles for building 6
	setUpBuildingSeven(); // Sets up tiles for building 7
	setUpBuildingEight(); // Sets up tiles for building 8
	setUpBuildingNine(); // Sets up tiles for building 9

	// Initialises variables
	aboveTile = NULL; // The tile above
	belowTile = NULL; // The tile below
	colliderType = ColliderType::NONE;
}

TileManager::~TileManager()
{
}


// Updates tiles
void TileManager::update(Player &player, float dt, Controller &controller, AudioManager &audioManager)
{
	// If player is near building 1, check collisions on building 1 and building 2
	if (player.getPosition().x <= 700)
	{
		collisions(player, section1, dt, 12, controller, audioManager);
		collisions(player, section2, dt, 12, controller, audioManager);
	}

	// If player is near building 2, check collisions on building 2 and building 3
	else if (player.getPosition().x <= 1400)
	{
		collisions(player, section2, dt, 12, controller, audioManager);
		collisions(player, section3, dt, 21, controller, audioManager);
	}

	// If player is near building 3, check collisions on building 3 and building 4
	else if (player.getPosition().x <= 2500)
	{
		collisions(player, section3, dt, 21, controller, audioManager);
		collisions(player, section4, dt, 7, controller, audioManager);
	}

	// If player is near building 4, check collisions on building 4 and building 5
	else if (player.getPosition().x <= 3000)
	{
		collisions(player, section4, dt, 7, controller, audioManager);
		collisions(player, section5, dt, 21, controller, audioManager);
	}

	// If player is near building 5, check collisions on building 5 and building 6
	else if (player.getPosition().x <= 4000)
	{
		collisions(player, section5, dt, 21, controller, audioManager);
		collisions(player, section6, dt, 7, controller, audioManager);
	}

	// If player is near building 6, check collisions on building 6 and building 7
	else if (player.getPosition().x <= 4500) // if player is near building 6
	{
		collisions(player, section6, dt, 7, controller, audioManager);
		collisions(player, section7, dt, 7, controller, audioManager);
	}

	// If player is near building 7, check collisions on building 7 and building 8
	else if (player.getPosition().x <= 5000) // if player is near building 7
	{
		collisions(player, section7, dt, 7, controller, audioManager);
		collisions(player, section8, dt, 7, controller, audioManager);
	}

	// If player is near building 8, check collisions on building 8 and building 9
	else if (player.getPosition().x <= 5500) // if player is near building 8
	{
		collisions(player, section8, dt, 7, controller, audioManager);
		collisions(player, section9, dt, 5, controller, audioManager);
	}

	// If player is near building 9, check collisions on building 9
	else if (player.getPosition().x <= 5700) // if player is near building 9
	{
		collisions(player, section9, dt, 5, controller, audioManager);
	}
}

// Checks for collisions
void TileManager::collisions(Player &player, std::vector<Tile>* section, float dt, int numTiles, Controller &controller, AudioManager &audioManager)
{
	for (int i = 0; i < (int)section->size(); i++)
	{
		// If tile is a collider
		if ((*section)[i].isCollider())
		{
			// Checks for collisions between player and tiles
			if (Collision::checkBoundingBox(&player, &(*section)[i]))
			{
				aboveTile = &(*section)[i - numTiles]; // If colliding, get above tile
				belowTile = &(*section)[i + numTiles]; // If colliding, get below tile

				player.collisionResponse(&(*section)[i], dt, aboveTile, belowTile, controller, audioManager); // If colliding, run player collision response
			}
		}
	}
}

// Renders tiles to window
void TileManager::render(sf::RenderWindow* window, Player &player)
{	
	// If player is near building 1, render building 1 and building 2
	if (player.getPosition().x <= 700)
	{
		tileMap.render(window);
		tileMap2.render(window);
	}

	// If player is near building 2, render building 1, building 2 and building 3
	else if (player.getPosition().x <= 1400)
	{
		tileMap.render(window);
		tileMap2.render(window);
		tileMap3.render(window);
	}

	// If player is near building 3, render building 1, building 2, building 3 and building 4
	else if (player.getPosition().x <= 2500)
	{
		tileMap.render(window);
		tileMap2.render(window);
		tileMap3.render(window);
		tileMap4.render(window);
	}

	// If player is near building 4, render building 2, building 3, building 4 and building 5
	else if (player.getPosition().x <= 3000)
	{
		tileMap2.render(window);
		tileMap3.render(window);
		tileMap4.render(window);
		tileMap5.render(window);
	}

	// If player is near building 5, render building 3, building 4, building 5 and building 6
	else if (player.getPosition().x <= 4000)
	{
		tileMap3.render(window);
		tileMap4.render(window);
		tileMap5.render(window);
		tileMap6.render(window);
	}

	// If player is near building 6, render building 4, building 5, building 6 and building 7
	else if (player.getPosition().x <= 4500)
	{
		tileMap4.render(window);
		tileMap5.render(window);
		tileMap6.render(window);
		tileMap7.render(window);
	}

	// If player is near building 7, render building 5, building 6, building 7 and building 8
	else if (player.getPosition().x <= 5000) // if player is near building 7
	{
		tileMap5.render(window);
		tileMap6.render(window);
		tileMap7.render(window);
		tileMap8.render(window);
	}

	// If player is near end, render building 6, building 7 and building 8 and building 9
	else
	{
		tileMap6.render(window);
		tileMap7.render(window);
		tileMap8.render(window);
		tileMap9.render(window);
	}
}

// Checks which side of tile is colliding
void TileManager::checkCollisionSide(Player &player, GameObject* collider)
{
	// Works out centres and distances between centres

	int playerXCentre = player.getPosition().x + (player.getSize().x / 2); // Player's centre on x-axis
	int playerYCentre = player.getPosition().y + (player.getSize().y / 2); // Player's centre on y-axis

	int colliderXCentre = collider->getPosition().x + (collider->getSize().x / 2); // Collider's centre on x-axis
	int colliderYCentre = collider->getPosition().y + (collider->getSize().y / 2); // Collider's centre on y-axis

	int xDifference = playerXCentre - colliderXCentre; // Difference between centres on x-axis
	int yDifference = playerYCentre - colliderYCentre; // Difference between centres on y-axis

	int posX = 0;
	int posY = 0;

	if (xDifference < 0)
	{
		posX = xDifference * -1; // Difference on x-axis is negative
	}

	else
	{
		posX = xDifference; // Difference on x-axis is positive
	}

	if (yDifference < 0)
	{
		posY = yDifference * -1; // Difference on y-axis is negative
	}

	else
	{
		posY = yDifference; // Difference on x-axis is positive
	}

	// Works out which side was hit

	if (posX > posY) // It is x-axis
	{
		if (xDifference < 0) // Left was hit
		{
			collisionSide = CollisionSide::LEFT;
		}

		else // Right was hit
		{
			collisionSide = CollisionSide::RIGHT;
		}
	}

	else // It is y-axis
	{
		if (yDifference < 0) // Bottom was hit
		{
			collisionSide = CollisionSide::BOTTOM;
		}

		else // Top was hit
		{
			collisionSide = CollisionSide::TOP;
		}
	}
}

// Loads all tile map textures
void TileManager::loadTextures()
{
	tileMap.loadTexture("gfx/props/MyTileset.png");
	tileMap2.loadTexture("gfx/props/MyTileset.png");
	tileMap3.loadTexture("gfx/props/MyTileset.png");
	tileMap4.loadTexture("gfx/props/MyTileset.png");
	tileMap6.loadTexture("gfx/props/MyTileset.png");
	tileMap5.loadTexture("gfx/props/MyTileset.png");
	tileMap7.loadTexture("gfx/props/MyTileset.png");
	tileMap8.loadTexture("gfx/props/MyTileset.png");
	tileMap9.loadTexture("gfx/props/MyTileset.png");
}

// Sets up building 1
void TileManager::setUpBuildingOne()
{
	// Sets tile set for tile map 1
	tileMap.setTileSet(tiles);

	// Sets tile map 1's size
	sf::Vector2u mapSize1(12, 28);

	// Lays out map 1
	std::vector<int> map1 =
	{
		0, 3, 14, 15, 16, 1, 1, 14, 15, 16, 18, 0,
		0, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 0,
		0, 2, 5, 6, 7, 67, 87, 5, 6, 7, 17, 0,
		0, 2, 8, 9, 10, 68, 88, 8, 9, 10, 18, 0,
		0, 3, 11, 12, 13, 67, 1, 11, 12, 13, 19, 0,
		0, 2, 14, 15, 16, 68, 1, 14, 15, 16, 18, 0,
		0, 3, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 4, 5, 6, 7, 58, 59, 5, 6, 7, 17, 0,
		0, 2, 8, 9, 10, 60, 61, 8, 9, 10, 17, 0,
		0, 3, 11, 12, 13, 1, 1, 11, 12, 13, 18, 0,
		0, 4, 14, 15, 16, 1, 1, 14, 15, 16, 19, 0,
		105, 106, 106, 106, 106, 62, 106, 106, 106, 106, 106, 107,
		0, 3, 5, 6, 7, 62, 67, 5, 6, 7, 18, 0,
		0, 3, 8, 9, 10, 62, 67, 8, 9, 10, 18, 0,
		0, 2, 11, 12, 13, 62, 67, 11, 12, 13, 17, 0,
		0, 3, 14, 15, 16, 62, 68, 14, 15, 16, 18, 0,
		0, 52, 52, 52, 52, 62, 52, 52, 52, 52, 52, 0,
		0, 2, 5, 6, 7, 62, 1, 5, 6, 7, 17, 0,
		0, 3, 8, 9, 10, 62, 1, 8, 9, 10, 18, 0,
		0, 4, 11, 12, 13, 62, 87, 11, 12, 13, 19, 0,
		0, 2, 14, 15, 16, 63, 88, 14, 15, 16, 19, 0,
		0, 3, 106, 106, 106, 106, 106, 106, 106, 62, 106, 107,
		0, 4, 5, 6, 7, 58, 59, 5, 6, 62, 17, 0,
		0, 2, 8, 9, 10, 60, 61, 8, 9, 62, 17, 0,
		0, 3, 11, 12, 13, 1, 1, 11, 12, 62, 18, 0,
		0, 4, 14, 15, 16, 1, 1, 14, 15, 63, 19, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	// Builds tile map 1
	tileMap.setTileMap(map1, mapSize1);
	tileMap.setPosition(sf::Vector2f(20, 0));
	tileMap.buildLevel();
}

// Sets up building 2
void TileManager::setUpBuildingTwo()
{
	// Sets tile set for tile map 2
	tileMap2.setTileSet(tiles);

	// Sets tile map 2's size
	sf::Vector2u mapSize2(12, 20);

	// Lays out map 2
	std::vector<int> map2 =
	{
		0, 0, 0, 53, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 56, 56, 57, 56, 56, 56, 56, 56, 56, 56, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 2, 1, 67, 67, 64, 1, 1, 58, 59, 17, 0,
		0, 3, 1, 67, 67, 65, 1, 1, 60, 61, 18, 0,
		0, 4, 1, 67, 67, 65, 1, 1, 1, 91, 19, 0,
		0, 2, 1, 67, 67, 65, 1, 1, 1, 92, 17, 0,
		0, 3, 1, 67, 67, 65, 69, 70, 71, 1, 18, 0,
		0, 4, 1, 90, 90, 65, 72, 73, 74, 1, 19, 0,
		0, 2, 1, 87, 87, 65, 58, 59, 91, 1, 17, 0,
		0, 3, 1, 88, 88, 66, 60, 61, 92, 1, 18, 0,
		0, 4, 1, 67, 67, 1, 65, 1, 91, 1, 19, 0,
		0, 2, 1, 67, 67, 1, 65, 1, 92, 1, 17, 0,
		0, 3, 1, 67, 67, 1, 65, 90, 90, 90, 18, 0,
		0, 4, 1, 67, 67, 1, 65, 90, 90, 90, 19, 0,
		0, 2, 1, 66, 67, 1, 65, 1, 1, 1, 17, 0,
		0, 3, 69, 70, 71, 1, 65, 1, 58, 59, 18, 0,
		0, 4, 72, 73, 74, 1, 65, 1, 60, 61, 19, 0,
	};

	// Builds tile map 2
	tileMap2.setTileMap(map2, mapSize2);
	tileMap2.setPosition(sf::Vector2f(720, 320));
	tileMap2.buildLevel();
}

// Sets up building 3
void TileManager::setUpBuildingThree()
{
	// Sets tile set for tile map 3
	tileMap3.setTileSet(tiles);
	
	// Sets tile map 3's size
	sf::Vector2u mapSize3(21, 33);

	// Lays out map 3
	std::vector<int> map3 =
	{
		0, 20, 21, 32, 33, 34, 28, 75, 76, 77, 28, 93, 94, 95, 28, 32, 33, 34, 44, 45, 0,
		0, 22, 23, 35, 36, 37, 29, 78, 79, 80, 29, 96, 97, 98, 29, 35, 36, 37, 46, 47, 0,
		0, 24, 25, 38, 39, 40, 30, 81, 82, 83, 30, 99, 100, 101, 29, 38, 39, 40, 48, 49, 0,
		0, 26, 27, 41, 42, 43, 31, 84, 85, 86, 30, 102, 103, 104, 29, 41, 42, 43, 50, 51, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 32, 33, 34, 28, 75, 76, 77, 28, 32, 33, 34, 28, 93, 94, 95, 44, 45, 0,
		0, 22, 23, 35, 36, 37, 29, 78, 79, 80, 29, 35, 36, 37, 29, 96, 97, 98, 46, 47, 0,
		0, 24, 25, 38, 39, 40, 31, 81, 82, 83, 30, 38, 39, 40, 29, 99, 100, 101, 48, 49, 0,
		0, 26, 27, 41, 42, 43, 30, 84, 85, 86, 30, 41, 42, 43, 29, 102, 103, 104,50, 51, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 62, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 93, 94, 95, 28, 75, 76, 77, 28, 32, 33, 34, 62, 75, 76, 77, 44, 45, 0,
		0, 22, 23, 96, 97, 98, 29, 78, 79, 80, 29, 35, 36, 37, 62, 78, 79, 80, 46, 47, 0,
		0, 24, 25, 99, 100, 101, 30, 81, 82, 83, 30, 38, 39, 40, 62, 81, 82, 83, 48, 49, 0,
		0, 26, 27, 102, 103, 104, 30, 84, 85, 86, 30, 41, 42, 43, 62, 84, 85, 86, 50, 51, 0,
		105, 106, 106, 106, 106, 106, 29, 52, 52, 52, 52, 52, 52, 52, 62, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 32, 33, 34, 29, 58, 59, 1, 1, 1, 58, 59, 62, 32, 33, 34, 44, 45, 0,
		0, 22, 23, 35, 36, 37, 29, 60, 61, 1, 1, 1, 60, 61, 62, 35, 36, 37, 46, 47, 0,
		0, 24, 25, 38, 39, 40, 30, 89, 1, 69, 70, 71, 1, 1, 62, 38, 39, 40, 48, 49, 0,
		0, 26, 27, 41, 42, 43, 31, 90, 1, 72, 73, 74, 1, 1, 62, 41, 42, 43, 50, 51, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 62, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 75, 76, 77, 28, 75, 76, 77, 28, 93, 94, 95, 62, 32, 33, 34, 44, 45, 0,
		0, 22, 23, 78, 79, 80, 29, 78, 79, 80, 31, 96, 97, 98, 62, 35, 36, 37, 46, 47, 0,
		0, 24, 25, 81, 82, 83, 30, 81, 82, 83, 29, 99, 100, 101, 62, 38, 39, 40, 48, 49, 0,
		0, 26, 27, 84, 85, 86, 30, 84, 85, 86, 29, 102, 103, 104, 63, 41, 42, 43, 50, 51, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 32, 33, 34, 28, 75, 76, 77, 28, 32, 33, 34, 28, 32, 33, 34, 44, 45, 0,
		0, 22, 23, 35, 36, 37, 29, 78, 79, 80, 29, 35, 36, 37, 29, 35, 36, 37, 46, 47, 0,
		0, 24, 25, 38, 39, 40, 30, 81, 82, 83, 30, 38, 39, 40, 29, 38, 39, 40, 48, 49, 0
	};

	// Builds tile map 3
	tileMap3.setTileMap(map3, mapSize3);
	tileMap3.setPosition(sf::Vector2f(1420, 0));
	tileMap3.buildLevel();
}

// Sets up building 4
void TileManager::setUpBuildingFour()
{
	// Sets tile set for tile map 4
	tileMap4.setTileSet(tiles);

	// Sets tile map 4's size
	sf::Vector2u mapSize4(7, 27);

	// Lays out map 4
	std::vector<int> map4 =
	{
		0, 0, 0, 53, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 56, 56, 57, 56, 56, 0,
		105, 106, 106, 106, 106, 106, 107,
		0, 2, 67, 91, 1, 18, 0,
		0, 3, 67, 92, 1, 17, 0,
		0, 4, 67, 91, 1, 18, 0,
		0, 2, 67, 92, 1, 18, 0,
		0, 3, 67, 91, 1, 18, 0,
		0, 4, 67, 92, 1, 19, 0,
		0, 2, 58, 59, 1, 18, 0,
		0, 3, 60, 61, 1, 18, 0,
		0, 4, 1, 91, 1, 19, 0,
		0, 2, 1, 92, 1, 18, 0,
		0, 3, 1, 91, 1, 18, 0,
		0, 4, 1, 92, 1, 18, 0,
		0, 2, 1, 91, 1, 18, 0,
		0, 3, 1, 92, 1, 18, 0,
		0, 4, 1, 91, 1, 18, 0,
		0, 3, 1, 92, 1, 18, 0,
		0, 3, 69, 70, 71, 19, 0,
		0, 3, 72, 73, 74, 18, 0
	};

	// Builds tile map 4
	tileMap4.setTileMap(map4, mapSize4);
	tileMap4.setPosition(sf::Vector2f(2480, 40));
	tileMap4.buildLevel();
}

// Sets up building 5
void TileManager::setUpBuildingFive()
{
	// Sets tile set for tile map 5
	tileMap5.setTileSet(tiles);

	// Sets tile map 5's size
	sf::Vector2u mapSize5(21, 28);

	// Lays out map 5
	std::vector<int> map5 =
	{
		// 21 x 5
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 56, 57, 56, 56, 56, 0, 0, 0, 56, 56, 56, 57, 0,
		0, 0, 0, 0, 0, 0, 105, 106, 106, 106, 106, 106, 106, 106, 62, 106, 106, 106, 106, 106, 107,
		0, 0, 0, 0, 0, 0, 0, 20, 21, 1, 1, 1, 1, 89, 62, 1, 58, 59, 44, 45, 0,
		0, 0, 0, 0, 0, 0, 0, 22, 23, 90, 90, 1, 1, 1, 62, 1, 60, 61, 46, 47, 0,
		0, 0, 0, 0, 0, 0, 0, 24, 25, 89, 90, 1, 1, 1, 62, 1, 1, 1, 48, 49, 0,
		0, 0, 0, 0, 0, 0, 0, 26, 27, 1, 1, 1, 1, 1, 62, 1, 1, 1, 50, 51, 0,
		0, 0, 0, 0, 0, 0, 0, 24, 25, 69, 70, 71,  1, 1, 62, 1, 90, 89, 46, 47, 0,
		0, 0, 0, 0, 0, 0, 0, 26, 27, 72, 73, 74, 1, 1, 62, 1, 90, 90, 48, 49, 0,
		0, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 62, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 58, 59, 1, 28, 1, 58, 59, 28, 58, 59, 1, 62, 91, 1, 1, 44, 45, 0,
		0, 22, 23, 60, 61, 1, 29, 1, 60, 61, 29, 60, 61, 1, 62, 92, 1, 1, 46, 47, 0,
		0, 24, 25, 89, 89, 1, 31, 1, 90, 90, 29, 90, 90, 1, 62, 91, 1, 90, 48, 49, 0,
		0, 26, 27, 90, 90, 1, 29, 1, 90, 89, 29, 90, 90, 1, 62, 92, 1, 1, 50, 51, 0,
		0, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 62, 52, 52, 52, 52, 52, 0,
		0, 20, 21, 93, 94, 95, 28, 75, 76, 77, 28, 32, 33, 34, 62, 75, 76, 77, 44, 45, 0,
		0, 22, 23, 96, 97, 98, 29, 78, 79, 80, 29, 35, 36, 37, 62, 78, 79, 80, 46, 47, 0,
		0, 24, 25, 99,100, 101, 30, 81, 82, 83, 30, 38, 39, 40, 62, 81, 82, 83, 48, 49, 0,
		0, 26, 27, 102, 103, 104, 30, 84, 85, 86, 30, 41, 42, 43, 63, 84, 85, 86, 50, 51, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 32, 33, 34, 29, 75, 76, 77, 29, 75, 76, 77, 28, 32, 33, 34, 44, 45, 0,
		0, 22, 23, 35, 36, 37, 29, 78, 79, 80, 29, 78, 79, 80, 29, 35, 36, 37, 46, 47, 0,
		0, 24, 25, 38, 39, 40, 30, 81, 82, 83, 29, 81, 82, 83, 31, 38, 39, 40, 48, 49, 0,
		0, 26, 27, 41, 42, 43, 31, 84, 85, 86, 29, 84, 85, 86, 29, 41, 42, 43, 50, 51, 0,
		105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107,
		0, 20, 21, 32, 33, 34, 28, 32, 33, 34, 28, 93, 94, 95, 28, 32, 33, 34, 44, 45, 0
	};

	// Builds tile map 5
	tileMap5.setTileMap(map5, mapSize5);                                            // section 5 - 21 wide
	tileMap5.setPosition(sf::Vector2f(2980, 0));
	tileMap5.buildLevel();
}

// Sets up building 6
void TileManager::setUpBuildingSix()
{
	// Sets tile set for tile map 6
	tileMap6.setTileSet(tiles);

	// Sets tile map 6's size
	sf::Vector2u mapSize6(7, 27);

	// Lays out map 6
	std::vector<int> map6 =
	{
		0, 0, 0, 53, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 56, 56, 57, 56, 56, 0,
		105, 106, 106, 106, 106, 106, 107,
		0, 2, 67, 91, 1, 18, 0,
		0, 3, 67, 92, 1, 17, 0,
		0, 4, 67, 91, 1, 18, 0,
		0, 2, 67, 92, 1, 18, 0,
		0, 3, 67, 91, 1, 18, 0,
		0, 4, 67, 92, 1, 19, 0,
		0, 2, 58, 59, 1, 18, 0,
		0, 3, 60, 61, 1, 18, 0,
		0, 4, 1, 91, 1, 19, 0,
		0, 2, 1, 92, 1, 18, 0,
		0, 3, 1, 91, 1, 18, 0,
		0, 4, 1, 92, 1, 18, 0,
		0, 2, 1, 91, 1, 18, 0,
		0, 3, 1, 92, 1, 18, 0,
		0, 4, 1, 91, 1, 18, 0,
		0, 3, 1, 92, 1, 18, 0,
		0, 3, 69, 70, 71, 19, 0,
		0, 3, 72, 73, 74, 18, 0
	};
	
	// Builds tile map 6
	tileMap6.setTileMap(map6, mapSize6);
	tileMap6.setPosition(sf::Vector2f(4040, 40));
	tileMap6.buildLevel();
}

// Sets up building 7
void TileManager::setUpBuildingSeven()
{
	// Sets tile set for tile map 7
	tileMap7.setTileSet(tiles);

	// Sets tile map 7's size
	sf::Vector2u mapSize7(7, 21);

	// Lays out map 7
	std::vector<int> map7 =
	{
		0, 0, 0, 53, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 56, 56, 57, 56, 56, 0,
		105, 106, 106, 106, 106, 106, 107,
		0, 2, 67, 91, 1, 18, 0,
		0, 3, 67, 92, 1, 17, 0,
		0, 4, 67, 91, 1, 18, 0,
		0, 2, 67, 92, 1, 18, 0,
		0, 3, 67, 91, 1, 18, 0,
		0, 4, 67, 92, 1, 19, 0,
		0, 2, 58, 59, 1, 18, 0,
		0, 3, 60, 61, 1, 18, 0,
		0, 4, 1, 91, 1, 19, 0,
		0, 2, 1, 92, 1, 18, 0,
		0, 3, 1, 91, 1, 18, 0,
		0, 4, 1, 92, 1, 18, 0,
	};

	// Builds tile map 7
	tileMap7.setTileMap(map7, mapSize7);                                            // section 7 - 7 wide
	tileMap7.setPosition(sf::Vector2f(4540, 280));
	tileMap7.buildLevel();
}

// Sets up building 8
void TileManager::setUpBuildingEight()
{
	// Sets tile set for tile map 8
	tileMap8.setTileSet(tiles);

	// Sets tile map 8's size
	sf::Vector2u mapSize8(7, 21);

	// Lays out map 8
	std::vector<int> map8 =
	{
		0, 0, 0, 53, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 0, 0, 55, 0, 0, 0,
		0, 56, 56, 57, 56, 56, 0,
		105, 106, 106, 106, 106, 106, 107,
		0, 2, 67, 91, 1, 18, 0,
		0, 3, 67, 92, 1, 17, 0,
		0, 4, 67, 91, 1, 18, 0,
		0, 2, 67, 92, 1, 18, 0,
		0, 3, 67, 91, 1, 18, 0,
		0, 4, 67, 92, 1, 19, 0,
		0, 2, 58, 59, 1, 18, 0,
		0, 3, 60, 61, 1, 18, 0,
		0, 4, 1, 91, 1, 19, 0,
		0, 2, 1, 92, 1, 18, 0,
		0, 3, 1, 91, 1, 18, 0,
		0, 4, 1, 92, 1, 18, 0,
	};
	
	// Builds tile map 8
	tileMap8.setTileMap(map8, mapSize8);                                            // section 8 - 7 wide
	tileMap8.setPosition(sf::Vector2f(5040, 280));
	tileMap8.buildLevel();
}

// Sets up building 9
void TileManager::setUpBuildingNine()
{
	// Sets tile set for tile map 9
	tileMap9.setTileSet(tiles);

	// Sets tile map 9's size
	sf::Vector2u mapSize9(5, 29);

	// Lays out map9
	std::vector<int> map9 =
	{
		3, 5, 6, 7, 91,
		3, 8, 9, 10, 92,
		2, 11, 12, 13, 91,
		3, 14, 15, 16, 92,
		106, 106, 106, 106, 106,
		3, 5, 6, 7, 91,
		3, 8, 9, 10, 92,
		2, 11, 12, 13, 91,
		3, 14, 15, 16, 92,
		52, 52, 52, 52, 52,
		2, 5, 6, 7, 67,
		3, 8, 9, 10, 68,
		4, 11, 12, 13, 67,
		2, 14, 15, 16, 68,
		106, 106, 106, 106, 106,
		4, 5, 6, 7, 58,
		2, 8, 9, 10, 60,
		3, 11, 12, 13, 1,
		4, 14, 15, 16, 1,
		106, 106, 106, 106, 106,
		3, 5, 6, 7, 1,
		3, 8, 9, 10, 1,
		2, 11, 12, 13, 1,
		3, 14, 15, 16, 1,
		106, 106, 106, 106, 106,
		3, 5, 6, 7, 1,
		3, 8, 9, 10, 1,
		2, 11, 12, 13, 1,
		3, 14, 15, 16, 1
	};

	// Builds tile map 9
	tileMap9.setTileMap(map9, mapSize9);                                            // section 9 - 5 wide
	tileMap9.setPosition(sf::Vector2f(5580, 0));
	tileMap9.buildLevel();
}

// Sets up ladder tiles
void TileManager::setUpLadders()
{
	// Top of ladder
	tiles[62].setTextureRect(sf::IntRect(0, 80, 16, 16));
	tiles[62].setCollider(true);
	tiles[62].setColliderType(ColliderType::LADDER); // Sets type to Ladder for collisions

	// Bottom of ladder
	tiles[63].setTextureRect(sf::IntRect(0, 96, 16, 16));
	tiles[63].setCollider(true);
	tiles[63].setColliderType(ColliderType::LADDER); // Sets type to Ladder for collisions
}

// Sets up platform tiles
void TileManager::setUpPlatforms()
{
	// Left platform
	tiles[105].setTextureRect(sf::IntRect(224, 128, 16, 16));
	tiles[105].setCollider(true);
	tiles[105].setColliderType(ColliderType::PLATFORM); // Sets type to Platform for collisions

	// Middle platform
	tiles[106].setTextureRect(sf::IntRect(240, 128, 16, 16));
	tiles[106].setCollider(true);
	tiles[106].setColliderType(ColliderType::PLATFORM); // Sets type to Platform for collisions

	// Right platform
	tiles[107].setTextureRect(sf::IntRect(256, 128, 16, 16));
	tiles[107].setCollider(true);
	tiles[107].setColliderType(ColliderType::PLATFORM); // Sets type to Platform for collisions
}

// Sets up empty tiles
void TileManager::setUpEmptyTiles()
{
	// Transparent
	tiles[0].setTextureRect(sf::IntRect(0, 128, 16, 16)); // transparent

	// Black
	tiles[1].setTextureRect(sf::IntRect(48, 0, 16, 16)); // black tile
}

// Sets up brick tiles
void TileManager::setUpBricks()
{
	// Left bricks
	tiles[2].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(0, 16, 16, 16));
	tiles[4].setTextureRect(sf::IntRect(0, 32, 16, 16));

	// Right bricks
	tiles[17].setTextureRect(sf::IntRect(96, 0, 16, 16));
	tiles[18].setTextureRect(sf::IntRect(96, 16, 16, 16));
	tiles[19].setTextureRect(sf::IntRect(96, 32, 16, 16));
}

// Sets up window tiles
void TileManager::setUpWindows()
{
	// Normal window
	tiles[5].setTextureRect(sf::IntRect(32, 0, 16, 16));
	tiles[6].setTextureRect(sf::IntRect(48, 0, 16, 16));
	tiles[7].setTextureRect(sf::IntRect(64, 0, 16, 16));
	tiles[8].setTextureRect(sf::IntRect(32, 16, 16, 16));
	tiles[9].setTextureRect(sf::IntRect(48, 16, 16, 16));
	tiles[10].setTextureRect(sf::IntRect(64, 16, 16, 16));
	tiles[11].setTextureRect(sf::IntRect(32, 32, 16, 16));
	tiles[12].setTextureRect(sf::IntRect(48, 32, 16, 16));
	tiles[13].setTextureRect(sf::IntRect(64, 32, 16, 16));
	tiles[14].setTextureRect(sf::IntRect(32, 48, 16, 16));
	tiles[15].setTextureRect(sf::IntRect(48, 48, 16, 16));
	tiles[16].setTextureRect(sf::IntRect(64, 48, 16, 16));

	// Blinds down window
	tiles[32].setTextureRect(sf::IntRect(208, 0, 16, 16));
	tiles[33].setTextureRect(sf::IntRect(224, 0, 16, 16));
	tiles[34].setTextureRect(sf::IntRect(240, 0, 16, 16));
	tiles[35].setTextureRect(sf::IntRect(208, 16, 16, 16));
	tiles[36].setTextureRect(sf::IntRect(224, 16, 16, 16));
	tiles[37].setTextureRect(sf::IntRect(240, 16, 16, 16));
	tiles[38].setTextureRect(sf::IntRect(208, 32, 16, 16));
	tiles[39].setTextureRect(sf::IntRect(224, 32, 16, 16));
	tiles[40].setTextureRect(sf::IntRect(240, 32, 16, 16));
	tiles[41].setTextureRect(sf::IntRect(208, 48, 16, 16));
	tiles[42].setTextureRect(sf::IntRect(224, 48, 16, 16));
	tiles[43].setTextureRect(sf::IntRect(240, 48, 16, 16));

	// Window up window
	tiles[75].setTextureRect(sf::IntRect(160, 80, 16, 16));
	tiles[76].setTextureRect(sf::IntRect(176, 80, 16, 16));
	tiles[77].setTextureRect(sf::IntRect(192, 80, 16, 16));
	tiles[78].setTextureRect(sf::IntRect(160, 96, 16, 16));
	tiles[79].setTextureRect(sf::IntRect(176, 96, 16, 16));
	tiles[80].setTextureRect(sf::IntRect(192, 96, 16, 16));
	tiles[81].setTextureRect(sf::IntRect(160, 112, 16, 16));
	tiles[82].setTextureRect(sf::IntRect(176, 112, 16, 16));
	tiles[83].setTextureRect(sf::IntRect(192, 112, 16, 16));
	tiles[84].setTextureRect(sf::IntRect(160, 128, 16, 16));
	tiles[85].setTextureRect(sf::IntRect(176, 128, 16, 16));
	tiles[86].setTextureRect(sf::IntRect(192, 128, 16, 16));

	// Large window
	tiles[93].setTextureRect(sf::IntRect(320, 80, 16, 16));
	tiles[94].setTextureRect(sf::IntRect(336, 80, 16, 16));
	tiles[95].setTextureRect(sf::IntRect(352, 80, 16, 16));
	tiles[96].setTextureRect(sf::IntRect(320, 96, 16, 16));
	tiles[97].setTextureRect(sf::IntRect(336, 96, 16, 16));
	tiles[98].setTextureRect(sf::IntRect(352, 96, 16, 16));
	tiles[99].setTextureRect(sf::IntRect(320, 112, 16, 16));
	tiles[100].setTextureRect(sf::IntRect(336, 112, 16, 16));
	tiles[101].setTextureRect(sf::IntRect(352, 112, 16, 16));
	tiles[102].setTextureRect(sf::IntRect(320, 128, 16, 16));
	tiles[103].setTextureRect(sf::IntRect(336, 128, 16, 16));
	tiles[104].setTextureRect(sf::IntRect(352, 128, 16, 16));
}

// Sets up wall tiles
void TileManager::setUpWalls()
{
	// Left wall
	tiles[20].setTextureRect(sf::IntRect(128, 0, 16, 16));
	tiles[21].setTextureRect(sf::IntRect(144, 0, 16, 16));
	tiles[22].setTextureRect(sf::IntRect(128, 16, 16, 16));
	tiles[23].setTextureRect(sf::IntRect(144, 16, 16, 16));
	tiles[24].setTextureRect(sf::IntRect(128, 32, 16, 16));
	tiles[25].setTextureRect(sf::IntRect(144, 32, 16, 16));
	tiles[26].setTextureRect(sf::IntRect(128, 48, 16, 16));
	tiles[27].setTextureRect(sf::IntRect(144, 48, 16, 16));

	// Middle wall
	tiles[28].setTextureRect(sf::IntRect(176, 0, 16, 16));
	tiles[29].setTextureRect(sf::IntRect(176, 16, 16, 16));
	tiles[30].setTextureRect(sf::IntRect(176, 32, 16, 16));
	tiles[31].setTextureRect(sf::IntRect(176, 48, 16, 16));

	// Right wall
	tiles[44].setTextureRect(sf::IntRect(272, 0, 16, 16));
	tiles[45].setTextureRect(sf::IntRect(288, 0, 16, 16));
	tiles[46].setTextureRect(sf::IntRect(272, 16, 16, 16));
	tiles[47].setTextureRect(sf::IntRect(288, 16, 16, 16));
	tiles[48].setTextureRect(sf::IntRect(272, 32, 16, 16));
	tiles[49].setTextureRect(sf::IntRect(288, 32, 16, 16));
	tiles[50].setTextureRect(sf::IntRect(272, 48, 16, 16));
	tiles[51].setTextureRect(sf::IntRect(288, 48, 16, 16));
}

// Sets up prop tiles
void TileManager::setUpPropTiles()
{
	// Block
	tiles[52].setTextureRect(sf::IntRect(320, 0, 16, 16));

	// Post
	tiles[53].setTextureRect(sf::IntRect(336, 0, 16, 16));
	tiles[54].setTextureRect(sf::IntRect(336, 16, 16, 16));
	tiles[55].setTextureRect(sf::IntRect(336, 32, 16, 16));
	tiles[56].setTextureRect(sf::IntRect(320, 48, 16, 16));
	tiles[57].setTextureRect(sf::IntRect(336, 48, 16, 16));

	// Air con
	tiles[58].setTextureRect(sf::IntRect(352, 0, 16, 16));
	tiles[59].setTextureRect(sf::IntRect(368, 0, 16, 16));
	tiles[60].setTextureRect(sf::IntRect(352, 16, 16, 16));
	tiles[61].setTextureRect(sf::IntRect(368, 16, 16, 16));

	// Left pipe
	tiles[64].setTextureRect(sf::IntRect(32, 80, 16, 16));
	tiles[65].setTextureRect(sf::IntRect(32, 96, 16, 16));
	tiles[66].setTextureRect(sf::IntRect(32, 112, 16, 16));

	// Panel
	tiles[67].setTextureRect(sf::IntRect(64, 80, 16, 16));
	tiles[68].setTextureRect(sf::IntRect(64, 96, 16, 16));

	// Pipes
	tiles[69].setTextureRect(sf::IntRect(96, 80, 16, 16));
	tiles[70].setTextureRect(sf::IntRect(112, 80, 16, 16));
	tiles[71].setTextureRect(sf::IntRect(128, 80, 16, 16));
	tiles[72].setTextureRect(sf::IntRect(96, 96, 16, 16));
	tiles[73].setTextureRect(sf::IntRect(112, 96, 16, 16));
	tiles[74].setTextureRect(sf::IntRect(128, 96, 16, 16));

	// Grate
	tiles[87].setTextureRect(sf::IntRect(224, 80, 16, 16));
	tiles[88].setTextureRect(sf::IntRect(224, 96, 16, 16));

	// Screen
	tiles[89].setTextureRect(sf::IntRect(256, 80, 16, 16)); // screen
	tiles[90].setTextureRect(sf::IntRect(256, 96, 16, 16));

	// Small pipe
	tiles[91].setTextureRect(sf::IntRect(288, 80, 16, 16));
	tiles[92].setTextureRect(sf::IntRect(288, 96, 16, 16));
}