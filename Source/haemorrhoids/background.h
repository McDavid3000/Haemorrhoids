#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

// Local includes:
#include "entity.h"

// Forward Declarations:
class Sprite;
class BackBuffer;

class Background : public Entity
{
	//Member Methods:
public:
	Background();
	~Background();

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x);

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	void SetAngle(float angle);
	float GetAngle();

protected:

private:
	Background(const Background& bg);
	Background& operator=(const Background& bg);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

private:

};

#endif __BACKGROUND_H__
