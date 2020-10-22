#include "playership.h"
#include "sprite.h"
#include "smokeanimation.h"
#include "backbuffer.h"
#include "entity.h"

#include <cmath> 

Playership::Playership()
	: Entity()
	, m_isThrust(false)
	, m_lives()
	, m_score()
{
	m_lives = 3;
}

Playership::~Playership()
{
	m_bulletPool.~PlayerBulletPool();
	delete m_smokeAnimation;
	m_smokeAnimation = 0;
}

bool 
Playership::Initialise(Sprite * sprite)
{
	bool init = Entity::Initialise(sprite); 
	SetCenter();
	m_score = 0;
	m_isThrust = true;
	m_dead = false;

	return init;
}

//could be packed into a singel init method override that takes in several sprites
bool
Playership::InitialiseBullets(BackBuffer* backBuffer)
{
	return (m_bulletPool.Initialise(backBuffer));
}

bool
Playership::InitialiseSmokeAnimation(AnimatedSprite * sprite)
{
	m_smokeAnimation = new SmokeAnimation();
	bool init = (m_smokeAnimation->Initialise(sprite));
	SetSmokeStartPos();
	return init;
}

void
Playership::SetDead(bool dead)
{
	Entity::SetDead(dead);
	m_smokeAnimation->SetDead(dead);
}

void
Playership::SetSmokeStartPos()
{
	m_smokeAnimation->SetPositionX(this->m_position.x);
	m_smokeAnimation->SetPositionY(this->m_position.y + 32);
}

//on init set centre
void
Playership::SetCenter() 
{

	//screensize diveded by 2 minus the sprite size
	float centreX = 400;
	float centreY = 280;

	SetVerticalVelocity(0.0f);
	SetHorizontalVelocity(0.0f);

	SetPosition(centreX, centreY);
}

int Playership::GetLives()
{
	return m_lives;
}

int 
Playership::GetScore()
{
	return m_score;
}

bool Playership::IsInvincible()
{
	return m_invincibility;
}

void Playership::SetInvincible(bool set)
{
	m_invincibility = set;
}

void 
Playership::SetLives(int lives)
{
	m_lives = lives;
}

void 
Playership::SetScore(int score)
{
	m_score += score;
}

void
Playership::Process(float deltaTime)
{

	float pi = 3.14159265359f;

	//process smoke
	float radius = float(hypot(16, 16));

	float angle = float(atan(1)) * (180/pi);

	float x = cos(angle) * radius;
	float y = sin(angle) * radius;

	float centerSmokeX = (x + this->GetPositionX() + 16); 
	float centreSmokeY = (y + this->GetPositionY() + 16);
	float centerShipX = this->GetPositionX() + 16;
	float centerShipY = this->GetPositionY() + 16;

	float pos = cos(this->GetAngle()*(pi/180))*(centerShipX - centerSmokeX) - sin(this->GetAngle()*(pi / 180))*(centreSmokeY - centerShipY) + centerShipX;
	float posy = +sin(this->GetAngle()*(pi / 180))*(centerShipX - centerSmokeX) + cos(this->GetAngle()*(pi / 180))*(centreSmokeY- centerShipY) + centerShipY;

	m_smokeAnimation->SetPositionX(pos);
	m_smokeAnimation->SetPositionY(posy);

	m_smokeAnimation->SetAngle(GetAngle());
	
	m_smokeAnimation->Process(deltaTime);

	Entity::Process(deltaTime);
}

void 
Playership::Draw(BackBuffer& backBuffer)
{
	int centreX = m_pSprite->GetCenterX() + int(GetPositionX());
	int centreY = m_pSprite->GetCenterY() + int(GetPositionY());

	if (m_isThrust)
	{
		m_smokeAnimation->Draw(backBuffer, centreX, centreY);
	}

	Entity::Draw(backBuffer);
}



void 
Playership::Thrust()
{
	m_isThrust = true;

	float pi = 3.14159265359f;

	//can't allow velocity to be set higher than the speed limit
	float newXVelocity = m_velocity.x + (sin(m_pSprite->GetAngle()*(pi / 180)) * 100);

	if (newXVelocity < 300 && newXVelocity > -300)
	{
		m_velocity.x = newXVelocity;
	}

	float newYVelocity = m_velocity.y + (-cos(m_pSprite->GetAngle()*(pi / 180)) * 100);

	if (newYVelocity < 300 && newYVelocity > -300)
	{
		m_velocity.y = newYVelocity;
	}
}

void
Playership::TurnSpaceshipLeft()
{
	m_isThrust = true;

	m_pSprite->SetAngle(m_pSprite->GetAngle() - 30);
}

void
Playership::TurnSpaceshipRight()
{
	m_pSprite->SetAngle(m_pSprite->GetAngle() + 30);

}

void
Playership::FireBullet()
{
	m_bulletPool.GetNextBullet(this);
}

void
Playership::ProcessBullets(float deltaTime)
{
	m_bulletPool.ProcessBullets(deltaTime);
}

void
Playership::DrawBullets(BackBuffer& backBuffer)
{
	m_bulletPool.DrawBullets(backBuffer);
}

PlayerBulletPool*
Playership::GetBulletPool()
{
	return &m_bulletPool;
}

bool
Playership::WithinSpawnRadius(Entity& e)
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

	thisCircle.radius = 150;

	//set greatest radius
	if (e.GetCentre().x > e.GetCentre().y)
	{
		eCircle.radius = e.GetCentre().x;
	}
	else
	{
		eCircle.radius = e.GetCentre().y;
	}

	int centreScreenX = 400;
	int centreScreenY = 300;

	float x = centreScreenX - (e.GetPositionX() + e.GetCentre().x);
	float y = centreScreenY - (e.GetPositionY() + e.GetCentre().y);

	float hypotenuse = hypot(x, y);

	if ((thisCircle.radius + eCircle.radius) >= hypotenuse)
	{
		colliding = true;
	}

	return colliding;
}


