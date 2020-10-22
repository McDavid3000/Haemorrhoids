#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "entity.h"
#include "vector2.h"

class PlayerBullet : public Entity
{
	//member methods
public:
	PlayerBullet();
	~PlayerBullet();

	void Process(float deltaTime);

	void SetOrigin(float x, float y);
	Vector2 GetOrigin();

protected:

private:

	//member data

public:
	Vector2 m_origin;
protected:

private:

};

#endif _PLAYERBULLET_H_