#ifndef _SMOKEANIMATION_H_
#define _SMOKEANIMATION_H_

#include "entity.h"

class AnimatedSprite;
class BackBuffer;

class SmokeAnimation : public Entity
{
	//member methods
public:
	SmokeAnimation();
	~SmokeAnimation();

	bool Initialise(AnimatedSprite* animatedSprite);

	void Process(float deltaTime);
	void Draw(BackBuffer & backBuffer, int centreX, int centreY);

	void SetAnimation(bool set);

	void SetAngle(float angle);

protected:

private:

	//member data
public:
	AnimatedSprite* m_pAnimatedSprite;

protected:

private:

};

#endif _SMOKEANIMATION_H_