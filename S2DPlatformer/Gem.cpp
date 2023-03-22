#include "Gem.h"

#include "PlatformerGame.h"

const int Gem::PointValue = 30;
const Color* Gem::Color = Color::Green;

Gem::Gem(Level* level, Vector2* position)
	: _level(level), _basePosition(position)
{
	LoadContent();
}


Gem::~Gem(void)
{
	delete _texture;
    delete _origin;
    delete _collectedSound;
    delete _basePosition;
}

const Level* Gem::GetLevel() const
{
	return _level;
}

Vector2 Gem::GetPosition() const
{
	float time = PlatformerGame::TotalTime / 1000.0f;

	return *_basePosition + Vector2(time, _bounce);
}

Circle Gem::GetBoundingCircle() const
{
	return Circle(GetPosition(), Tile::Width / 3.0f);
}

void Gem::LoadContent()
{
	_texture = new Texture2D();
	_texture->Load("Content/Sprites/Gem.png", true);

	_origin = new Vector2(_texture->GetWidth() / 2.0f, _texture->GetHeight() / 2.0f);

	_collectedSound = new SoundEffect();
	_collectedSound->Load("Content/Sounds/GemCollected.wav");
}

void Gem::Update(int elapsedGameTime)
{
	// Bounce control constants
	const float BounceHeight = 0.18f;
	const float BounceRate = 3.0f;
	const float BounceSync = -0.75f;

	// Bounce along a sine curve over time.
	// Include the X coordinate so that neighboring gems bounce in a nice wave pattern.            
	double t = ((float)PlatformerGame::TotalTime / 1000.0f) * BounceRate + GetPosition().X * BounceSync;
	_bounce = (float)sin(t) * BounceHeight * _texture->GetHeight();
}

void Gem::OnCollected(Player* collectedBy)
{
	Audio::Play(_collectedSound);
}

void Gem::Draw(int elapsedGameTime)
{
	float time = ((float)PlatformerGame::TotalTime / 1000.0f);

	SpriteBatch::Draw(_texture, &(GetPosition()), nullptr, _origin, 1.0f, 0.0f, Color, SpriteEffect::NONE);
}