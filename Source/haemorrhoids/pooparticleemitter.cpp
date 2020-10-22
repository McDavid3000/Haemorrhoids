#include "pooparticleemitter.h"
#include "backbuffer.h"
#include <ctime> 

PooParticleEmitter::PooParticleEmitter()
{
}

PooParticleEmitter::~PooParticleEmitter()
{

}


//should be boolb
void
PooParticleEmitter::InitialiseParticles(BackBuffer* backBuffer)
{
	bool init;
	for (int i = 0; i < 15; i++)
	{
		if (!m_arrPooParticles[i].Initialise(backBuffer))
		{
			init = false;
		}
	}
}


void
PooParticleEmitter::Process(float deltaTime)
{

	for (int i = 0; i < 15; i++)
	{
		m_arrPooParticles[i].Process(deltaTime);
		m_arrPooParticles[i].SetAge(m_arrPooParticles[i].m_age--);
		m_arrPooParticles[i].SetAlpha(m_arrPooParticles[i].m_age);

		if (m_arrPooParticles[i].GetPositionX() == 800 || m_arrPooParticles[i].GetPositionX() == 0
			|| m_arrPooParticles[i].GetPositionY() == 600 || m_arrPooParticles[i].GetPositionY() == 0 || m_arrPooParticles[i].m_age <= 0)
		{
			m_arrPooParticles[i].SetDead(true);
		}
	}
}

void
PooParticleEmitter::Draw(BackBuffer &backBuffer)
{
	for (int i = 0; i < 15; i++)
	{
		m_arrPooParticles[i].Draw(backBuffer);
	}
}

void 
PooParticleEmitter::SpawnParticles(float x, float y, float velx, float vely)
{
	//randomly generate the number of particles

	int numParticles = (rand() % 15);

	for (int i = 0; i < numParticles; i++)
	{
		if (!m_arrPooParticles[i].IsDead())
		{
			m_arrPooParticles[i].SetVerticalVelocity(velx + ((rand() % 100) - 50));
			m_arrPooParticles[i].SetHorizontalVelocity(vely + ((rand() % 100) - 50));
			m_arrPooParticles[i].SetPosition((x + 4), y);
			m_arrPooParticles[i].SetAge(255);
		}
	}
}
