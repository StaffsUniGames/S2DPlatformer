#include "Animation.h"


Animation::Animation(Texture2D* texture, float frameTime, bool isLooping)
	: _texture(texture), _frameTime(frameTime), _isLooping(isLooping)
{
}


Animation::~Animation(void)
{
	delete _texture;
}

const Texture2D* Animation::GetTexture() const
{
	return _texture;
}

const float Animation::GetFrameTime() const
{
	return _frameTime;
}

const bool Animation::IsLooping() const
{
	return _isLooping;
}

const int Animation::GetFrameCount() const
{
	return _texture->GetWidth() / _texture->GetHeight();
}

const int Animation::GetFrameWidth() const
{
	return _texture->GetHeight();
}

const int Animation::GetFrameHeight() const
{
	return _texture->GetHeight();
}