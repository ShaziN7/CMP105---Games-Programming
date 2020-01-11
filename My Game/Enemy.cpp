#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}


sf::Vector2f Enemy::getSpawnPoint()
{
	return spawnPoint; // Gets enemy spawn point
}

void Enemy::setSpawnPoint(sf::Vector2f sp)
{
	spawnPoint = sp; // Sets enemy spawn point
}

void Enemy::setColliderType(ColliderType ct)
{
	colliderType = ct; // Sets enemy collider type
}