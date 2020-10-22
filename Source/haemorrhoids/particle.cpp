#include "particle.h"
#include "backbuffer.h"
#include "sprite.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void 
Particle::Process(float deltaTime)
{
	m_age--;
	Entity::Process(deltaTime);
}

void 
Particle::Draw(BackBuffer &backBuffer)
{
	Entity::Draw(backBuffer);
}

void 
Particle::SetAge(int age)
{
	m_age = age;
}

void Particle::SetAlpha(unsigned char alpha)
{
	m_pSprite->SetAlpha(alpha);
}

unsigned char Particle::GetAlpha()
{
	return m_pSprite->GetAlpha();
}



