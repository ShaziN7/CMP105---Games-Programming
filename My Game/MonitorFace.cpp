#include "MonitorFace.h"


MonitorFace::MonitorFace()
{
	// Sets up the Flash animation
	flash.addFrame(sf::IntRect(0, 0, 21, 18));
	flash.addFrame(sf::IntRect(21, 0, 21, 18));
	flash.addFrame(sf::IntRect(42, 0, 21, 18));
	flash.addFrame(sf::IntRect(63, 0, 21, 18));
	flash.setFrameSpeed(0.1f);
	flash.setFlipped(false);
}

MonitorFace::~MonitorFace()
{
}


// Animates the Flash animation
void MonitorFace::update(float dt)
{
	flash.animate(dt);
	setTextureRect(flash.getCurrentFrame());
}