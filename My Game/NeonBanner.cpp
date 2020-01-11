#include "NeonBanner.h"


NeonBanner::NeonBanner()
{
	// Sets up the Flash animation
	flash.addFrame(sf::IntRect(0, 0, 19, 48));
	flash.addFrame(sf::IntRect(19, 0, 19, 48));
	flash.addFrame(sf::IntRect(38, 0, 19, 48));
	flash.addFrame(sf::IntRect(57, 0, 19, 48));
	flash.setFrameSpeed(0.1f);
	flash.setFlipped(false);
}

NeonBanner::~NeonBanner()
{
}


// Animates the Flash animation
void NeonBanner::update(float dt)
{
	flash.animate(dt);
	setTextureRect(flash.getCurrentFrame());
}