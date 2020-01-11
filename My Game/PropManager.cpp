#include "PropManager.h"


PropManager::PropManager()
{
	// Loads the prop textures
	loadTextures();

	// Set up vectors and objects
	setUpBigBanners();
	setUpCokeBanners();
	setUpMonitorFaces();
	setUpNeonBanners();
	setUpScrollBanners();
	setUpSushiBanners();
	setUpSideBanners();
	setUpStillProps();
}

PropManager::~PropManager()
{
}


// Updates all props
void PropManager::update(float dt)
{
	for (int i = 0; i < bigBanners.size(); i++)
	{
		bigBanners[i].update(dt);
	}

	for (int i = 0; i < cokeBanners.size(); i++)
	{
		cokeBanners[i].update(dt);
	}

	for (int i = 0; i < monitorFaces.size(); i++)
	{
		monitorFaces[i].update(dt);
	}

	for (int i = 0; i < neonBanners.size(); i++)
	{
		neonBanners[i].update(dt);
	}

	for (int i = 0; i < scrollBanners.size(); i++)
	{
		scrollBanners[i].update(dt);
	}

	for (int i = 0; i < sushiBanners.size(); i++)
	{
		sushiBanners[i].update(dt);
	}

	for (int i = 0; i < sideBanners.size(); i++)
	{
		sideBanners[i].update(dt);
	}

	for (int i = 0; i < stillProps.size(); i++)
	{
		stillProps[i].update(dt);
	}
}

// Checks if props are visible on screen and if so renders them
void PropManager::render(sf::RenderWindow* window, sf::View* view)
{
	for (int i = 0; i < bigBanners.size(); i++)
	{
		if (bigBanners[i].getVisible(*view))
		{
			window->draw(bigBanners[i]);
		}
	}

	for (int i = 0; i < cokeBanners.size(); i++)
	{
		if (cokeBanners[i].getVisible(*view))
		{
			window->draw(cokeBanners[i]);
		}
	}

	for (int i = 0; i < monitorFaces.size(); i++)
	{
		if (monitorFaces[i].getVisible(*view))
		{
			window->draw(monitorFaces[i]);
		}
	}

	for (int i = 0; i < neonBanners.size(); i++)
	{
		if (neonBanners[i].getVisible(*view))
		{
			window->draw(neonBanners[i]);
		}
	}

	for (int i = 0; i < scrollBanners.size(); i++)
	{
		if (scrollBanners[i].getVisible(*view))
		{
			window->draw(scrollBanners[i]);
		}
	}

	for (int i = 0; i < sushiBanners.size(); i++)
	{
		if (sushiBanners[i].getVisible(*view))
		{
			window->draw(sushiBanners[i]);
		}
	}

	for (int i = 0; i < sideBanners.size(); i++)
	{
		if (sideBanners[i].getVisible(*view))
		{
			window->draw(sideBanners[i]);
		}
	}

	for (int i = 0; i < stillProps.size(); i++)
	{
		if (stillProps[i].getVisible(*view))
		{
			window->draw(stillProps[i]);
		}
	}
}

// Loads all prop textures
void PropManager::loadTextures()
{
	monitorFaceTexture.loadFromFile("gfx/props/MonitorFaceSheet.png");
	scrollBannerTexture.loadFromFile("gfx/props/ScrollBannerSheet.png");
	sideBannerTexture.loadFromFile("gfx/props/SideBannerSheet.png");
	neonBannerTexture.loadFromFile("gfx/props/NeonBannerSheet.png");
	bigBannerTexture.loadFromFile("gfx/props/BigBannerSheet.png");
	cokeBannerTexture.loadFromFile("gfx/props/CokeBannerSheet.png");
	sushiBannerTexture.loadFromFile("gfx/props/SushiBannerSheet.png");
	bannersTexture.loadFromFile("gfx/props/Banners.png");
	hotelSignTexture.loadFromFile("gfx/props/HotelSign.png");
	openBannerTexture.loadFromFile("gfx/props/OpenBanner.png");
}

// Sets up Big Banners props
void PropManager::setUpBigBanners()
{
	for (int i = 0; i < 3; i++)
	{
		bigBanners.push_back(BigBanner());
		bigBanners[i].setTexture(&bigBannerTexture);
		bigBanners[i].setSize(sf::Vector2f(35 * 2, 92 * 2));
	}

	bigBanners[0].setPosition(800, 560);
	bigBanners[0].setBuilding(2);

	bigBanners[1].setPosition(2180, 500);
	bigBanners[1].setBuilding(3);

	bigBanners[2].setPosition(3200, 150);
	bigBanners[2].setBuilding(5);
}

// Sets up Coke Banners props
void PropManager::setUpCokeBanners()
{
	for (int i = 0; i < 4; i++)
	{
		cokeBanners.push_back(CokeBanner());
		cokeBanners[i].setTexture(&cokeBannerTexture);
		cokeBanners[i].setSize(sf::Vector2f(27 * 2, 78 * 2));
	}

	cokeBanners[0].setPosition(950, 750);
	cokeBanners[0].setBuilding(2);

	cokeBanners[1].setPosition(1450, -100);
	cokeBanners[1].setBuilding(3);

	cokeBanners[2].setPosition(3740, 750);
	cokeBanners[2].setBuilding(5);

	cokeBanners[3].setPosition(4550, 600);
	cokeBanners[3].setBuilding(6);
}

// Sets up Monitor Faces props
void PropManager::setUpMonitorFaces()
{
	for (int i = 0; i < 6; i++)
	{
		monitorFaces.push_back(MonitorFace());
		monitorFaces[i].setTexture(&monitorFaceTexture);
		monitorFaces[i].setSize(sf::Vector2f(21 * 2, 18 * 2));
	}

	monitorFaces[0].setPosition(100, 770);
	monitorFaces[0].setBuilding(1);

	monitorFaces[1].setPosition(90, 440);
	monitorFaces[1].setBuilding(1);

	monitorFaces[2].setPosition(3180, 430);
	monitorFaces[2].setBuilding(5);

	monitorFaces[3].setPosition(3400, 430);
	monitorFaces[3].setBuilding(5);

	monitorFaces[4].setPosition(4160, 324);
	monitorFaces[4].setBuilding(6);

	monitorFaces[5].setPosition(5674, 554);
	monitorFaces[5].setBuilding(8);
}

// Sets up Neon Banners props
void PropManager::setUpNeonBanners()
{
	for (int i = 0; i < 3; i++)
	{
		neonBanners.push_back(NeonBanner());
		neonBanners[i].setTexture(&neonBannerTexture);
		neonBanners[i].setSize(sf::Vector2f(19 * 2, 48 * 2));
	}

	neonBanners[0].setPosition(66, 74);
	neonBanners[0].setBuilding(1);

	neonBanners[1].setPosition(1450, 400);
	neonBanners[1].setBuilding(3);

	neonBanners[2].setPosition(5600, 300);
	neonBanners[2].setBuilding(8);
}

// Sets up Scroll Banners props
void PropManager::setUpScrollBanners()
{
	for (int i = 0; i < 2; i++)
	{
		scrollBanners.push_back(ScrollBanner());
		scrollBanners[i].setTexture(&scrollBannerTexture);
		scrollBanners[i].setSize(sf::Vector2f(13 * 2, 47 * 2));
	}

	scrollBanners[0].setPosition(440, 780);
	scrollBanners[0].setBuilding(1);

	scrollBanners[1].setPosition(1988, 210);
	scrollBanners[1].setBuilding(3);
}

// Sets up Sushi Banners props
void PropManager::setUpSushiBanners()
{
	for (int i = 0; i < 3; i++)
	{
		sushiBanners.push_back(SushiBanner());
		sushiBanners[i].setTexture(&sushiBannerTexture);
		sushiBanners[i].setSize(sf::Vector2f(36 * 2, 13 * 2));
	}

	sushiBanners[0].setPosition(830, 822);
	sushiBanners[0].setBuilding(2);

	sushiBanners[1].setPosition(220, 190);
	sushiBanners[1].setBuilding(3);

	sushiBanners[2].setPosition(5130, 440);
	sushiBanners[2].setBuilding(7);
}

// Sets up Side Banners props
void PropManager::setUpSideBanners()
{
	for (int i = 0; i < 4; i++)
	{
		sideBanners.push_back(SideBanner());
		sideBanners[i].setTexture(&sideBannerTexture);
		sideBanners[i].setSize(sf::Vector2f(19 * 2, 76 * 2));
	}

	sideBanners[0].setPosition(430, 360);
	sideBanners[0].setBuilding(1);

	sideBanners[1].setPosition(1020, 504);
	sideBanners[1].setBuilding(2);

	sideBanners[2].setPosition(2190, 740);
	sideBanners[2].setBuilding(3);

	sideBanners[3].setPosition(2500, 400);
	sideBanners[3].setBuilding(4);
}

// Sets up Still props
void PropManager::setUpStillProps()
{
	for (int i = 0; i < 3; i++)
	{
		stillProps.push_back(Prop());
		stillProps[i].setSize(sf::Vector2f(19 * 2, 76 * 2));
	}

	stillProps[0].setTexture(&bannersTexture);
	stillProps[0].setSize(sf::Vector2f(28 * 2, 66 * 2));
	stillProps[0].setPosition(3000, 500);
	stillProps[0].setBuilding(5);

	stillProps[1].setTexture(&hotelSignTexture);
	stillProps[1].setSize(sf::Vector2f(68 * 2, 35 * 2));
	stillProps[1].setPosition(3650, 70);
	stillProps[1].setBuilding(5);

	stillProps[2].setTexture(&openBannerTexture);
	stillProps[2].setSize(sf::Vector2f(14 * 2, 44 * 2));
	stillProps[2].setPosition(5580, 720);
	stillProps[2].setBuilding(8);
}