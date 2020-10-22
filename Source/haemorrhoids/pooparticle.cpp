#include "pooparticle.h"
#include "backbuffer.h"

PooParticle::PooParticle()
{
}

PooParticle::~PooParticle()
{
}

bool PooParticle::Initialise(BackBuffer * backBuffer)
{
	bool init = true;

	if (!Entity::Initialise(backBuffer->CreateSprite("..\\Game\\Assets\\Art\\pooparticle.png")))
	{
		init = false;
	}
	return (init);
}

void PooParticle::Process(float deltaTime)
{
	m_age--;
	Entity::Process(deltaTime);
}
