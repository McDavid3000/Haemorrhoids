// Local includes:
#include "introstate.h"
#include "game.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "menustate.h"


// Forward Declarations:
class Sprite; 

// Static Members:
IntroState IntroState::sm_IntroStateInstance;

IntroState::IntroState()
	:
	m_FMODLogo()
{

}

IntroState * IntroState::GetInstance()
{
	return &sm_IntroStateInstance;
}

void IntroState::DestroyInstance()
{
}

bool IntroState::Initialise(Game* game)
{
	FMOD_RESULT result;

	m_pGameEngine = game;

	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\introfart.wav", FMOD_DEFAULT, 0, &m_pSplatSound);

	//init FMOD logo
	if (!m_FMODLogo.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\FMOD.png")))
	{
		LogManager::GetInstance().Log("FMOD logo Init Fail!");
		return (false);
	}
	m_FMODLogo.SetAlpha(255);
	m_FMODLogo.SetPosition(36, 204);

	//init AUT logo
	if (!m_AUTLogo.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\AUT.png")))
	{
		LogManager::GetInstance().Log("AUT logo Init Fail!");
		return (false);
	}
	m_AUTLogo.SetAlpha(255);
	m_AUTLogo.SetPosition(0, 0);

	//init SDL logo CHANGE LOGGERS!
	if (!m_SDLLogo.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\SDL.png")))
	{
		LogManager::GetInstance().Log("SDL logo Init Fail!");
		return (false);
	}
	m_SDLLogo.SetAlpha(255);
	m_SDLLogo.SetPosition(0, 91);

	//init Haemorrhoids logo
	if (!m_haaemorrhoidsStartScreen.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\startscreen.png")))
	{
		LogManager::GetInstance().Log("Start screen Init Fail!");
		return (false);
	}
	m_haaemorrhoidsStartScreen.SetPosition(0, 0);

	//init ship sprite
	if (!m_shipAnimation.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\startscreenship.png")))
	{
		LogManager::GetInstance().Log("Playership Init Fail!");
		return (false);
	}
	m_shipAnimation.SetPosition(290, 280);

	return true;
}

void IntroState::Process(Game * game, float deltaTime)
{
	game->GetFMODPtr()->update();

	if (!m_FMODLogo.isBlendedOut())
	{
		m_FMODLogo.SetAlpha(m_FMODLogo.GetAlpha() - 1);
	}
	else if(!m_AUTLogo.isBlendedOut())
	{
		m_AUTLogo.SetAlpha(m_AUTLogo.GetAlpha() - 1);
	}
	else if (!m_SDLLogo.isBlendedOut())
	{
		m_SDLLogo.SetAlpha(m_SDLLogo.GetAlpha() - 1);
	}
}

void IntroState::Draw(Game * game, BackBuffer & backBuffer)
{
	if (!m_FMODLogo.isBlendedOut())
	{
		m_FMODLogo.Draw(backBuffer);
	}
	else if (!m_AUTLogo.isBlendedOut())
	{
		m_AUTLogo.Draw(backBuffer);
	}
	else if (!m_SDLLogo.isBlendedOut())
	{
		m_SDLLogo.Draw(backBuffer);
	}
	else
	{
		m_haaemorrhoidsStartScreen.Draw(backBuffer);
		if (!m_shipAnimation.IsDead())
		{
			m_shipAnimation.DrawAndShrink(backBuffer);
		}
		else
		{
			FMOD_RESULT result = game->GetFMODPtr()->playSound(m_pSplatSound, 0, false, &m_pChannel1);
			game->ChangeState(MenuState::GetInstance());
		}
	}
}

void IntroState::HandleEvents(Game * game)
{
}

void IntroState::CleanUp()
{
}

void IntroState::Pause()
{
}

void IntroState::Resume()
{
}

void IntroState::Quit()
{
}


