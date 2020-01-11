#include "Turret.h"


Turret::Turret()
{
	// Sets up the Spin animation
	spin.addFrame(sf::IntRect(550, 0, 25, 23));
	spin.addFrame(sf::IntRect(605, 0, 25, 23));
	spin.addFrame(sf::IntRect(660, 0, 25, 23));
	spin.addFrame(sf::IntRect(715, 0, 25, 23));
	spin.addFrame(sf::IntRect(770, 0, 25, 23));
	spin.addFrame(sf::IntRect(825, 0, 25, 23));
	spin.setFrameSpeed(0.2f);
	spin.setFlipped(false);

	// Sets up the Explode animation
	explode.addFrame(sf::IntRect(220, 0, 55, 52));
	explode.addFrame(sf::IntRect(275, 0, 55, 52));
	explode.addFrame(sf::IntRect(330, 0, 55, 52));
	explode.addFrame(sf::IntRect(385, 0, 55, 52));
	explode.addFrame(sf::IntRect(440, 0, 55, 52));
	explode.addFrame(sf::IntRect(495, 0, 55, 52));
	explode.setFrameSpeed(0.05f);
	explode.setLooping(false);
	explode.setFlipped(false);

	// Sets Spin to be the default animation
	currentAnimation = &spin;
	setTextureRect(currentAnimation->getCurrentFrame());

	deathTimer = 0; // Initialises death timer
}

Turret::~Turret()
{
}


void Turret::update(float dt, AudioManager &audioManager)
{
	// Set the current animation to the Spin animation if turret is not exploding
	if (currentAnimation != &explode)
	{
		currentAnimation = &spin;
	}

	if (currentAnimation == &explode)
	{
		if (audioManager.getSound("enemy")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("enemy"); // Play enemy shot sound
		}

		deathTimer += dt; // If turret has been shot, start the death timer

		if (deathTimer >= 0.2)
		{
			if (audioManager.getSound("turret")->getStatus() == sf::SoundSource::Stopped)
			{
				audioManager.playSoundbyName("turret"); // Play turret death sound
			}
		}

		if (deathTimer >= 0.4)
		{
			deathTimer = 0; // Reset death timer
			setAlive(false); // Kill the turret
		}
	}
	
	// Animate the current animation
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());
}

// Changes the current animation after collision
void Turret::collisionResponse(GameObject* collider)
{
	currentAnimation = &explode;
	setTextureRect(currentAnimation->getCurrentFrame());
	setCollider(false);
}

// Resets the turret animations
void Turret::resetAnimation()
{
	explode.reset();
	currentAnimation = &spin;
	setTextureRect(currentAnimation->getCurrentFrame());
}

// If turret should animate or not
void Turret::shouldAnimate(bool a)
{
	if (a == true)
	{
		currentAnimation->setPlaying(true); // If yes, animate turret
	}

	else if (a == false)
	{
		currentAnimation->reset();
		currentAnimation->setPlaying(false); // If no, stop animating turret
	}
}