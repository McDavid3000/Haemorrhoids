#include "bloodparticle.h"
#include "backbuffer.h"

BloodParticle::BloodParticle()
{
}

BloodParticle::~BloodParticle()
{
}

bool BloodParticle::Initialise(BackBuffer * backBuffer)
{
	bool init = true;

	if (!Entity::Initialise(backBuffer->CreateSprite("..\\Game\\Assets\\Art\\bloodparticle.png")))
	{
		init = false;
	}
	return (init);
}

void BloodParticle::Process(float deltaTime)
{
	m_age--;
	Entity::Process(deltaTime);
}
