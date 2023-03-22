#pragma once

#include "S2D/S2D.h"

using namespace S2D;

class Animation
{
public:
	Animation(Texture2D* texture, float frameTime, bool isLooping);
	~Animation(void);

	const Texture2D* GetTexture() const;
	const float GetFrameTime() const;
	const bool IsLooping() const;
	const int GetFrameCount() const;
	const int GetFrameWidth() const;
	const int GetFrameHeight() const;

private:
	Texture2D* _texture;
	float _frameTime;
	bool _isLooping;

};

