#include "Player.h"
#include "RectangleExtensions.h"

#include "S2D\Input.h"

// Constants for controling horizontal movement
const float Player::MoveAcceleration = 13000.0f;
const float Player::MaxMoveSpeed = 1750.0f;
const float Player::GroundDragFactor = 0.48f;
const float Player::AirDragFactor = 0.58f;

// Constants for controlling vertical movement
const float Player::MaxJumpTime = 0.35f;
const float Player::JumpLaunchVelocity = -3500.0f;
const float Player::GravityAcceleration = 3400.0f;
const float Player::MaxFallSpeed = 550.0f;
const float Player::JumpControlPower = 0.14f; 

Player::Player(Level* level, Vector2* position)
	: _level(level)
{
	LoadContent();

	Reset(position);
}


Player::~Player(void)
{
	delete _idleAnimation;
    delete _runAnimation;
    delete _jumpAnimation;
    delete _celebrateAnimation;
    delete _dieAnimation;

    // Sounds
    delete _killedSound;
    delete _jumpSound;
    delete _fallSound;

	delete _position;
	delete _velocity;
	delete _localBounds;
}

Level* Player::GetLevel()
{
	return _level;
}

bool Player::IsAlive()
{
	return _isAlive;
}

bool Player::IsOnGround(){
	return _isOnGround;
}

Vector2* Player::GetPosition()
{
	return _position;
}

void Player::SetPosition(Vector2 position)
{
	*_position = position;
}

Vector2* Player::GetVelocity()
{
	return _velocity;
}

void Player::SetVelocity(Vector2 velocity)
{
	*_velocity = velocity;
}

void Player::ApplyPhysics(int elapsedGameTime)
{
	float elapsed = 0.016f;

    Vector2 previousPosition = *_position;

    // Base velocity is a combination of horizontal movement control and
    // acceleration downward due to gravity.
    _velocity->X += _movement * MoveAcceleration * elapsed;
    _velocity->Y = MathHelper::Clamp(_velocity->Y + GravityAcceleration * elapsed, -MaxFallSpeed, MaxFallSpeed);

    _velocity->Y = DoJump(_velocity->Y, elapsedGameTime);

    // Apply pseudo-drag horizontally.
    if (IsOnGround())
        _velocity->X *= GroundDragFactor;
    else
        _velocity->X *= AirDragFactor;

    // Prevent the player from running faster than his top speed.            
    _velocity->X = MathHelper::Clamp(_velocity->X, -MaxMoveSpeed, MaxMoveSpeed);

    // Apply velocity.
    *_position += (*_velocity * elapsed);
	_position->X = (float)MathHelper::Round(_position->X);
	_position->Y = (float)MathHelper::Round(_position->Y);

    // If the player is now colliding with the level, separate them.
    HandleCollisions();

    // If the collision stopped us from moving, reset the velocity to zero.
    if (_position->X == previousPosition.X)
        _velocity->X = 0;

    if (_position->Y == previousPosition.Y)
        _velocity->Y = 0;
}

void Player::Update(int elapsedGameTime)
{
	GetInput();

    ApplyPhysics(elapsedGameTime);

    if (IsAlive() && IsOnGround())
    {
        if (abs(_velocity->X) - 0.02f > 0)
        {
			_sprite.PlayAnimation(*_runAnimation);
        }
        else
        {
            _sprite.PlayAnimation(*_idleAnimation);
        }
    }

    // Clear input.
    _movement = 0.0f;
    _isJumping = false;
}

Rect Player::GetBoundingRectangle()
{
	float left = MathHelper::Round(_position->X - _sprite.GetOrigin().X) + _localBounds->X;
    float top = MathHelper::Round(_position->Y - _sprite.GetOrigin().Y) + _localBounds->Y;

	return Rect(left, top, _localBounds->Width, _localBounds->Height);
	
}

void Player::OnKilled(Enemy* killedBy)
{
	_isAlive = false;

    if (killedBy != nullptr)
		Audio::Play(_killedSound);
    else
        Audio::Play(_fallSound);

    _sprite.PlayAnimation(*_dieAnimation);
}

void Player::OnReachedExit()
{
	_sprite.PlayAnimation(*_celebrateAnimation);
}

void Player::Reset(Vector2* start)
{
	_position = start;
    _velocity = new Vector2();
    _isAlive = true;
    _sprite.PlayAnimation(*_idleAnimation);
}

void Player::Draw(int elapsedGameTime)
{
	// Flip the sprite to face the way we are moving.
	if (_velocity->X > 0)
		flip = SpriteEffect::FLIPHORIZONTAL;
	else
		flip = SpriteEffect::NONE;

	// Draw that sprite.
	_sprite.Draw(elapsedGameTime, *_position, flip);
}

void Player::LoadContent()
{
	Texture2D* tex = new Texture2D();
	tex->Load("Content/Sprites/Player/Idle.png", false);
	_idleAnimation = new Animation(tex, 0.1f, true);

	tex = new Texture2D();
	tex->Load("Content/Sprites/Player/Run.png", false);
	_runAnimation = new Animation(tex, 0.1f, true);
	
	tex = new Texture2D();
	tex->Load("Content/Sprites/Player/Jump.png", false);
	_jumpAnimation = new Animation(tex, 0.1f, false);
	
	tex = new Texture2D();
	tex->Load("Content/Sprites/Player/Celebrate.png", false);
	_celebrateAnimation = new Animation(tex, 0.1f, false);
	
	tex = new Texture2D();
	tex->Load("Content/Sprites/Player/Die.png", false);
	_dieAnimation = new Animation(tex, 0.1f, false);

	// Calculate bounds within texture size.            
	int width = (int)(_idleAnimation->GetFrameWidth() * 0.4);
	int left = (_idleAnimation->GetFrameWidth() - width) / 2;
	int Height = (int)(_idleAnimation->GetFrameWidth() * 0.8);
	int top = _idleAnimation->GetFrameHeight() - Height;
	_localBounds = new Rect((float)left, (float)top, width, Height);

	// Load sounds.            
	_killedSound = new SoundEffect();
	_killedSound->Load("Content/Sounds/PlayerKilled.wav");

	_jumpSound = new SoundEffect();
	_jumpSound->Load("Content/Sounds/PlayerJump.wav");

	_fallSound = new SoundEffect();
	_fallSound->Load("Content/Sounds/PlayerFall.wav");
}

void Player::HandleCollisions()
{
	// Get the player's bounding rectangle and find neighboring tiles.
    Rect bounds = GetBoundingRectangle();
    int leftTile = (int)floorf((float)bounds.Left() / Tile::Width);
    int rightTile = (int)ceilf(((float)bounds.Right() / Tile::Width)) - 1;
    int topTile = (int)floorf((float)bounds.Top() / Tile::Height);
    int bottomTile = (int)ceilf(((float)bounds.Bottom() / Tile::Height)) - 1;

    // Reset flag to search for ground collision.
    _isOnGround = false;

    // For each potentially colliding tile,
    for (int y = topTile; y <= bottomTile; ++y)
    {
        for (int x = leftTile; x <= rightTile; ++x)
        {
            // If this tile is collidable,
            TileCollision collision = _level->GetCollision(x, y);
            if (collision != TileCollision::Passable)
            {
                // Determine collision depth (with direction) and magnitude.
                Rect tileBounds = _level->GetBounds(x, y);
                Vector2 depth = RectangleExtensions::GetIntersectionDepth(&bounds, &tileBounds);
                if (depth != *Vector2::Zero)
                {
                    float absDepthX = abs(depth.X);
                    float absDepthY = abs(depth.Y);

                    // Resolve the collision along the shallow axis.
                    if (absDepthY < absDepthX || collision == TileCollision::Platform)
                    {
                        // If we crossed the top of a tile, we are on the ground.
                        if (_previousBottom <= tileBounds.Top())
                            _isOnGround = true;

                        // Ignore platforms, unless we are on the ground.
                        if (collision == TileCollision::Impassable || IsOnGround())
                        {
                            // Resolve the collision along the Y axis.
                            _position = new Vector2(_position->X, _position->Y + depth.Y);

                            // Perform further collisions with the new bounds.
                            bounds = GetBoundingRectangle();
                        }
                    }
                    else if (collision == TileCollision::Impassable) // Ignore platforms.
                    {
                        // Resolve the collision along the X axis.
                        _position = new Vector2(_position->X + depth.X, _position->Y);

                        // Perform further collisions with the new bounds.
                        bounds = GetBoundingRectangle();
                    }
                }
            }
        }
    }

    // Save the new bounds bottom.
    _previousBottom = bounds.Bottom();
}

void Player::GetInput()
{
	Input::KeyboardState* state = Input::Keyboard::GetState();

    // If any digital horizontal movement input is found, override the analog movement.
    if (state->IsKeyDown(Input::Keys::A))
    {
        _movement = -1.0f;
    }
    else if (state->IsKeyDown(Input::Keys::D))
    {
        _movement = 1.0f;
    }
	else
	{
		_movement = 0.0f;
	}

    // Check if the player wants to jump.
	_isJumping = state->IsKeyDown(Input::Keys::SPACE) || state->IsKeyDown(Input::Keys::W);
}

float Player::DoJump(float velocityY, int elapsedGameTime)
{
	// If the player wants to jump
    if (_isJumping)
    {
        // Begin or continue a jump
        if ((!_wasJumping && IsOnGround()) || _jumpTime > 0.0f)
        {
            if (_jumpTime == 0.0f)
				Audio::Play(_jumpSound);

			_jumpTime += (float)elapsedGameTime / 1000.0f;
            _sprite.PlayAnimation(*_jumpAnimation);
        }

        // If we are in the ascent of the jump
        if (0.0f < _jumpTime && _jumpTime <= MaxJumpTime)
        {
            // Fully override the vertical velocity with a power curve that gives players more control over the top of the jump
            velocityY = JumpLaunchVelocity * (1.0f - (float)pow(_jumpTime / MaxJumpTime, JumpControlPower));
        }
        else
        {
            // Reached the apex of the jump
            _jumpTime = 0.0f;
        }
    }
    else
    {
        // Continues not jumping or cancels a jump in progress
        _jumpTime = 0.0f;
    }
    _wasJumping = _isJumping;

    return velocityY;
}