#ifndef _POOPARTICLE_H_
#define _POOPARTICLE_H_

#include "particle.h"

class PooParticle : public Particle
{
	//member methods
public:
	PooParticle();
	~PooParticle();

	bool Initialise(BackBuffer * backBuffer);

	void Process(float deltaTime);

protected:

private:

	//member data

public:

protected:

private:

};

#endif _POOPARTICLE_H_