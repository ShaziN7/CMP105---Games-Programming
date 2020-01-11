#include "SushiBanner.h"


SushiBanner::SushiBanner()
{
	// Sets up the Flash animation
	flash.addFrame(sf::IntRect(0, 0, 36, 13));
	flash.addFrame(sf::IntRect(36, 0, 36, 13));
	flash.addFrame(sf::IntRect(72, 0, 36, 13));
	flash.setFrameSpeed(0.1f);
	flash.setFlipped(false);
}

SushiBanner::~SushiBanner()
{
}


// Animates the Flash animation
void SushiBanner::update(float dt)
{
	flash.animate(dt);
	setTextureRect(flash.getCurrentFrame());
}