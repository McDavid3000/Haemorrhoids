#ifndef _POOPARTICLEEMITTER_H_
#define _POOPARTICLEEMITTER_H_

#include "particleemitter.h"
#include "pooparticle.h"

class PooParticleEmitter 
{
	//member methods
public:
	PooParticleEmitter();
	~PooParticleEmitter();

	void InitialiseParticles(BackBuffer * backBuffer);
	void SpawnParticles(float x, float y, float velx, float vely);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	//member data

public:
	PooParticle m_arrPooParticles[15];

protected:

private:

};

#endif _POOPARTICLEEMITTER_H_