#include "controlstate.h" 

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
ControlState ControlState::sm_ControlStateInstance;

ControlState::ControlState()
{

}

ControlState * ControlState::GetInstance()
{
	return &sm_ControlStateInstance;
}

void ControlState::DestroyInstance()
{
}

bool ControlState::Initialise(Game* game)
{
	FMOD_RESULT result;

	m_pGameEngine = game;

	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\introfart.wav", FMOD_DEFAULT, 0, &m_pSplatSound);

	if (!m_haaemorrhoidsStartScreen.Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Logos\\controlscreen.png")))
	{
		LogManager::GetInstance().Log("Control screen Init Fail!");
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

void ControlState::Process(Game * game, float deltaTime)
{
	game->GetFMODPtr()->update();
}

void ControlState::Draw(Game * game, BackBuffer & backBuffer)
{
	m_haaemorrhoidsStartScreen.Draw(backBuffer);
	m_backButton.Draw(backBuffer);
}

void ControlState::HandleEvents(Game * game)
{
	game->GetInputHandlerPtr()->ProcessControlStateInput(*this);
}

void ControlState::CleanUp()
{
	m_haaemorrhoidsStartScreen.~Background();
	m_backButton.~Background();
}

void
ControlState::Pause()
{
}

void
ControlState::Resume()
{
}

void ControlState::Quit()
{
	m_pGameEngine->Quit();
}

void
ControlState::Back()
{
	m_pGameEngine->ChangeState(MenuState::GetInstance());
}

