#pragma once

#include "S2D\S2D.h"

#include "Animation.h"

using namespace S2D;

class Animation;

class AnimationPlayer
{
public:
	AnimationPlayer(void);
	~AnimationPlayer(void);

	const Animation* GetAnimation() const;
	const int GetFrameIndex() const;
	const Vector2 GetOrigin() const;

	void PlayAnimation(Animation& animation);
	void Draw(int elapsedGameTime, Vector2& position, SpriteEffect& spriteEffects);

private:
	Animation* _animation;
	int _frameIndex;
	float _time;

};

