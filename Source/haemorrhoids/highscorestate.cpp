#include "highscorestate.h" 

// Local includes:
#include "introstate.h"
#include "game.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "playstate.h"
#include "menustate.h"


// Forward Declarations:
class Sprite;

// Static Members:
HighScoreState HighScoreState::sm_HighScoreStateInstance;

HighScoreState::HighScoreState()
{

}

HighScoreState * HighScoreState::GetInstance()
{
	return &sm_HighScoreStateInstance;
}

void HighScoreState::DestroyInstance()
{
}

bool HighScoreState::Initialise(Game* game)
{
	FMOD_RESULT result;

	m_pGameEngine = game;

	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\introfart.wav", FMOD_DEFAULT, 0, &m_pSplatSound);

	//init Haemorrhoids logo
	if (!m_haaemorrhoidsStartScreen.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\startscreen.png")))
	{
		LogManager::GetInstance().Log("Start screen Init Fail!");
		return (false);
	}
	m_haaemorrhoidsStartScreen.SetPosition(0, 0);

	if (!m_backButton.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\backbutton.png")))
	{
		LogManager::GetInstance().Log("Back button Init Fail!");
		return (false);
	}
	m_backButton.SetPosition(10, 560);

	return true;
}

void HighScoreState::Process(Game * game, float deltaTime)
{
	game->GetFMODPtr()->update();
}

void HighScoreState::Draw(Game * game, BackBuffer & backBuffer)
{
	m_haaemorrhoidsStartScreen.Draw(backBuffer);
	m_backButton.Draw(backBuffer);

	char buffer[64];
	int ySpacing = 400;
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(buffer, "%d. %s: %d", (i+1), m_pGameEngine->m_highScores[i].name, m_pGameEngine->m_highScores[i].score);
		LogManager::GetInstance().Log(buffer);
		backBuffer.DrawText(300, ySpacing, buffer);
		ySpacing = ySpacing + 30;
	}
}

void HighScoreState::HandleEvents(Game * game)
{
	game->GetInputHandlerPtr()->ProcessHighScoreInput(*this);
}

void HighScoreState::CleanUp()
{
	m_haaemorrhoidsStartScreen.~Background();
	m_backButton.~Background();
}

void
HighScoreState::Pause()
{
}

void
HighScoreState::Resume()
{
}

void HighScoreState::Quit()
{
	//sound effect
	m_pGameEngine->Quit();
}

void
HighScoreState::Back()
{
	//sound effect!
	m_pGameEngine->ChangeState(MenuState::GetInstance());
}

