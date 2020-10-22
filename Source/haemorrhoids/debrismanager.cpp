#include "debrismanager.h"
#include "debris.h"
#include "backbuffer.h"
#include "logmanager.h"
#include "entity.h"
#include "pooparticleemitter.h"


#include <ctime> 

DebrisManager::DebrisManager()
	: m_arrLargeDebris()
	, m_arrMedDebris()
	, m_arrSmallDebris()
{
}

DebrisManager::~DebrisManager()
{
}

bool 
DebrisManager::Initialise(BackBuffer* backBuffer)
{
	bool init = true;

	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].Initialise(backBuffer->CreateSprite("..\\Game\\Assets\\Art\\largepoop.png")))
		{
			LogManager::GetInstance().Log("Large debris Init Fail!");
			init = false;
			return (init);
		}

		m_arrLargeDebris[i].SetDead(true);
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].Initialise(backBuffer->CreateSprite("..\\Game\\Assets\\Art\\medpoop.png")))
		{
			LogManager::GetInstance().Log("Med debris Init Fail!");
			init = false;
			return (init);
		}

		m_arrMedDebris[j].SetDead(true);
	}


	for (int k = 0; k < 24; k++)
	{
		if (!m_arrSmallDebris[k].Initialise(backBuffer->CreateSprite("..\\Game\\Assets\\Art\\smallpoop.png")))
		{
			LogManager::GetInstance().Log("Small debris Init Fail!");
			init = false;
			return (init);
		}

		m_arrSmallDebris[k].SetDead(true);
	}

	SpawnDebris(Size::Large, 2, 0, 0);

	return (init);
}

bool DebrisManager::DebrisWithinSpawnRadius()
{
	bool collision = false;

	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].IsDead())
		{
			if (WithinPlayerSpawnRadius(m_arrLargeDebris[i]))
			{
				collision = true;
			}
		}
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].IsDead())
		{
			if (WithinPlayerSpawnRadius(m_arrMedDebris[j]))
			{
				collision = true;

			}
		}
	}

	for (int j = 0; j < 24; j++)
	{
		if (!m_arrSmallDebris[j].IsDead())
		{
			if (WithinPlayerSpawnRadius(m_arrSmallDebris[j]))
			{
				collision = true;

			}
		}
	}

	return collision;
}

void 
DebrisManager::SpawnDebris(Size size, int number, float XLocation, float YLocation)
{
	if (number > 6)
	{
		number = 6;
	}

	if (size == Size::Large)
	{
		for (int i = 0; i < number; i++)
		{
			m_arrLargeDebris[i].SetDead(false);
			m_arrLargeDebris[i].SetVerticalVelocity((float((rand() % 100) - 50)));
			m_arrLargeDebris[i].SetHorizontalVelocity((float((rand() % 100) - 50)));
							   
			m_arrLargeDebris[i].SetAngle(float((rand() % 360)));
			
			//dont spawn on player
			do{
				m_arrLargeDebris[i].SetPosition((float(rand() % 800)), (float(rand() % 600)));
			} while (WithinPlayerSpawnRadius(m_arrLargeDebris[i]));
		}
	}
	
	else if (size == Size::Medium)
	{
		int index = 0;
		int counter = 0;

		while (counter != number)
		{
			if (m_arrMedDebris[index].IsDead())
			{
				m_arrMedDebris[index].SetDead(false);
				m_arrMedDebris[index].SetVerticalVelocity(float((rand() % 100) - 50));
				m_arrMedDebris[index].SetHorizontalVelocity(float((rand() % 100) - 50));
				m_arrMedDebris[index].SetAngle(float(rand() % 360));
				m_arrMedDebris[index].SetPosition(XLocation, YLocation);
				
				counter++;
			}

			index++;
		}
	}
	else if (size == Size::Small)
	{
		int index = 0;
		int counter = 0;

		while (counter != number)
		{
			if (m_arrSmallDebris[index].IsDead())
			{
				m_arrSmallDebris[index].SetDead(false);
				m_arrSmallDebris[index].SetVerticalVelocity(float((rand() % 100) - 50));
				m_arrSmallDebris[index].SetHorizontalVelocity(float((rand() % 100) - 50));
				m_arrSmallDebris[index].SetAngle(float(rand() % 360));
				m_arrSmallDebris[index].SetPosition(XLocation, YLocation);

				counter++;
			}

			index++;
		}
	}
}

std::vector<Entity*>
DebrisManager::CheckDebrisCollisionWithBullet(Entity& e)
{
	std::vector<Entity*> vecDebris; 

	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].IsDead())
		{
			if (m_arrLargeDebris[i].IsCollidingWith(e) && !e.IsDead())
			{
				m_arrLargeDebris[i].SetDead(true);
				e.SetDead(true);

				//spawn 2 smaller
				SpawnDebris(Size::Medium, 2, m_arrLargeDebris[i].GetPositionX(), m_arrLargeDebris[i].GetPositionY());

//				For CreateAPooParticles() method
				vecDebris.push_back(&m_arrLargeDebris[i]);
			}
		}
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].IsDead())
		{
			if (m_arrMedDebris[j].IsCollidingWith(e) && !e.IsDead())
			{
				m_arrMedDebris[j].SetDead(true);
				e.SetDead(true);

				vecDebris.push_back(&m_arrMedDebris[j]);

				//spawn two smaller
				SpawnDebris(Size::Small, 2, m_arrMedDebris[j].GetPositionX(), m_arrMedDebris[j].GetPositionY());
			}
		}
	}

	for (int j = 0; j < 24; j++)
	{
		if (!m_arrSmallDebris[j].IsDead())
		{
			if (m_arrSmallDebris[j].IsCollidingWith(e) && !e.IsDead())
			{
				m_arrSmallDebris[j].SetDead(true);
				e.SetDead(true);

				vecDebris.push_back(&m_arrSmallDebris[j]);

			}
		}
	}

	return vecDebris;
}

bool DebrisManager::CheckDebrisCollisionWithPlayer(Entity & e)
{
	bool collision = false;

	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].IsDead())
		{
			if (m_arrLargeDebris[i].IsCollidingWith(e) && !e.IsDead())
			{
				collision = true;
			}
		}
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].IsDead())
		{
			if (m_arrMedDebris[j].IsCollidingWith(e) && !e.IsDead())
			{
				collision = true;

			}
		}
	}

	for (int j = 0; j < 24; j++)
	{
		if (!m_arrSmallDebris[j].IsDead())
		{
			if (m_arrSmallDebris[j].IsCollidingWith(e) && !e.IsDead())
			{
				collision = true;

			}
		}
	}

	return collision;
}

void
DebrisManager::Process(float deltaTime)
{
	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].IsDead())
		{
			m_arrLargeDebris[i].Process(deltaTime);
		}
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].IsDead())
		{
			m_arrMedDebris[j].Process(deltaTime);
		}
	}

	for (int j = 0; j < 24; j++)
	{
		if (!m_arrSmallDebris[j].IsDead())
		{
			m_arrSmallDebris[j].Process(deltaTime);
		}
	}
}


void
DebrisManager::Draw(BackBuffer & backBuffer)
{
	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].IsDead())
		{
			m_arrLargeDebris[i].Draw(backBuffer);
		}
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].IsDead())
		{
			m_arrMedDebris[j].Draw(backBuffer);
		}
	}

	for (int j = 0; j < 24; j++)
	{
		if (!m_arrSmallDebris[j].IsDead())
		{
			m_arrSmallDebris[j].Draw(backBuffer);
		}
	}
}

bool
DebrisManager::AllDead()
{
	bool allDead = true;

	for (int i = 0; i < 6; i++)
	{
		if (!m_arrLargeDebris[i].IsDead())
		{
			allDead = false;
		}
	}

	for (int j = 0; j < 12; j++)
	{
		if (!m_arrMedDebris[j].IsDead())
		{
			allDead = false;
		}
	}

	for (int j = 0; j < 24; j++)
	{
		if (!m_arrSmallDebris[j].IsDead())
		{
			allDead = false;
		}
	}

	return allDead;
}

bool
DebrisManager::WithinPlayerSpawnRadius(Entity& e)
{
	bool colliding = false;

	if ((e.GetPositionY() + e.GetCentre().y)  > 180 && (e.GetPositionY() + e.GetCentre().y) < 400)
	{
		if ((e.GetPositionX() + e.GetCentre().y) > 300 && (e.GetPositionX() + e.GetCentre().y) < 500)
		{
			colliding = true;
		}
	}
	return colliding;
}

