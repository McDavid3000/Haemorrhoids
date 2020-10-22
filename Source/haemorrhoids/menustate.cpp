#include "menustate.h"

// Local includes:
#include "introstate.h"
#include "game.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "playstate.h"
#include "highscorestate.h"
#include "controlstate.h"


// Forward Declarations:
class Sprite;

// Static Members:
MenuState MenuState::sm_MenuStateInstance;

MenuState::MenuState()
{

}

MenuState * MenuState::GetInstance()
{
	return &sm_MenuStateInstance;
}

void MenuState::DestroyInstance()
{
}

bool MenuState::Initialise(Game* game)
{
	FMOD_RESULT result;

	m_pGameEngine = game;

	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\introfart.wav", FMOD_DEFAULT, 0, &m_pSplatSound);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\deathfart.wav", FMOD_DEFAULT, 0, &m_pDeathSound);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\startfart.wav", FMOD_DEFAULT, 0, &m_pStartSound);


	result = game->GetFMODPtr()->playSound(m_pSplatSound, 0, false, &m_pChannel1);

	//init Haemorrhoids logo
	if (!m_haaemorrhoidsStartScreen.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\startscreen.png")))
	{
		LogManager::GetInstance().Log("Start screen Init Fail!");
		return (false);
	}
	m_haaemorrhoidsStartScreen.SetPosition(0, 0);

	if (!m_playButton.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\playbutton.png")))
	{
		LogManager::GetInstance().Log("Play button Init Fail!");
		return (false);
	}
	m_playButton.SetPosition(325, 400);

	if (!m_highScoresButton.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\highscoresbutton.png")))
	{
		LogManager::GetInstance().Log("Highscores button Init Fail!");
		return (false);
	}
	m_highScoresButton.SetPosition(325, 465);

	if (!m_settingsButton.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\controlsbutton.png")))
	{
		LogManager::GetInstance().Log("Controls button Init Fail!");
		return (false);
	}
	m_settingsButton.SetPosition(325, 530);

	if (!m_quitButton.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\quitbutton.png")))
	{
		LogManager::GetInstance().Log("Quit button Init Fail!");
		return (false);
	}
	m_quitButton.SetPosition(10, 560);

	//if (!m_creditsButton.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\creditsbutton.png")))
	//{
	//	LogManager::GetInstance().Log("Play button Init Fail!");
	//	return (false);
	//}
	//m_creditsButton.SetPosition(690, 560);

	return true;
}

void MenuState::Process(Game * game, float deltaTime)
{
	game->GetFMODPtr()->update();

}

void MenuState::Draw(Game * game, BackBuffer & backBuffer)
{

	m_haaemorrhoidsStartScreen.Draw(backBuffer);
	m_playButton.Draw(backBuffer);
	m_quitButton.Draw(backBuffer);
	//m_creditsButton.Draw(backBuffer);
	m_highScoresButton.Draw(backBuffer);
	m_settingsButton.Draw(backBuffer);
}

void MenuState::HandleEvents(Game * game)
{
	game->GetInputHandlerPtr()->ProcessMenuInput(*this);
}

void MenuState::CleanUp()
{
	m_haaemorrhoidsStartScreen.~Background();
	m_playButton.~Background();
	m_quitButton.~Background();
	//m_creditsButton.~Background();
	m_highScoresButton.~Background();
	m_settingsButton.~Background();
}

void 
MenuState::Pause()
{
}

void
MenuState::Resume()
{
}

void MenuState::Quit()
{
	//sound effect
	m_pGameEngine->Quit();
}

void MenuState::ShowHighScores()
{
	m_pGameEngine->GetFMODPtr()->playSound(m_pSplatSound, 0, false, &m_pChannel1);
	m_pGameEngine->ChangeState(HighScoreState::GetInstance());
}

void MenuState::ShowControls()
{
	m_pGameEngine->GetFMODPtr()->playSound(m_pSplatSound, 0, false, &m_pChannel1);
	m_pGameEngine->ChangeState(ControlState::GetInstance());
}

void
MenuState::StartGame()
{
	PlayState::GetInstance()->SetDebug(false);
	m_pGameEngine->GetFMODPtr()->playSound(m_pStartSound, 0, false, &m_pChannel1);
	SDL_Delay(1000);
	m_pGameEngine->ChangeState(PlayState::GetInstance());
}

void MenuState::StartGameDebug()
{
	PlayState::GetInstance()->SetDebug(true);
	m_pGameEngine->ChangeState(PlayState::GetInstance());
}

