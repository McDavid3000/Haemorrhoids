#include "playerbullet.h"


PlayerBullet::PlayerBullet()
	: Entity()
	, m_origin()
{
}

PlayerBullet::~PlayerBullet()
{
}

void 
PlayerBullet::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

void 
PlayerBullet::SetOrigin(float x, float y)
{
	m_origin.x = x;
	m_origin.y = y;
}

Vector2 
PlayerBullet::GetOrigin()
{
	return  m_origin;
}
