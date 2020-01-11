#pragma once

#include "Framework/TileMap.h"
#include "Framework/Collision.h"
#include "Tile.h"
#include "Player.h"


class TileManager
{

public:

	TileManager();
	~TileManager();

	void update(Player &player, float dt, Controller &controller, AudioManager &audioManager); // Updates tiles
	void collisions(Player &player, std::vector<Tile>* section, float dt, int numTiles, Controller &controller, AudioManager &audioManager); // Checks for collisions
	void render(sf::RenderWindow* window, Player &player); // Renders tiles to window
	void checkCollisionSide(Player &player, GameObject* collider); // Checks which side of the tile the collision has happened
	void loadTextures(); // Loads tile textures
	void setUpBuildingOne(); // Sets up tiles for building 1
	void setUpBuildingTwo(); // Sets up tiles for building 2
	void setUpBuildingThree(); // Sets up tiles for building 3
	void setUpBuildingFour(); // Sets up tiles for building 4
	void setUpBuildingFive(); // Sets up tiles for building 5
	void setUpBuildingSix(); // Sets up tiles for building 6
	void setUpBuildingSeven(); // Sets up tiles for building 7
	void setUpBuildingEight(); // Sets up tiles for building 8
	void setUpBuildingNine(); // Sets up tiles for building 9
	void setUpLadders(); // Sets up ladder tiles
	void setUpPlatforms(); // Sets up platform tiles
	void setUpEmptyTiles(); // Sets up empty tiles
	void setUpBricks(); // Sets up brick tiles
	void setUpWindows(); // Sets up window tiles
	void setUpWalls(); // Sets up wall tiles
	void setUpPropTiles(); // Sets up prop tiles


private:

	// Initialises Tile and Tile Map objects

	Tile tile;
	Tile* aboveTile; // The tile above, used in ladder collision
	Tile* belowTile; // The tile below, used in ladder collision

	TileMap tileMap; // Tile map for Building 1
	TileMap tileMap2; // Tile map for Building 2
	TileMap tileMap3; // Tile map for Building 3
	TileMap tileMap4; // Tile map for Building 4
	TileMap tileMap6; // Tile map for Building 5
	TileMap tileMap5; // Tile map for Building 6
	TileMap tileMap7; // Tile map for Building 7
	TileMap tileMap8; // Tile map for Building 8
	TileMap tileMap9; // Tile map for Building 9


	// Initialises vectors
	std::vector<Tile> tiles;
	std::vector<Tile>* section1 = tileMap.getLevel(); // Building 1
	std::vector<Tile>* section2 = tileMap2.getLevel(); // Building 2
	std::vector<Tile>* section3 = tileMap3.getLevel(); // Building 3
	std::vector<Tile>* section4 = tileMap4.getLevel(); // Building 4
	std::vector<Tile>* section5 = tileMap5.getLevel(); // Building 5
	std::vector<Tile>* section6 = tileMap6.getLevel(); // Building 6
	std::vector<Tile>* section7 = tileMap7.getLevel(); // Building 7
	std::vector<Tile>* section8 = tileMap8.getLevel(); // Building 8
	std::vector<Tile>* section9 = tileMap9.getLevel(); // Building 9

	ColliderType colliderType; // Which type of collider the tile is
	CollisionSide collisionSide; // Which side of the tile has collided

	int numTiles; // How many tiles horizontally the map has, used to calculate above and below tiles
};