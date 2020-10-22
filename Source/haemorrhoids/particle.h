#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "entity.h"

//forward declaration
class BackBuffer;

class Particle : public Entity
{
	//member methods
public:
	Particle();
	~Particle();

	void Process(float deltaTime);
	void Draw(BackBuffer &backBuffer);
	void SetAge(int age);
	void SetAlpha(unsigned char alpha);
	unsigned char GetAlpha();

protected:

private:

	//member data

public:
	//Vector2D m_acceleration;
	int m_age;
protected:

private:

};

#endif _PARTICLE_H_