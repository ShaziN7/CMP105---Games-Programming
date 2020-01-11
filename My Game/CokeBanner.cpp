#include "CokeBanner.h"


CokeBanner::CokeBanner()
{
	// Sets up the Flash animation
	flash.addFrame(sf::IntRect(0, 0, 27, 78));
	flash.addFrame(sf::IntRect(27, 0, 27, 78));
	flash.addFrame(sf::IntRect(54, 0, 27, 78));
	flash.setFrameSpeed(0.1f);
	flash.setFlipped(false);
}

CokeBanner::~CokeBanner()
{
}


// Animates the Flash animation
void CokeBanner::update(float dt)
{
	flash.animate(dt);
	setTextureRect(flash.getCurrentFrame());
}
