#include "debris.h"
#include "sprite.h"

Debris::Debris()
	: Entity()
{
}

Debris::~Debris()
{
}

void
Debris::Spawn()
{
	//set location based on a circle around player location
	m_position.x = 100;
	m_position.y = 200;
	//set angle randomly 
	m_pSprite->SetAngle(30);
	//set speed randomly
	m_velocity.x = 20;
	m_velocity.y = 30;
}

void
Debris::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}
