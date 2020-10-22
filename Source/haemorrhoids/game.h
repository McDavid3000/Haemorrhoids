// COMP710 GP 2D Framework 2020
#ifndef __GAME_H__
#define __GAME_H__

// Library includes:
#include <fmod.hpp>  

// Local includes:
#include "debrismanager.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Playership;
class SmokeAnimation;
class PooParticleEmitter;
class Haemorrhoid;
class BloodParticleEmitter;
class PlayState;
class GameState;

struct HighScore
{
	int score;
	char name[16];
};

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	int GetFPS();

	//State managment methods
	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void SetHighScores(HighScore m_highScore);

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);

	Game();

	//Member Data:
public:

	std::vector<GameState*> m_vecGameStates;

	PlayState* pState;

	HighScore m_highScores[5];

	FMOD::System* GetFMODPtr();
	BackBuffer* GetBackBufferPtr();
	InputHandler* GetInputHandlerPtr();

protected:
	static Game* sm_pInstance;
	FMOD::System* m_pfMod;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;

	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

private:
};

#endif // __GAME_H__
