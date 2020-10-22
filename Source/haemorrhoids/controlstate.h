
#ifndef __CONTROLSTATE_H__
#define __CONTROLSTATE_H__

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
class Game;

class ControlState : public GameState
{
	//Member Methods:
public:
	//~PlayState();

	static ControlState* GetInstance();
	static void DestroyInstance();


	bool Initialise(Game* game);

	void Process(Game* game, float deltaTime);
	void Draw(Game* game, BackBuffer& backBuffer);
	void HandleEvents(Game* game);

	void CleanUp();
	void Pause();
	void Resume();

	// Gameplay methods:
	void Back();
	void Quit();

protected:
	ControlState();//make singleton!

private:


	//Member Data:
public:

protected:
	static ControlState sm_ControlStateInstance;

private:

	//background images
	Background m_haaemorrhoidsStartScreen;

	// FMOD (sound) members:
	FMOD::Sound* m_pSplatSound;
	FMOD::Sound* m_pEngineSound;

	FMOD::Channel* m_pChannel1 = 0;
	FMOD::Channel* m_pChannel2 = 0;

	// Buttons:
	Background m_backButton;

	//Game engine ptr
	Game* m_pGameEngine;
};

#endif __CONTROLSTATE_H__
