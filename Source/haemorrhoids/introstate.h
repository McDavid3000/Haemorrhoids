// COMP710 GP 2D Framework 2020
#ifndef __INTROSTATE_H__
#define __INTROSTATE_H__

// Includes
#include <fmod.hpp>  
#include <cassert>
#include <SDL.h>
#include <cstdio>

// Local includes:
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

class IntroState : public GameState
{
	//Member Methods:
public:
	//~PlayState();

	static IntroState* GetInstance();
	static void DestroyInstance();

	bool Initialise(Game* game);

	void Process(Game* game, float deltaTime);
	void Draw(Game* game, BackBuffer& backBuffer);
	void HandleEvents(Game* game);

	void CleanUp();
	void Pause();
	void Resume();

	// Gameplay methods:

	void Quit();

protected:
	IntroState();//make singleton!

private:

	//Member Data:
public:

protected:
	static IntroState sm_IntroStateInstance;

private:

	//background images
	Background m_FMODLogo;
	Background m_AUTLogo;
	Background m_SDLLogo;
	Background m_haaemorrhoidsStartScreen;
	Background m_haaemorrhoidsControlScreen;
	Background m_shipAnimation;

	// FMOD (sound) members:
	FMOD::Sound* m_pSplatSound;
	FMOD::Sound* m_pEngineSound;

	FMOD::Channel* m_pChannel1 = 0;
	FMOD::Channel* m_pChannel2 = 0;

	// Game entities:
	Playership* m_pPlayership;

	//Game engine ptr
	Game* m_pGameEngine;
};

#endif __INTROSTATE_H__
