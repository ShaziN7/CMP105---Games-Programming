#include "SideBanner.h"


SideBanner::SideBanner()
{
	// Sets up the Flash animation
	flash.addFrame(sf::IntRect(0, 0, 19, 76));
	flash.addFrame(sf::IntRect(19, 0, 19, 76));
	flash.addFrame(sf::IntRect(38, 0, 19, 76));
	flash.addFrame(sf::IntRect(57, 0, 19, 76));
	flash.setFrameSpeed(0.1f);
	flash.setFlipped(false);
}

SideBanner::~SideBanner()
{
}


// Animates the Flash animation
void SideBanner::update(float dt)
{
	flash.animate(dt);
	setTextureRect(flash.getCurrentFrame());
}