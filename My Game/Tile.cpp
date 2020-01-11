#include "Tile.h"


Tile::Tile()
{
}

Tile::~Tile()
{
}


ColliderType Tile::getColliderType()
{
	return colliderType;
}

void Tile::setColliderType(ColliderType ct)
{
	colliderType = ct;
}