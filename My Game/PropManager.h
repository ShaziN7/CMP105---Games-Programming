#pragma once

#include "Prop.h"
#include "BigBanner.h"
#include "CokeBanner.h"
#include "MonitorFace.h"
#include "ScrollBanner.h"
#include "SushiBanner.h"
#include "SideBanner.h"
#include "NeonBanner.h"


class PropManager
{

public:

	PropManager();
	~PropManager();

	void update(float dt); // Updates props
	void render(sf::RenderWindow* window, sf::View* view); // Renders props to window


private:

	// ---------- Private Functions ---------- \\

	void loadTextures(); // Loads prop textures
	void setUpBigBanners(); // Sets up Big Banners props
	void setUpCokeBanners(); // Sets up Coke Banners props
	void setUpMonitorFaces(); // Sets up Monitor Faces props
	void setUpNeonBanners(); // Sets up Neon Banners props
	void setUpScrollBanners(); // Sets up Scroll Banners props
	void setUpSushiBanners(); // Sets up Sushi Banners props
	void setUpSideBanners(); // Sets up Side Banners props
	void setUpStillProps(); // Sets up Still props


	// ---------- Variables ---------- \\

	// Prop textures
	sf::Texture bigBannerTexture;
	sf::Texture cokeBannerTexture;
	sf::Texture monitorFaceTexture;
	sf::Texture scrollBannerTexture;
	sf::Texture sushiBannerTexture;
	sf::Texture sideBannerTexture;
	sf::Texture neonBannerTexture;
	sf::Texture bannersTexture;
	sf::Texture hotelSignTexture;
	sf::Texture openBannerTexture;

	// Prop vectors
	std::vector<BigBanner> bigBanners;
	std::vector<CokeBanner> cokeBanners;
	std::vector<MonitorFace> monitorFaces;
	std::vector<NeonBanner> neonBanners;
	std::vector<ScrollBanner> scrollBanners;
	std::vector<SushiBanner> sushiBanners;
	std::vector<SideBanner> sideBanners;
	std::vector<Prop> stillProps;
};