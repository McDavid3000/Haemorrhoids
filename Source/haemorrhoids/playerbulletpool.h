#pragma once

#ifndef __PLAYERBULLETPOOL_H__
#define __PLAYERBULLETPOOL_H__

// Local includes:
#include "playerbullet.h"

// Forward Declarations:
class BackBuffer;
class Playership;

class PlayerBulletPool
{
	//Member Methods:
public:
	PlayerBulletPool();
	~PlayerBulletPool();

	bool Initialise(BackBuffer* backBuffer);

	void GetNextBullet(Playership* ship);
	void ProcessBullets(float deltaTime);
	void DrawBullets(BackBuffer & backBuffer);
	PlayerBullet* GetBullets();

	void CheckBulletInRange(PlayerBullet* playerBullet);

protected:

private:
	PlayerBulletPool(const PlayerBulletPool& entity);
	PlayerBulletPool& operator=(const PlayerBulletPool& entity);

	//Member Data:
public:

protected:
	PlayerBullet m_arrBulletPool[10];
	int m_nextBullet;

private:

};

#endif //__PLAYERBULLETPOOL_H__
