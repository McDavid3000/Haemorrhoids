#ifndef _PLAYERSHIP_H_
#define _PLAYERSHIP_H_

#include "entity.h"
#include "playerbullet.h"
#include "playerbulletpool.h"
#include "smokeanimation.h"

class Playership : public Entity
{
	//member methods
public:
	Playership();
	~Playership();

	bool Initialise(Sprite* sprite);
	bool InitialiseBullets(BackBuffer* backBuffer);
	bool InitialiseSmokeAnimation(AnimatedSprite * sprite);
	void SetDead(bool dead);
	void SetSmokeStartPos();
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetCenter();

	int GetLives();
	int GetScore();

	bool IsInvincible();
	void SetInvincible(bool set);

	void SetLives(int lives);
	void SetScore(int score);

	void Thrust();
	void TurnSpaceshipLeft();
	void TurnSpaceshipRight();

	void FireBullet();
	void ProcessBullets(float deltaTime);
	void DrawBullets(BackBuffer & backBuffer);
	PlayerBulletPool* GetBulletPool();

	bool WithinSpawnRadius(Entity & e);

protected:

private:

	//member data

public:
	SmokeAnimation* m_smokeAnimation;
	bool m_isThrust;
	int m_lives;
	int m_score;
	bool m_invincibility;

protected:

	PlayerBulletPool m_bulletPool;

private:

};

#endif _PLAYERSHIP_H_