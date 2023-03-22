#pragma once

#include "Animation.h"
#include "AnimationPlayer.h"
#include "Level.h"
#include "Tile.h"

#include "S2D\S2D.h"

#include <string>

using namespace S2D;

enum class FaceDirection
{
	Left = -1,
	Right = 1
};

class Level;
class Animation;
class AnimationPlayer;

class Enemy
{

public:
	Enemy(Level* level, Vector2 position, std::string spriteSet);
	~Enemy(void);

	void LoadContent(std::string spriteSet);
	void Update(int elapsedGameTime);
	void Draw(int elapsedGameTime);

	const Level* GetLevel() const;
	const Vector2* GetPosition() const;
	const Rect GetBoundingRectangle() const;

private:
	Level* _level;
	Vector2 _position;
	Rect* _localBounds;

	Animation* _runAnimation;
	Animation* _idleAnimation;
	AnimationPlayer _sprite;

	FaceDirection _direction;

	float _waitTime;
	static const float MaxWaitTime;
	static const float MoveSpeed;
};

