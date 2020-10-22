// COMP710 GP 2D Framework 2020

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "playership.h"
#include "debris.h"
#include "smokeanimation.h"
#include "pooparticleemitter.h"
#include "haemorrhoid.h"
#include "bloodparticleemitter.h"
#include "gamestate.h"
#include "menustate.h"
#include "introstate.h"
#include "playstate.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <fstream>

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
{

}

Game::~Game()
{
	while (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->CleanUp();
		m_vecGameStates.pop_back();
	}

	PlayState::DestroyInstance();
	MenuState::DestroyInstance();
	IntroState::DestroyInstance();

	m_pfMod->release();
	m_pfMod->close();


	delete m_pInputHandler;
	m_pInputHandler = 0;
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool
Game::Initialise()
{
	const int width = 800;
	const int height = 600;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(255, 255, 255);

	// Create and init FMOD
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pfMod);
	if (result != FMOD_OK)
	{
		//logger
	}

	result = m_pfMod->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		//logger
	}

	//load highscores OR init to zero if no ini file
	m_highScores[0].score = (500);
	sprintf_s(m_highScores[0].name, "%s", "Devin");
	m_highScores[1].score = 400;
	sprintf_s(m_highScores[1].name, "%s", "Dr Van Nost");
	m_highScores[2].score = 300;
	sprintf_s(m_highScores[2].name, "%s", "Dr Van Nost");
	m_highScores[3].score = 200;
	sprintf_s(m_highScores[3].name, "%s", "Dr Van Nost");
	m_highScores[4].score = 100;
	sprintf_s(m_highScores[4].name, "%s", "Dr Van Nost");
	

	return (true);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);

	//ask state to handle events
	m_vecGameStates.back()->HandleEvents(this);

	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);

		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}

		// DEBUG STUB:
		char buffer[64];
		sprintf_s(buffer, "%f", deltaTime);
		LogManager::GetInstance().Log(buffer);

		Draw(*m_pBackBuffer);
	}

	return (m_looping);
}

void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

    m_vecGameStates.back()->Process(this, deltaTime);
 }

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	m_vecGameStates.back()->Draw(this, backBuffer);

	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

int Game::GetFPS()
{
	return m_FPS;
}

void
Game::ChangeState(GameState * state)
{

	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->CleanUp();
		m_vecGameStates.pop_back();
	}

	// store and init the new state
	m_vecGameStates.push_back(state);
	m_vecGameStates.back()->Initialise(this);
}

void
Game::PushState(GameState * state)
{

	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->Pause();
	}

	m_vecGameStates.push_back(state);
	m_vecGameStates.back()->Initialise(this);
}

void Game::PopState()
{
	// cleanup the current state
	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->CleanUp();
		m_vecGameStates.pop_back();
	}

	// resume previous state
	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->Resume();
	}
}

FMOD::System *
Game::GetFMODPtr()
{
	return m_pfMod;
}

BackBuffer *
Game::GetBackBufferPtr()
{
	return m_pBackBuffer;
}

InputHandler *
Game::GetInputHandlerPtr()
{
	return m_pInputHandler;
}

void 
Game::SetHighScores(HighScore highScore)
{
	HighScore newScores[5];

	int insertPos = 0;
	bool isHighScore = false;

	for (int i = 4; i >= 0; i--)
	{
		if (highScore.score > m_highScores[i].score)
		{
			insertPos = (i);
			isHighScore = true;
		}
	}

	if (isHighScore)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i < insertPos)
			{
				newScores[i] = m_highScores[i];
			}

			if (i == insertPos)
			{
				newScores[i] = highScore;
			}

			if (i > insertPos)
			{
				newScores[i] = m_highScores[i - 1];
			}
		}

		memcpy(m_highScores, newScores, sizeof(m_highScores));

		std::ofstream highScoresFile("highscores.csv");

		// Send data to the stream
		highScoresFile << m_highScores[0].name;
		highScoresFile << m_highScores[1].name;
		highScoresFile << m_highScores[2].name;
		highScoresFile << m_highScores[3].name;
		highScoresFile << m_highScores[4].name;

		// Close the file
		highScoresFile.close();

	}
}

