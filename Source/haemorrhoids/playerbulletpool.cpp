#include "playerbulletpool.h"
#include <cmath>
#include "backbuffer.h"
#include "playership.h"

PlayerBulletPool::PlayerBulletPool()
{
}

PlayerBulletPool::~PlayerBulletPool()
{
}

bool 
PlayerBulletPool::Initialise(BackBuffer* backBuffer)
{
	m_nextBullet = 0;
	bool init = true;

	for (int i = 0; i < 10; i++)
	{
		if (!m_arrBulletPool[i].Initialise(backBuffer->CreateSprite("..\\Game\\Assets\\Art\\playerbullet.png")))
		{
			init = false;
		}

		m_arrBulletPool[i].SetDead(true);
	}

	return init;
}

void
PlayerBulletPool::GetNextBullet(Playership* ship)
{
	float pi = 3.14159265359f;

	m_arrBulletPool[m_nextBullet].SetDead(false);
	m_arrBulletPool[m_nextBullet].SetPosition(ship->GetPositionX(), ship->GetPositionY());
	m_arrBulletPool[m_nextBullet].SetOrigin(ship->GetPositionX(), ship->GetPositionY());
	m_arrBulletPool[m_nextBullet].SetHorizontalVelocity(sin(ship->GetAngle()*(pi / 180)) * 150);
	m_arrBulletPool[m_nextBullet].SetVerticalVelocity(-cos(ship->GetAngle()*(pi / 180)) * 150);
	m_arrBulletPool[m_nextBullet].SetAngle(ship->GetAngle());

	if (m_nextBullet != 9)
	{
		m_nextBullet++;
	}
	else
	{
		m_nextBullet = 0;
	}
}

void 
PlayerBulletPool::ProcessBullets(float deltaTime)
{
	for (int i = 0; i < 10; i++)
	{
		if (!m_arrBulletPool[i].IsDead())
		{
			m_arrBulletPool[i].Process(deltaTime);
			CheckBulletInRange(&m_arrBulletPool[i]);
		}
	}
}

void
PlayerBulletPool::DrawBullets(BackBuffer& backBuffer)
{
	for (int i = 0; i < 10; i++)
	{
		if (!m_arrBulletPool[i].IsDead())
		{
			m_arrBulletPool[i].Draw(backBuffer);
		}
	}
}

PlayerBullet*
PlayerBulletPool::GetBullets()
{
	return m_arrBulletPool;
}

void 
PlayerBulletPool::CheckBulletInRange(PlayerBullet* playerBullet)
{
	float x = abs((playerBullet->GetPositionX()) - abs(playerBullet->GetOrigin().x));
	float y = abs((playerBullet->GetPositionY()) - abs(playerBullet->GetOrigin().y));

	float hypotenuse = hypot(x, y);

	if (hypotenuse > 150)
	{
		playerBullet->SetDead(true);
	}
}








