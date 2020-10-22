// COMP710 GP 2D Framework 2020
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Local includes:
#include "vector2.h" 

// Forward Declarations:
class BackBuffer;
class Sprite;

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void DrawAndShrink(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	void SetAngle(float angle);
	float GetAngle();

	void SetAlpha(unsigned char alpha);
	unsigned char GetAlpha();
	bool isBlendedOut();

	Vector2 GetCentre();

	int GetSpriteHeight();
	int GetSpriteWidth();

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_centre;

	bool m_dead;

	bool m_blendedOut;

private:

};

#endif __ENTITY_H__
