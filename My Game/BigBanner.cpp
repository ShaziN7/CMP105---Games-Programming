#include "BigBanner.h"


BigBanner::BigBanner()
{
	// Sets up the Flash animation
	flash.addFrame(sf::IntRect(0, 0, 35, 92));
	flash.addFrame(sf::IntRect(35, 0, 35, 92));
	flash.addFrame(sf::IntRect(70, 0, 35, 92));
	flash.addFrame(sf::IntRect(105, 0, 35, 92));
	flash.setFrameSpeed(0.1f);
	flash.setFlipped(false);
}

BigBanner::~BigBanner()
{
}


// Animates the Flash animation
void BigBanner::update(float dt)
{
	flash.animate(dt);
	setTextureRect(flash.getCurrentFrame());
}