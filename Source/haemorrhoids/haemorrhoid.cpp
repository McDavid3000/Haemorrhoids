#include "haemorrhoid.h"
#include "sprite.h"
#include <assert.h>
#include "animatedsprite.h"

#include <cmath>
#include <assert.h>

Haemorrhoid::Haemorrhoid()
	: Entity()
{
}

Haemorrhoid::~Haemorrhoid()
{
	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

bool
Haemorrhoid::Initialise(AnimatedSprite* animatedSprite)
{
	assert(animatedSprite);

	m_pAnimatedSprite = animatedSprite;

	m_pAnimatedSprite->SetCenter(60,60);


	m_pAnimatedSprite->SetFrameWidth(120);
	m_pAnimatedSprite->SetFrameSpeed(.10f);

	m_pAnimatedSprite->AddFrame(0);
	m_pAnimatedSprite->AddFrame(120);
	m_pAnimatedSprite->AddFrame(240);
	m_pAnimatedSprite->AddFrame(360);
	m_pAnimatedSprite->AddFrame(480);

	m_pAnimatedSprite->SetLooping(false);

	//no good need to override
	SetPositionX(0);
	SetPositionY(0);
	m_pAnimatedSprite->SetAngle(float(rand() % 360));

	return true;
}

void
Haemorrhoid::Spawn()
{
	SetDead(false);
	m_health = 10;

	m_pAnimatedSprite->m_paused = false;
	m_pAnimatedSprite->m_hasAnimated = false;
	m_pAnimatedSprite->m_animating = false;

	//dont spawn on player
	do
	{
		float x = float(rand() % 680);
		float y = float(rand() % 480);
		SetPosition(x, y);
	} while (WithinPlayerSpawnRadius());
}

bool 
Haemorrhoid::CheckCollision(Entity& e)
{
	bool collision = false;

	if (!this->IsDead())
	{
		if (this->IsCollidingWith(e))
		{
			e.SetDead(true);
			m_health--;
			collision = true;
		}

		if (m_health <= 0)
		{
 			if (!m_pAnimatedSprite->IsAnimating())
			{
				m_pAnimatedSprite->StartAnimating();
				this->SetDead(true);
			}
		}
	}

	return collision;
}

void
Haemorrhoid::SetHealth(int health)
{
	m_health = health;
}

int
Haemorrhoid::GetHealth()
{
	return m_health;
}

bool
Haemorrhoid::WithinPlayerSpawnRadius()
{
	bool colliding = false;

	if ((this->GetPositionY() + this->GetCentre().y) > 150 && (this->GetPositionY() + this->GetCentre().y) < 450)
	{
		if ((this->GetPositionX() + this->GetCentre().y) > 250 && (this->GetPositionX() + this->GetCentre().y) < 550)
		{
			colliding = true;
		}
	}

	return colliding;
}

void 
Haemorrhoid::SetAnimation(bool set)
{
	m_pAnimatedSprite->StartAnimating();
}

void
Haemorrhoid::Draw(BackBuffer& backBuffer)
{
	assert(m_pAnimatedSprite); 

	m_pAnimatedSprite->SetX(static_cast<int>(m_position.x));
	m_pAnimatedSprite->SetY(static_cast<int>(m_position.y));

	if (!this->m_pAnimatedSprite->HasAnimated())
	{
		m_pAnimatedSprite->DrawRotatingSprite(backBuffer, 0, 0);
	}
}

bool
Haemorrhoid::IsCollidingWith(Entity& e)
{
	bool colliding = false;

	struct Circle
	{
		float px;
		float py;
		float radius;
	};

	Circle thisCircle;
	Circle eCircle;

	thisCircle.radius = float(m_pAnimatedSprite->GetCenterX());
	eCircle.radius = float(e.GetCentre().x);

	float x = (GetPositionX() + m_pAnimatedSprite->GetCenterX()) - (e.GetPositionX() + e.GetCentre().x);
	float y = (GetPositionY() + m_pAnimatedSprite->GetCenterY()) - (e.GetPositionY() + e.GetCentre().x);

	float hypotenuse = hypot(x, y);

	if ((thisCircle.radius + eCircle.radius) >= hypotenuse)
	{
		colliding = true;
	}

	return colliding;

	return colliding;
}

void
Haemorrhoid::SetAngle(float angle)
{
	m_pAnimatedSprite->SetAngle(angle);
}

float
Haemorrhoid::GetAngle()
{
	return m_pAnimatedSprite->GetAngle();
}

void
Haemorrhoid::SetAlpha(unsigned char alpha)
{
	m_pAnimatedSprite->SetAlpha(alpha);

	if (alpha <= 0)
	{
		m_blendedOut = true;
	}
}

unsigned char
Haemorrhoid::GetAlpha()
{
	return m_pAnimatedSprite->GetAlpha();
}

Vector2 
Haemorrhoid::GetCentre()
{
 	m_centre.x = float(m_pAnimatedSprite->GetCenterX());
	m_centre.y = float(m_pAnimatedSprite->GetCenterY());

	return m_centre;
}

void
Haemorrhoid::Process(float deltaTime)
{
	m_pAnimatedSprite->Process(deltaTime);
	m_position.x = m_position.x + (deltaTime * m_velocity.x);
	m_position.y = m_position.y + (deltaTime * m_velocity.y);
}