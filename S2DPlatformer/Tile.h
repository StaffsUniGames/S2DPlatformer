#pragma once

#include "S2D\S2D.h"

using namespace S2D;

/// <summary>
/// Controls the collision detection and response behavior of a tile.
/// </summary>
enum class TileCollision
{
    /// <summary>
    /// A passable tile is one which does not hinder player motion at all.
    /// </summary>
    Passable = 0,

    /// <summary>
    /// An impassable tile is one which does not allow the player to move through
    /// it at all. It is completely solid.
    /// </summary>
    Impassable = 1,

    /// <summary>
    /// A platform tile is one which behaves like a passable tile except when the
    /// player is above it. A player can jump up through a platform as well as move
    /// past it to the left and right, but can not fall down through the top of it.
    /// </summary>
    Platform = 2,
};

struct Tile
{
public:
    Texture2D* Texture;
    TileCollision Collision;

    static const int Width;
    static const int Height;

    static const Vector2* Size;

    Tile(Texture2D* texture, TileCollision collision);
	~Tile(void);
};