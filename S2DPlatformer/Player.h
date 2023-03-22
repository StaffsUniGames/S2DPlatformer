#pragma once

#include "Level.h"
#include "Enemy.h"
#include "Animation.h"
#include "AnimationPlayer.h"

#include "S2D\S2D.h"

class Level;
class Enemy;
class Animation;
class AnimationPlayer;

using namespace S2D;

class Player
{
private:
	Animation* _idleAnimation;
    Animation* _runAnimation;
    Animation* _jumpAnimation;
    Animation* _celebrateAnimation;
    Animation* _dieAnimation;
    SpriteEffect flip;
    AnimationPlayer _sprite;

    // Sounds
    SoundEffect* _killedSound;
    SoundEffect* _jumpSound;
    SoundEffect* _fallSound;

	Level* _level;

	bool _isAlive;
	
	Vector2* _position;

    float _previousBottom;

	Vector2* _velocity;

    // Constants for controling horizontal movement
    static const float MoveAcceleration;
    static const float MaxMoveSpeed;
    static const float GroundDragFactor;
    static const float AirDragFactor;

    // Constants for controlling vertical movement
    static const float MaxJumpTime;
    static const float JumpLaunchVelocity;
    static const float GravityAcceleration;
    static const float MaxFallSpeed;
    static const float JumpControlPower; 

    // Input configuration
    static const float MoveStickScale;
    static const float AccelerometerScale;        
	
	bool _isOnGround;

    /// <summary>
    /// Current user movement input.
    /// </summary>
    float _movement;

    // Jumping state
    bool _isJumping;
    bool _wasJumping;
    float _jumpTime;

    Rect* _localBounds;

public:
	Player(Level* level, Vector2* position);
	~Player(void);

	Level* GetLevel();
	Vector2* GetPosition();
	void SetPosition(Vector2 position);
	Vector2* GetVelocity();
	void SetVelocity(Vector2 velocity);

	bool IsAlive();
	bool IsOnGround();
	void ApplyPhysics(int elapsedGameTime);
	void Update(int elapsedGameTime);
	void Reset(Vector2* start);
	void Draw(int elapsedGameTime);
	void LoadContent();
	void HandleCollisions();

	Rect GetBoundingRectangle();

	void OnKilled(Enemy* killedBy);
	void OnReachedExit();

	void GetInput();
	float DoJump(float velocityY, int elapsedGameTime);
};

