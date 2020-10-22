#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_

//includes
#include <vector>
#include "particle.h"

//forward declarations
class Particle;
class BackBuffer;

class ParticleEmitter
{
	//member methods
public:
	ParticleEmitter();
	~ParticleEmitter();

protected:

private:

	//member data

public:

protected:
	std::vector<Particle> m_vecParticleContainer;

private:

};

#endif _PARTICLEEMITTER_H_