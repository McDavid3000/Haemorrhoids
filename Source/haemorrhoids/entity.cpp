// COMP710 GP 2D Framework 2020

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <cmath>

Entity::Entity()
: m_pSprite(0)
, m_position(0.0f, 0.0f)
, m_velocity(0.0f, 0.0f)
, m_dead(false)
, m_blendedOut(false)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	sprite->SetHandleCenter();

	return (true);
}

void 
Entity::Process(float deltaTime)
{
	m_position.x = m_position.x + (deltaTime * m_velocity.x);
	m_position.y = m_position.y + (deltaTime * m_velocity.y);

	if (m_position.x > 800)
	{
		m_position.x = 0;
	}

	if (m_position.x < 0)
	{
		m_position.x = 800;
	}	

	if (m_position.y > 600)
	{
		m_position.y = 0;
	}	

	if (m_position.y < 0)
	{
		m_position.y = 600;
	}
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));

	if (!this->IsDead())
	{
		m_pSprite->Draw(backBuffer);
	}
}

void
Entity::DrawAndShrink(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));

	if (m_pSprite->GetAlteredHeight() < 20)
	{
		SetDead(true);
	}
	else
	{
		m_pSprite->DrawAndShrink(backBuffer);
	}
}

bool
Entity::IsCollidingWith(Entity& e)
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

	thisCircle.radius = float(m_pSprite->GetCenterX());
	eCircle.radius = float(e.m_pSprite->GetCenterX());

	float x = (GetPositionX() + m_pSprite->GetCenterX()) - (e.GetPositionX() + e.m_pSprite->GetCenterX());
	float y = (GetPositionY() + m_pSprite->GetCenterY()) - (e.GetPositionY() + e.m_pSprite->GetCenterY());

	float hypotenuse = hypot(x, y);

	if ((thisCircle.radius + eCircle.radius) >= hypotenuse)
	{
		colliding = true;
	}
	
	return colliding;
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool Entity::IsDead() const
{
	return m_dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_position.Set(x, y);
}

void
Entity::SetPositionX(float x)
{
	m_position.Set(x, m_position.y);
}

void
Entity::SetPositionY(float y)
{
	m_position.Set(m_position.x, y);
}

float 
Entity::GetPositionX() const
{
	return m_position.x;

}

float 
Entity::GetPositionY() const
{
	return m_position.y;
}

float 
Entity::GetHorizontalVelocity() const
{
	return m_velocity.x;
}

float 
Entity::GetVerticalVelocity() const
{
	return m_velocity.y;
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocity.x = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocity.y = y;
}

void 
Entity::SetAngle(float angle)
{
	m_pSprite->SetAngle(angle);
}

float 
Entity::GetAngle()
{
	return m_pSprite->GetAngle();
}

void 
Entity::SetAlpha(unsigned char alpha)
{
	m_pSprite->SetAlpha(alpha);

	if (alpha <= 0)
	{
		m_blendedOut = true;
	}
}

unsigned char 
Entity::GetAlpha()
{
	return m_pSprite->GetAlpha();
}

bool Entity::isBlendedOut()
{
	return m_blendedOut;
}

Vector2 
Entity::GetCentre()
{
	m_centre.x = float(m_pSprite->GetCenterX());
	m_centre.y = float(m_pSprite->GetCenterY());

	return m_centre;
}

//get sprites  width and height
int
Entity::GetSpriteHeight()
{
	return m_pSprite->GetHeight();
}

int
Entity::GetSpriteWidth()
{
	return m_pSprite->GetWidth();
}
