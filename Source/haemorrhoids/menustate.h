
#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

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

class MenuState : public GameState
{
	//Member Methods:
public:
	//~PlayState();

	static MenuState* GetInstance();
	static void DestroyInstance();

	bool Initialise(Game* game);

	void Process(Game* game, float deltaTime);
	void Draw(Game* game, BackBuffer& backBuffer);
	void HandleEvents(Game* game);

	void CleanUp();
	void Pause();
	void Resume();

	// Gameplay methods:
	void ShowHighScores();
	void ShowControls();
	void StartGame();
	void StartGameDebug();
	void Quit();

protected:
	MenuState();//make singleton!

private:

	//Member Data:
public:

protected:
	static MenuState sm_MenuStateInstance;

private:

	//background images
	Background m_haaemorrhoidsStartScreen;

	// FMOD (sound) members:
	FMOD::Sound* m_pSplatSound;
	FMOD::Sound* m_pDeathSound;
	FMOD::Sound* m_pStartSound;

	FMOD::Channel* m_pChannel1 = 0;
	FMOD::Channel* m_pChannel2 = 0;

	// Buttons:
	Background m_playButton;
	Background m_quitButton;
	Background m_creditsButton;	
	Background m_settingsButton;	
	Background m_highScoresButton;

	//Game engine ptr
	Game* m_pGameEngine;
};

#endif __MENUSTATE_H__
