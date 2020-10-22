#ifndef _BLOODPARTICLEEMITTER_H_
#define _BLOODPARTICLEEMITTER_H_

#include "particleemitter.h"
#include "bloodparticle.h"

class BloodParticleEmitter
{
	//member methods
public:
	BloodParticleEmitter();
	~BloodParticleEmitter();

	void SpawnParticles(float x, float y, float velx, float vely);

	void InitialiseParticles(BackBuffer* backBuffer);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	//member data
public:
	int m_blooPartArrSize;
	BloodParticle m_arrBloodParticles[100];

protected:

private:

};

#endif _BLOODPARTICLEEMITTER_H_