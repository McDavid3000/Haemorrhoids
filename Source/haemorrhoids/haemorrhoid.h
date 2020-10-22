#ifndef _HAEMORRHOID_H_
#define _HAEMORRHOID_H_

#include "entity.h"

class AnimatedSprite;


class Haemorrhoid : public Entity
{
	//member methods
public:
	Haemorrhoid();
	~Haemorrhoid();

	bool Initialise(AnimatedSprite* animatedSprite);

	void Draw(BackBuffer& backBuffer);
	bool IsCollidingWith(Entity& e);

	void SetAngle(float angle);
	float GetAngle();
	void SetAlpha(unsigned char alpha);

	unsigned char GetAlpha();
	Vector2 GetCentre();

	void Process(float deltaTime);

	void Spawn();
	bool CheckCollision(Entity & e);
	bool WithinPlayerSpawnRadius();

	void SetHealth(int health);
	int GetHealth();

	void SetAnimation(bool set);

protected:

private:

	//member data

public:
	AnimatedSprite* m_pAnimatedSprite;
protected:


private:
	int m_health;
};

#endif _HAEMORRHOID_H_