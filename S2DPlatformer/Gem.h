#pragma once

#include "S2D\S2D.h"

#include "Level.h"
#include "Circle.h"
#include "Player.h"
#include "Tile.h"

using namespace S2D;

class Player;
class Level;
class Circle;

class Gem
{
public:
	static const int PointValue;
    static const Color* Color;

	Gem(Level* level, Vector2* position);
	~Gem(void);

	const Level* GetLevel() const;

	Vector2 GetPosition() const;
	Circle GetBoundingCircle() const;

	void LoadContent();
	void Update(int elapsedGameTime);
	void OnCollected(Player* collectedBy);
	void Draw(int elapsedGameTime);

private:
	Texture2D* _texture;
    Vector2* _origin;
    SoundEffect* _collectedSound;

    // The gem is animated from a base position along the Y axis.
    Vector2* _basePosition;
    float _bounce;

	Level* _level;
};

