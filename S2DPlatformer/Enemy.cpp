#include "Enemy.h"

#include <cmath>

const float Enemy::MaxWaitTime = 0.5f;
const float Enemy::MoveSpeed = 64.0f;

Enemy::Enemy(Level* level, Vector2 position, std::string spriteSet)
	: _level(level), _position(position), _direction(FaceDirection::Left)
{
	LoadContent(spriteSet);
}


Enemy::~Enemy(void)
{
	delete _localBounds;
	delete _runAnimation;
	delete _idleAnimation;
}

const Level* Enemy::GetLevel() const
{
	return _level;
}

const Vector2* Enemy::GetPosition() const
{
	return &_position;
}

const Rect Enemy::GetBoundingRectangle() const
{
	float left = MathHelper::Round(_position.X - _sprite.GetOrigin().X) + _localBounds->X;
	float top = MathHelper::Round(_position.Y - _sprite.GetOrigin().Y) + _localBounds->Y;

	return Rect(left, top, _localBounds->Width, _localBounds->Height);
}

void Enemy::LoadContent(std::string spriteSet)
{
	spriteSet = "Content/Sprites/" + spriteSet + "/";

	Texture2D* run = new Texture2D();
	run->Load((spriteSet + "Run.png").c_str(), true);
	Texture2D* idle = new Texture2D();
	idle->Load((spriteSet + "Idle.png").c_str(), true);

	_runAnimation = new Animation(run, 0.1f, true);
	_idleAnimation = new Animation(idle, 0.15f, true);

	_sprite.PlayAnimation(*_idleAnimation);

	int width = (int)(_idleAnimation->GetFrameWidth() * 0.35);
    int left = (_idleAnimation->GetFrameWidth() - width) / 2;
    int Height = (int)(_idleAnimation->GetFrameWidth() * 0.7);
    int top = _idleAnimation->GetFrameHeight() - Height;
	_localBounds = new Rect((float)left, (float)top, width, Height);
}

void Enemy::Update(int elapsedGameTime)
{
    // Calculate tile position based on the side we are walking towards.
    float posX = _position.X + _localBounds->Width / 2 * (int)_direction;
    int tileX = (int)floor(posX / Tile::Width) - (int)_direction;
    int tileY = (int)floor(_position.Y / Tile::Height);

    if (_waitTime > 0)
    {
        // Wait for some amount of time.
        _waitTime = MathHelper::Max(0.0f, _waitTime - ((float)elapsedGameTime / 1000.0f));
        if (_waitTime <= 0.0f)
        {
            // Then turn around.
            _direction = (FaceDirection)(-(int)_direction);
        }
    }
    else
    {
        // If we are about to run into a wall or off a cliff, start waiting.
		if (_level->GetCollision(tileX + (int)_direction, tileY - 1) == TileCollision::Impassable ||
            _level->GetCollision(tileX + (int)_direction, tileY) == TileCollision::Passable)
        {
            _waitTime = MaxWaitTime;
        }
        else
        {
            // Move in the current direction.
            Vector2 velocity((int)_direction * MoveSpeed * ((float)elapsedGameTime / 1000.0f), 0.0f);
            _position = _position + velocity;
        }
    }
}

void Enemy::Draw(int elapsedGameTime)
{
	// Stop running when the game is paused or before turning around.
	if (!_level->GetPlayer()->IsAlive() ||
		_level->ReachedExit() ||
		_level->GetTimeRemaining() <= 0 ||
		_waitTime > 0)
	{
		_sprite.PlayAnimation(*_idleAnimation);
	}
	else
	{
		_sprite.PlayAnimation(*_runAnimation);
	}


	// Draw facing the way the enemy is moving.
	SpriteEffect flip = (int)_direction > 0 ? SpriteEffect::FLIPHORIZONTAL : SpriteEffect::NONE;
	_sprite.Draw(elapsedGameTime, _position, flip);
}