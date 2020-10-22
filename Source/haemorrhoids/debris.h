#ifndef _DEBRIS_H_
#define _DEBRIS_H_

#include "entity.h"

class Debris : public Entity
{
	//member methods
public:
	Debris();
	~Debris();

	void Spawn();

	void Process(float deltaTime);

protected:

private:

	//member data

public:

protected:


private:

};

#endif _DEBRIS_H_