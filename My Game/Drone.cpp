#include "Drone.h"


Drone::Drone()
{
	// Sets up the Turn animation
	turn.addFrame(sf::IntRect(0, 0, 55, 52));
	turn.addFrame(sf::IntRect(55, 0, 55, 52));
	turn.addFrame(sf::IntRect(110, 0, 55, 52));
	turn.addFrame(sf::IntRect(165, 0, 55, 52));
	turn.setFrameSpeed(0.1f);
	turn.setLooping(false);

	// Sets up the Explode animation
	explode.addFrame(sf::IntRect(220, 0, 55, 52));
	explode.addFrame(sf::IntRect(275, 0, 55, 52));
	explode.addFrame(sf::IntRect(330, 0, 55, 52));
	explode.addFrame(sf::IntRect(385, 0, 55, 52));
	explode.addFrame(sf::IntRect(440, 0, 55, 52));
	explode.addFrame(sf::IntRect(495, 0, 55, 52));
	explode.setFrameSpeed(0.05f);
	explode.setLooping(false);

	// Sets Turn to be the default animation
	currentAnimation = &turn;
	setTextureRect(currentAnimation->getCurrentFrame());
	
	// Initialises variables
	animTimer = 0;
	deathTimer = 0;
	moving = true;
	isHit = false;
}

Drone::~Drone()
{
}


void Drone::update(float dt, AudioManager &audioManager)
{
	// If the drone has not been hit
	if (!isHit)
	{
		// If the drone is going left, set target as left target
		if (horizDirection == 'l')
		{
			target = sf::Vector2f(leftTarget, getPosition().y);
			turn.setFlipped(false);
		}

		// If the drone is going right, set target as right target
		else if (horizDirection == 'r')
		{
			target = sf::Vector2f(rightTarget, getPosition().y);
			turn.setFlipped(true);
		}

		setTextureRect(turn.getCurrentFrame());

		// Uses vector to move the drone
		if (moving)
		{
			direction = target - getPosition();
			direction = Vector::normalise(direction);
			velocity = (direction * speed);
			move(velocity * dt);
		}

		// If the drone has reached the target position
		if (Vector::magnitude(target - getPosition()) <= 1)
		{
			animTimer += dt; // Start the animation timer
			moving = false; // Stop the drone moving
			setPosition(target);

			if (currentAnimation != &explode)
			{
				currentAnimation = &turn; // Set the current animation to the Turn animation if drone is not exploding
			}

			// Animate the current animation
			currentAnimation->animate(dt);
			setTextureRect(currentAnimation->getCurrentFrame());

			if (animTimer >= 0.5)
			{
				turn.reset(); // Reset Turn animation

				// If drone's direction was left, flip and go right
				if (horizDirection == 'l')
				{
					target = sf::Vector2f(rightTarget, getPosition().y);
					horizDirection = 'r';
					turn.setFlipped(true);
				}

				// If drone's direction was right, flip and go left
				else if (horizDirection == 'r')
				{
					target = sf::Vector2f(leftTarget, getPosition().y);
					horizDirection = 'l';
					turn.setFlipped(false);
				}

				animTimer = 0; // Reset the animation timer
				moving = true; // Move the drone again
			}
		}
	}

	else if (isHit)
	{
		if (audioManager.getSound("enemy")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("enemy"); // Play enemy shot sound
		}

		deathTimer += dt; // If drone has been shot, start the death timer

		currentAnimation->animate(dt); // Animate the current animation

		if (deathTimer >= 0.2)
		{
			if (audioManager.getSound("drone")->getStatus() == sf::SoundSource::Stopped)
			{
				audioManager.playSoundbyName("drone"); // Play drone death sound
			}
		}

		if (deathTimer >= 0.4)
		{
			deathTimer = 0; // Reset death timer
			setAlive(false); // Kill the drone
		}
	}
}

// Changes the current animation after collision and sets the drone to be hit
void Drone::collisionResponse(GameObject* collider)
{
	isHit = true; // Drone has been hit
	setCollider(false); // Don't collide when exploding

	currentAnimation = &explode; // Change animation to explode
	setTextureRect(currentAnimation->getCurrentFrame());
}

// Resets the drone animations
void Drone::resetAnimation()
{
	explode.reset();
	turn.reset();
	currentAnimation = &turn;
	setTextureRect(currentAnimation->getCurrentFrame());
}

void Drone::setIsHit(bool h)
{
	isHit = h;
}

void Drone::setHorizDirection(char d)
{
	horizDirection = d;
}

void Drone::setLeftTarget(int l)
{
	leftTarget = l;
}

void Drone::setRightTarget(int r)
{
	rightTarget = r;
}

void Drone::setAnimTimer(int a)
{
	animTimer = a;
}

void Drone::setDeathTimer(int d)
{
	deathTimer = d;
}

void Drone::setMoving(bool m)
{
	moving = m;
}
