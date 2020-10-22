#include "smokeanimation.h"
#include "animatedsprite.h"
#include <cassert>
#include "backbuffer.h"

SmokeAnimation::SmokeAnimation()
	: Entity()
{
}

SmokeAnimation::~SmokeAnimation()
{
	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

bool
SmokeAnimation::Initialise(AnimatedSprite* animatedSprite)
{
	m_pAnimatedSprite = animatedSprite;

	assert(m_pAnimatedSprite);

	m_pAnimatedSprite->SetFrameWidth(32);
	m_pAnimatedSprite->SetFrameSpeed(.10f);

	m_pAnimatedSprite->AddFrame(0);
	m_pAnimatedSprite->AddFrame(32);
	m_pAnimatedSprite->AddFrame(64);
	m_pAnimatedSprite->AddFrame(96);

	m_pAnimatedSprite->SetLooping(true);

	m_pAnimatedSprite->StartAnimating();

	SetPositionX(400);
	SetPositionY(332);
	m_pAnimatedSprite->SetX(400);
	m_pAnimatedSprite->SetY(332);

	return (true);
}

void 
SmokeAnimation::Process(float deltaTime)
{
	m_pAnimatedSprite->SetX(int(m_position.x));
	m_pAnimatedSprite->SetY(int(m_position.y));
	m_pAnimatedSprite->Process(deltaTime);
	if (!m_pAnimatedSprite->IsAnimating())
	{
		this->SetDead(true);
	}
}


void
SmokeAnimation::Draw(BackBuffer& backBuffer, int centreX, int centreY)
{
	if (m_pAnimatedSprite->IsAnimating() && !IsDead())
	{
		m_pAnimatedSprite->DrawRotatingSprite(backBuffer, centreX, centreY);
	}
}

void 
SmokeAnimation::SetAnimation(bool set)
{
	m_pAnimatedSprite->StartAnimating();
}

void 
SmokeAnimation::SetAngle(float angle)
{
	m_pAnimatedSprite->SetAngle(angle);
}







