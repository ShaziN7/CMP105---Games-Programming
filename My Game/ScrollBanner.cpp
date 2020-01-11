#include "ScrollBanner.h"


ScrollBanner::ScrollBanner()
{
	// Sets up the Scroll animation
	scroll.addFrame(sf::IntRect(0, 0, 13, 47));
	scroll.addFrame(sf::IntRect(13, 0, 13, 47));
	scroll.addFrame(sf::IntRect(26, 0, 13, 47));
	scroll.addFrame(sf::IntRect(39, 0, 13, 47));
	scroll.setFrameSpeed(0.1f);
	scroll.setFlipped(false);
}

ScrollBanner::~ScrollBanner()
{
}


// Animates the Scroll animation
void ScrollBanner::update(float dt)
{
	scroll.animate(dt);
	setTextureRect(scroll.getCurrentFrame());
}