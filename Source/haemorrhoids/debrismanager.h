#ifndef _DEBRISMANAGER_H_
#define _DEBRISMANAGER_H_

// Local includes:
#include "entity.h"
#include "debris.h"

//Library includes:
#include <vector>

//Forward declarations:
class PooParticleEmitter;

class DebrisManager 
{
	//member methods
public:
	DebrisManager();
	~DebrisManager();

	bool Initialise(BackBuffer* backBuffer);
	enum class Size { Large, Medium, Small };

	bool DebrisWithinSpawnRadius();

	void SpawnDebris(Size size, int number, float XLocation, float YLocation);

	std::vector<Entity*> CheckDebrisCollisionWithBullet(Entity& e);
	bool CheckDebrisCollisionWithPlayer(Entity& e);
	bool WithinPlayerSpawnRadius(Entity& e);

	bool AllDead();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:
	DebrisManager(const DebrisManager& dm);
	DebrisManager& operator=(const DebrisManager& dm);

	//member data
public:

protected:
	//container for dead and alive so iteration quicker too?
	Debris m_arrLargeDebris[6];
	Debris m_arrMedDebris[12];
	Debris m_arrSmallDebris[24];

	std::vector<PooParticleEmitter*> m_vecExplosionEmitterContainer;

private:

};

#endif _DEBRISMANAGER_H_