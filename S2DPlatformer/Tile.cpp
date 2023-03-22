#include "Tile.h"

const int Tile::Width = 40;
const int Tile::Height = 32;

const Vector2* Tile::Size = new Vector2((float)Width, (float)Height);

Tile::Tile(Texture2D* texture, TileCollision collision)
{
    Texture = texture;
    Collision = collision;
}

Tile::~Tile(void)
{
	delete Texture;
}
