#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(void)
{
	_animation = nullptr;
}


AnimationPlayer::~AnimationPlayer(void)
{
}

const Animation* AnimationPlayer::GetAnimation() const
{
	return _animation;
}

const int AnimationPlayer::GetFrameIndex() const
{
	return _frameIndex;
}

const Vector2 AnimationPlayer::GetOrigin() const
{
	return Vector2(_animation->GetFrameWidth() / 2.0f, (float)_animation->GetFrameHeight());
}

void AnimationPlayer::PlayAnimation(Animation& animation)
{
	if (_animation == &animation)
		return;

	this->_animation = &animation;
	this->_frameIndex = 0;
	this->_time = 0.0f;
}

void AnimationPlayer::Draw(int elapsedGameTime, Vector2& position, SpriteEffect& spriteEffect)
{
	if (_animation == nullptr)
		return;

	_time += (float)elapsedGameTime / 1000.0f;

	while (_time > _animation->GetFrameTime())
	{
		_time -= _animation->GetFrameTime();

		if (_animation->IsLooping())
		{
			_frameIndex = (_frameIndex + 1) % _animation->GetFrameCount();
		}
		else
		{
			_frameIndex = MathHelper::Min(_frameIndex + 1, _animation->GetFrameCount() - 1);
		}
	}
		Rect source((float)(_frameIndex * _animation->GetTexture()->GetHeight()), 0.0f, _animation->GetTexture()->GetHeight(), _animation->GetTexture()->GetHeight());

		SpriteBatch::Draw(_animation->GetTexture(), &position, &source, &(this->GetOrigin()), 1.0f, 0.0f, Color::White, spriteEffect);
}