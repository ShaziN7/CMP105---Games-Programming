#include "Player.h"


Player::Player()
{
	// Sets up the player animations
	setUpAnimations();

	// Sets the default animation to Idle
	currentAnimation = &idle;
	setTextureRect(currentAnimation->getCurrentFrame());

	// Initialises variables
	playerState = PlayerState::IDLE;
	playerDirection = PlayerDirection::RIGHT;
	animTimer = 0;
	score = 0;
	deaths = 0;
	ladderCollision = false;
	isColliding = false;
	applyGravity = false;
	hasSpawned = false;
	respawnTimer = 0;
}

Player::~Player()
{
}

void Player::handleInput(float dt, Controller &controller, AudioManager &audioManager)
{
	controller.updateState(); // Updates controller state

	// Doesn't deal with any input if player is hurt
	if (playerState != PlayerState::HURT)
	{
		if (hasSpawned) // Only allows input if spawn animation has played
		{
			// Player is jumping
			if ((input->isKeyDown(sf::Keyboard::J) || controller.getControllerState() & ControllerState::A)
				&& playerState != PlayerState::JUMPING && playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING)
			{
				playerState = PlayerState::JUMPING;

				velocity.y = -3.f * scale;
				move(velocity * dt);

				if (audioManager.getSound("jump")->getStatus() == sf::SoundSource::Stopped)
				{
					audioManager.playSoundbyName("jump"); // Play jump sound
				}
			}

			// Player is running left
			if ((input->isKeyDown(sf::Keyboard::A) || controller.getControllerState() & ControllerState::LEFT)
				&& playerState != PlayerState::JUMPING && playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING && playerState != PlayerState::RUNSHOOTING)
			{
				playerState = PlayerState::RUNNING;
				playerDirection = PlayerDirection::LEFT;

				setVelocity(-350, 0);

				if (audioManager.getSound("run")->getStatus() == sf::SoundSource::Stopped)
				{
					audioManager.playSoundbyName("run"); // Play run sound
				}
			}

			// Player is running right
			else if ((input->isKeyDown(sf::Keyboard::D) || controller.getControllerState() & ControllerState::RIGHT)
				&& playerState != PlayerState::JUMPING && playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING && playerState != PlayerState::RUNSHOOTING)
			{
				playerState = PlayerState::RUNNING;
				playerDirection = PlayerDirection::RIGHT;

				setVelocity(350, 0);

				if (audioManager.getSound("run")->getStatus() == sf::SoundSource::Stopped)
				{
					audioManager.playSoundbyName("run"); // Play run sound
				}
			}

			// No key press - Player is idle
			else if (!isAnyKeyPressed() && controller.getControllerState() == ControllerState::NONE
				&& playerState != PlayerState::JUMPING && playerState != PlayerState::HURT)
			{
				playerState = PlayerState::IDLE;

				audioManager.getSound("run")->stop(); // Stop run sound when player is not moving
			}
		}
	}
}

void Player::update(float dt, AudioManager &audioManager)
{
	// If player hasn't spawned
	if (!hasSpawned)
	{
		animTimer += dt; // Start animation timer

		if (animTimer >= 0.2)
		{
			spawnAnimation(); // Play spawn animation
			animTimer = 0; // Reset animation timer
			hasSpawned = true; // Set spawned to true
		}
	}

	directions(); // Makes sure player is facing correct direction
	animations(); // Animates the correct animations

	// If gravity should be applied, applies it
	if (applyGravity == true)
	{
		velocity.y += gravity * dt;
	}

	// Checks for collision with bottom of window and kills player if colliding
	if (getPosition().y >= 1300)
	{
		if (audioManager.getSound("fall")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("fall"); // Play fall sound
		}

		velocity = { 0, 0 }; // Stop player moving

		respawnTimer += dt; // Start respawn timer

		if (respawnTimer > 1)
		{
			respawnTimer = 0; // Reset respawn timer
			setAlive(false); // Set player to dead
			deaths += 1;
		}
	}

	// Checks for collision with left of window and stops player moving further
	if (getPosition().x <= 0)
	{
		setPosition(0, getPosition().y);
	}

	move(velocity*dt); // Moves the player

	// Animates the current animation
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

	if (isColliding)
	{
		isColliding = false; // Resets colliding bool
	}

	// Makes player fall directly off platform
	else if (!isColliding && playerState != PlayerState::JUMPING && playerState != PlayerState::HURT)
	{
		velocity.x = 0;
		playerState = PlayerState::JUMPING;
		applyGravity = true;

		if (audioManager.getSound("jump")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("jump"); // Play jump sound
		}
	}


	if (velocity.y > 0 && playerState != PlayerState::JUMPING && playerState != PlayerState::HURT)
	{
		playerState = PlayerState::JUMPING;
	}

	// Makes player fall and animate if they stop climbing a ladder
	else if (velocity.y < 0 && playerState != PlayerState::JUMPING && playerState != PlayerState::CLIMBING && playerState != PlayerState::HURT)
	{
		//velocity.x = 0;
		playerState = PlayerState::JUMPING;
		applyGravity = true;

		if (audioManager.getSound("jump")->getStatus() == sf::SoundSource::Stopped)
		{
			audioManager.playSoundbyName("jump"); // Play jump sound
		}
	}
}

// If player is colliding with a tile
void Player::collisionResponse(Tile* collider, float dt, Tile* aboveTile, Tile* belowTile, Controller &controller, AudioManager &audioManager)
{
	// If the tile is a ladder tile
	if (collider->getColliderType() == ColliderType::LADDER)
	{
		// If the player is below the ladder tile
		if ((getPosition().y + 32) >= collider->getPosition().y)
		{
			// Checks how close the player is to the ladder
			if (getPosition().x + (getSize().x / 2) >= collider->getPosition().x && getPosition().x + (getSize().x / 2) <= collider->getPosition().x + collider->getSize().x)
			{
				ladderCollision = true; // Player is colliding with ladder
				isColliding = true; // Player is colliding

				// Player is climbing up the ladder
				if ((input->isKeyDown(sf::Keyboard::W) || controller.getControllerState() & ControllerState::UP)
					&& getPlayerState() != PlayerState::JUMPING && getPlayerState() != PlayerState::HURT)
				{
					playerState = PlayerState::CLIMBING;

					velocity.x = 0;
					velocity.y = -0.5f * scale;
					move(velocity * dt);

					if (audioManager.getSound("climb")->getStatus() == sf::SoundSource::Stopped)
					{
						audioManager.playSoundbyName("climb"); // Play climb sound
					}

					// Checks the above tile, if it is not a ladder, stops player from climbing and sets to stand on top of ladder
					if (aboveTile->getColliderType() != ColliderType::LADDER)
					{
						if (getPosition().y <= aboveTile->getPosition().y + 10)
						{
							playerState = PlayerState::IDLE;

							velocity.y = 0;
							setPosition(getPosition().x, collider->getPosition().y - getSize().y);
						}
					}
				}
			}
		}

		// If the player is above the ladder tile
		else if (getPosition().y - 30 < collider->getPosition().y) // player above ladder
		{
			// Checks how close the player is to the ladder
			if (getPosition().x + (getSize().x / 2) >= collider->getPosition().x && getPosition().x + (getSize().x / 2) <= collider->getPosition().x + collider->getSize().x)
			{
				ladderCollision = true; // Player is colliding with ladder
				isColliding = true; // Player is colliding

				// Player is climbing down the ladder
				if ((input->isKeyDown(sf::Keyboard::S) || controller.getControllerState() & ControllerState::DOWN)
					&& getPlayerState() != PlayerState::HURT)
				{
					playerState = PlayerState::CLIMBING;

					velocity.x = 0;
					velocity.y = 0.5f * scale;
					move(velocity * dt);

					if (audioManager.getSound("climb")->getStatus() == sf::SoundSource::Stopped)
					{
						audioManager.playSoundbyName("climb"); // Play climb sound
					}

					// Checks the below tile, if it is not a ladder, stops player from climbing and sets to stand below the ladder
					if (belowTile->getColliderType() != ColliderType::LADDER)
					{
						if ((getPosition().y + getSize().y) >= belowTile->getPosition().y)

							playerState = PlayerState::IDLE;

						velocity.y = 0;
						setPosition(getPosition().x, belowTile->getPosition().y - getSize().y);
					}
				}
			}
		}
	}


	// If the tile is a platform tile
	if (playerState != PlayerState::CLIMBING && playerState != PlayerState::HURT && collider->getColliderType() == ColliderType::PLATFORM)
	{
		// If half of the player is above the platform
		if (getPosition().y + getSize().y / 2 < collider->getPosition().y)
		{
			// Checks how close the player is to the platform
			if (getPosition().x + (getSize().x / 2) >= collider->getPosition().x && getPosition().x + (getSize().x / 2) <= collider->getPosition().x + collider->getSize().x)
			{
				velocity.y = 0;
				isColliding = true;

				// Player is run shooting left
				if (((input->isKeyDown(sf::Keyboard::A) && input->isKeyDown(sf::Keyboard::K)) || ((controller.getControllerState() & (ControllerState::LEFT | ControllerState::X)) == (ControllerState::LEFT | ControllerState::X)))
					&& playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING && playerState != PlayerState::JUMPING)
				{
					playerState = PlayerState::RUNSHOOTING;
					playerDirection = PlayerDirection::LEFT;

					setVelocity(-350, 0);

					if (audioManager.getSound("run")->getStatus() == sf::SoundSource::Stopped)
					{
						audioManager.playSoundbyName("run"); // Play run sound
					}
				}

				// Player is run shooting right
				else if (((input->isKeyDown(sf::Keyboard::D) && input->isKeyDown(sf::Keyboard::K)) || ((controller.getControllerState() & (ControllerState::RIGHT | ControllerState::X)) == (ControllerState::RIGHT | ControllerState::X)))
					&& playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING && playerState != PlayerState::JUMPING)
				{
					playerState = PlayerState::RUNSHOOTING;
					playerDirection = PlayerDirection::RIGHT;

					setVelocity(350, 0);

					if (audioManager.getSound("run")->getStatus() == sf::SoundSource::Stopped)
					{
						audioManager.playSoundbyName("run"); // Play run sound
					}
				}

				// Player is running left
				else if ((input->isKeyDown(sf::Keyboard::A) || controller.getControllerState() & ControllerState::LEFT)
					&& playerState != PlayerState::JUMPING && playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING && playerState != PlayerState::RUNSHOOTING)
				{
					playerState = PlayerState::RUNNING;
					playerDirection = PlayerDirection::LEFT;

					setVelocity(-350, 0);

					if (audioManager.getSound("run")->getStatus() == sf::SoundSource::Stopped)
					{
						audioManager.playSoundbyName("run"); // Play run sound
					}
				}

				// Player is running right
				else if ((input->isKeyDown(sf::Keyboard::D) || controller.getControllerState() & ControllerState::RIGHT)
					&& playerState != PlayerState::JUMPING && playerState != PlayerState::HURT && playerState != PlayerState::CLIMBING && playerState != PlayerState::RUNSHOOTING)
				{
					playerState = PlayerState::RUNNING;
					playerDirection = PlayerDirection::RIGHT;

					setVelocity(350, 0);

					if (audioManager.getSound("run")->getStatus() == sf::SoundSource::Stopped)
					{
						audioManager.playSoundbyName("run"); // Play run sound
					}
				}

				// Player is crouching
				else if (input->isKeyDown(sf::Keyboard::S) || controller.getControllerState() & ControllerState::DOWN)
				{
					playerState = PlayerState::CROUCHING;
					velocity.x = 0;
				}

				// Player is shooting
				else if ((input->isKeyDown(sf::Keyboard::K) || controller.getControllerState() & ControllerState::X))
				{
					playerState = PlayerState::SHOOTING;

					velocity.x = 0;
					setPosition(getPosition().x, collider->getPosition().y - getSize().y);
				}

				// Player is idle
				else if (!ladderCollision)
				{
					playerState = PlayerState::IDLE;

					velocity = { 0, 0 };
					setPosition(getPosition().x, collider->getPosition().y - getSize().y);
				}
			}
		}
	}

	ladderCollision = false; // Reset ladder collision variable

}

// If player is colliding with a coin, add one to score
void Player::collisionResponse(Coin* collider)
{
	score += 1;
}

// If player is colliding with an enemy or bullets, make player hurt
void Player::collisionResponse(GameObject* collider, float dt, AudioManager &audioManager)
{
	if (playerState != PlayerState::HURT)
	{
			playerState = PlayerState::HURT;

			if (playerDirection == PlayerDirection::RIGHT)
			{
				velocity.x = -100;
			}

			else if (playerDirection == PlayerDirection::LEFT)
			{
				velocity.x = 100;
			}

			velocity.y = -3.f * scale;
			move(velocity * dt);

			if (audioManager.getSound("collide")->getStatus() == sf::SoundSource::Stopped)
			{
				audioManager.playSoundbyName("collide"); // Play collide sound
			}
		}
}

// Sets up the player animations
void Player::setUpAnimations()
{
	// Sets up Idle animation
	idle.addFrame(sf::IntRect(0, 268, 71, 67));
	idle.addFrame(sf::IntRect(71, 268, 71, 67));
	idle.addFrame(sf::IntRect(142, 268, 71, 67));
	idle.addFrame(sf::IntRect(213, 268, 71, 67));
	idle.setFrameSpeed(0.12f);

	// Sets up Run animation
	run.addFrame(sf::IntRect(0, 402, 71, 67));
	run.addFrame(sf::IntRect(71, 402, 71, 67));
	run.addFrame(sf::IntRect(142, 402, 71, 67));
	run.addFrame(sf::IntRect(213, 402, 71, 67));
	run.addFrame(sf::IntRect(284, 402, 71, 67));
	run.addFrame(sf::IntRect(355, 402, 71, 67));
	run.addFrame(sf::IntRect(426, 402, 71, 67));
	run.addFrame(sf::IntRect(497, 402, 71, 67));
	run.setFrameSpeed(0.12f);

	// Sets up Crouch animation
	crouch.addFrame(sf::IntRect(0, 134, 71, 67));

	// Sets up Climb animation
	climb.addFrame(sf::IntRect(0, 67, 71, 67));
	climb.addFrame(sf::IntRect(71, 67, 71, 67));
	climb.addFrame(sf::IntRect(142, 67, 71, 67));
	climb.addFrame(sf::IntRect(213, 67, 71, 67));
	climb.addFrame(sf::IntRect(284, 67, 71, 67));
	climb.addFrame(sf::IntRect(355, 67, 71, 67));
	climb.setFrameSpeed(0.18f);

	// Sets up Shoot animation
	shoot.addFrame(sf::IntRect(0, 536, 71, 67));

	// Sets up Run Shoot animation
	runShoot.addFrame(sf::IntRect(0, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(71, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(142, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(213, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(284, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(355, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(426, 469, 71, 67));
	runShoot.addFrame(sf::IntRect(497, 469, 71, 67));
	runShoot.setFrameSpeed(0.12f);

	// Sets up Jump animation
	jump.addFrame(sf::IntRect(0, 335, 71, 67));
	jump.addFrame(sf::IntRect(71, 335, 71, 67));
	jump.addFrame(sf::IntRect(142, 335, 71, 67));
	jump.addFrame(sf::IntRect(213, 335, 71, 67));
	jump.setFrameSpeed(0.2f);
	jump.setLooping(false);

	// Sets up Hurt animation
	hurt.addFrame(sf::IntRect(0, 201, 71, 67));
}

// Sets the correct animations for the player states
void Player::animations()
{
	switch (playerState)
	{
		case PlayerState::IDLE:
			jump.reset();
			currentAnimation = &idle;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;

		case PlayerState::RUNNING:
			currentAnimation = &run;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;

		case PlayerState::CROUCHING:
			currentAnimation = &crouch;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;

		case PlayerState::CLIMBING:
			currentAnimation = &climb;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;

		case PlayerState::SHOOTING:
			currentAnimation = &shoot;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;

		case PlayerState::JUMPING:
			currentAnimation = &jump;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = true;
			break;

		case PlayerState::RUNSHOOTING:
			currentAnimation = &runShoot;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;

		case PlayerState::HURT:
			currentAnimation = &hurt;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = true;
			break;

		default:
			currentAnimation = &idle;
			setTextureRect(currentAnimation->getCurrentFrame());
			applyGravity = false;
			break;
	}
}

// Plays the spawn animation
void Player::spawnAnimation()
{
	playerState = PlayerState::JUMPING;

	velocity.x = 150;
	velocity.y = -2.5f * scale;
}

// Deals with what way player is facing
void Player::directions()
{
	switch (playerDirection)
	{
		// If player is going left, flip them
		case PlayerDirection::LEFT:
		{
			currentAnimation->setFlipped(true);
			break;
		}

		// If player is going right, stop flipping them
		case PlayerDirection::RIGHT:
		{
			currentAnimation->setFlipped(false);
			break;
		}

		default:
		{
			break;
		}
	}
}

// Resets the player for a new game
void Player::resetPlayer(bool quit)
{
	// Sets the default animation to Idle
	currentAnimation = &idle;
	setTextureRect(currentAnimation->getCurrentFrame());

	// Initialises variables
	playerState = PlayerState::IDLE;
	playerDirection = PlayerDirection::RIGHT;
	animTimer = 0;
	score = 0;
	ladderCollision = false;
	isColliding = false;
	applyGravity = false;
	hasSpawned = false;

	if (quit)
	{
		deaths = 0;
	}
}


// Checks if any key is being pressed
bool Player::isAnyKeyPressed()
{
	for (int k = -1; k < sf::Keyboard::KeyCount; k++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
		{
			return true; // If key is pressed return true
		}
	}

	return false; // If key is not pressed return false
}

PlayerState Player::getPlayerState()
{
	return playerState;
}

PlayerDirection Player::getPlayerDirection()
{
	return playerDirection;
}

int Player::getScore()
{
	return score;
}

int Player::getDeaths()
{
	return deaths;
}