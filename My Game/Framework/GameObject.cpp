#include "GameObject.h"

GameObject::GameObject()
{
	input = nullptr;
}

GameObject::~GameObject()
{

}

// Override this function to provide input handling for the derived class
void GameObject::handleInput(float dt)
{
}

// override this function to provide functionality
void GameObject::update(float dt)
{
}

// Sets the velocity of the sprite
void GameObject::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}
void GameObject::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

// get sprite velocity
sf::Vector2f GameObject::getVelocity()
{
	return velocity;
}

// Returns collision box + position, giving the collision box in the correct position
sf::FloatRect GameObject::getCollisionBox() {
	
	return sf::FloatRect(collisionBox.left + getPosition().x, collisionBox.top + getPosition().y, collisionBox.width, collisionBox.height); 
}

// Reponse function, what the sprite does based on collision
// Colliding object is passed in for information
// e.g. compare sprite positions to determine new velocity direction.
// e.g. checking sprite type (world, enemy, bullet etc) so response is based on that.
void GameObject::collisionResponse(GameObject * collider)
{
}

// Function I added to check whether an object is visible on screen
bool GameObject::getVisible(sf::View view)
{
	if (getPosition().x + getSize().x >= view.getCenter().x - (view.getSize().x / 2) && // left
		getPosition().x - getSize().x <= view.getCenter().x + (view.getSize().x / 2) && // right
		getPosition().y + getSize().y >= view.getCenter().y - (view.getSize().y / 2) && // top
		getPosition().y - getSize().y <= view.getCenter().y + (view.getSize().y / 2)) // bottom
	{
		visible = true;
	}

	else
	{
		visible = false;
	}

	return visible;
}
