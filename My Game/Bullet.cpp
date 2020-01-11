#include "Bullet.h"


Bullet::Bullet()
{
	//setInput(input);

	// Sets up the Shot animation
	shot.addFrame(sf::IntRect(45, 0, 15, 11));
	shot.addFrame(sf::IntRect(60, 0, 15, 11));
	shot.addFrame(sf::IntRect(75, 0, 15, 11));
	shot.setFlipped(false);
	shot.setFrameSpeed(0.2f);

	// Sets up the Shot Hit animation
	shotHit.addFrame(sf::IntRect(0, 0, 15, 11));
	shotHit.addFrame(sf::IntRect(15, 0, 15, 11));
	shotHit.addFrame(sf::IntRect(30, 0, 15, 11));
	shotHit.setFrameSpeed(0.1f);
	shotHit.setFlipped(false);
	shotHit.setLooping(false);

	// Sets Shot to be the default animation
	currentAnimation = &shot;
	setTextureRect(currentAnimation->getCurrentFrame());

	animTimer = 0; // Initialises the animation timer
}

Bullet::~Bullet()
{
}


void Bullet::update(float dt)
{
	move(velocity*dt);

	// Makes sure the current animation defaults to Shot
	if (currentAnimation != &shotHit)
	{
		currentAnimation = &shot;
	}

	// Animates the current animation
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

	// If the current animation is Shot Hit - If the bullet has hit something
	if (currentAnimation == &shotHit)
	{
		setVelocity(0, 0); // Stops the bullet moving

		animTimer += dt; // Starts the animation timer

		if (animTimer >= 0.4)
		{
			setAlive(false); // Sets the bullet to not be alive
			shotHit.reset(); // Resets the Shot Hit animation
			currentAnimation = &shot; // Changes the current animation for the next time a bullet spawns
			setTextureRect(currentAnimation->getCurrentFrame());
			animTimer = 0; // Resets the animation timer
		}
	}
}

void Bullet::collisionResponse(GameObject* collider)
{
	// Changes the current animation after collision
	currentAnimation = &shotHit;
	setTextureRect(currentAnimation->getCurrentFrame());
}

BulletType Bullet::getBulletType()
{
	return bulletType;
}

void Bullet::setBulletType(BulletType bt)
{
	bulletType = bt;
}