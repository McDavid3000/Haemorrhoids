// COMP710 GP 2D Framework 2020
#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

// Includes
#include <fmod.hpp>  
#include <cassert>
#include <SDL.h>
#include <cstdio>

// Local includes:
#include "debrismanager.h"
#include "gamestate.h"
#include "background.h"

// Forward Declarations:
class BackBuffer;
class InputHandler;
class Sprite;
class Playership;
class SmokeAnimation;
class PooParticleEmitter;
class Haemorrhoid;
class BloodParticleEmitter;
class Game;


class PlayState : public GameState
{
	//Member Methods:
public:
	//~PlayState();

	static PlayState* GetInstance();
	static void DestroyInstance();


	bool Initialise(Game* game);

	void Process(Game* game, float deltaTime);
	void Draw(Game* game, BackBuffer& backBuffer);
	void HandleEvents(Game* game);

	void CleanUp();
	void Pause();
	void Resume();

	void SetDebug(bool debug);

	void InputPlayerName();

	//debug methods
	void ChangeLevel(int level);
	void ToggleInvincibility();
	void BackToMenu();

	// Gameplay methods:
	void SpaceshipThrust();
	void TurnSpaceshipLeft();
	void TurnSpaceshipRight();
	void FirePlayerBullet();

	void CreatePooParticles(float x, float y, float velx, float vely, Game * game);
	void CreateBloodParticles(float x, float y, float velx, float vely, Game * game);

	void Quit();

protected:
	PlayState();//make singleton!

private:


	//Member Data:
public:
	bool m_paused;
	bool m_debugMode;

protected:
	static PlayState sm_pPlayStateInstance;

private:

	// Level
	int m_level;

	// FMOD (sound) members:
	FMOD::Sound* m_pSplatSound;
	FMOD::Sound* m_pExplosionSound;
	FMOD::Sound* m_pMusicLoop;
	FMOD::Sound* m_pLaserSound;
	FMOD::Sound* m_pDeathSound;
	FMOD::Sound* m_pScreamSound;


	FMOD::Channel* m_pChannel1 = 0;
	FMOD::Channel* m_pChannel2 = 0;

	// Game entities:
	Playership* m_pPlayership;
	Haemorrhoid* m_pHaemorrhoid;

	Background* m_pbackground;
	DebrisManager m_debrisManager;

	char m_playerName[16];

	// Particles
	std::vector<PooParticleEmitter*> m_vecPooPartEmitterContainer;
	std::vector<BloodParticleEmitter*> m_vecBloodPartEmitterContainer;

	//Game engine ptr
	Game* m_pGameEngine;

};

#endif __PLAYSTATE_H__
