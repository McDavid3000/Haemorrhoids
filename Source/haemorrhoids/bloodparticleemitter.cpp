#include "bloodparticleemitter.h"
#include "backbuffer.h"

BloodParticleEmitter::BloodParticleEmitter()
{
}

BloodParticleEmitter::~BloodParticleEmitter()
{
}

void 
BloodParticleEmitter::InitialiseParticles(BackBuffer* backBuffer)
{
	bool init;

	m_blooPartArrSize = sizeof(m_arrBloodParticles) / sizeof(m_arrBloodParticles[0]);

	for (int i = 0; i < m_blooPartArrSize; i++)
	{
		if (!m_arrBloodParticles[i].Initialise(backBuffer))
		{
			init = false;
		}
	}
}

void
BloodParticleEmitter::Process(float deltaTime)
{

	for (int i = 0; i < m_blooPartArrSize; i++)
	{
		m_arrBloodParticles[i].Process(deltaTime);
		m_arrBloodParticles[i].SetAge(m_arrBloodParticles[i].m_age--);
		m_arrBloodParticles[i].SetAlpha(m_arrBloodParticles[i].m_age);

		if (m_arrBloodParticles[i].GetPositionX() == 800 || m_arrBloodParticles[i].GetPositionX() == 0
			|| m_arrBloodParticles[i].GetPositionY() == 600 || m_arrBloodParticles[i].GetPositionY() == 0 || m_arrBloodParticles[i].m_age <= 0)
		{
			m_arrBloodParticles[i].SetDead(true);
		}
	}
}

void
BloodParticleEmitter::Draw(BackBuffer &backBuffer)
{
	for (int i = 0; i < m_blooPartArrSize; i++)
	{
		m_arrBloodParticles[i].Draw(backBuffer);
	}
}

void 
BloodParticleEmitter::SpawnParticles(float x, float y, float velx, float vely)
{
	//randomly generate the number of particles

	int numParticles = (rand() % 20) + 80;

	for (int i = 0; i < numParticles; i++)
	{
		if (!m_arrBloodParticles[i].IsDead())
		{
			m_arrBloodParticles[i].SetVerticalVelocity(velx + ((rand() % 100) - 50));
			m_arrBloodParticles[i].SetHorizontalVelocity(vely + ((rand() % 100) - 50));
			m_arrBloodParticles[i].SetPosition((x + 4), y);
			m_arrBloodParticles[i].SetAge(255);
		}
	}
}

