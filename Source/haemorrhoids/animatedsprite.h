#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"
#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void DrawRotatingSprite(BackBuffer & backbuffer, int centreX, int centreY);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);
	int GetFrameWidth();
	int GetFrameX();

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();
	bool HasAnimated();

	bool IsLooping();
	void SetLooping(bool b);

protected:

private:

	// Fields:
public:
	bool m_animating;
	bool m_hasAnimated;
	bool m_paused;

protected:
	std::vector<int> m_vecFrameContainer;

	float m_frameSpeed;
	int m_frameWidth;

	float m_timeElapsed;
	unsigned int m_currentFrame;

	bool m_loop;


private:

};

#endif // __ANIMATEDSPRITE_H__
