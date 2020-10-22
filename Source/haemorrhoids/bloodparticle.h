#ifndef _BLOODPARTICLE_H_
#define _BLOODPARTICLE_H_

#include "particle.h"

class BloodParticle : public Particle
{
	//member methods
public:
	BloodParticle();
	~BloodParticle();

	bool Initialise(BackBuffer * backBuffer);

	void Process(float deltaTime);

protected:

private:

	//member data

public:

protected:

private:

};

#endif _BLOODPARTICLE_H_
