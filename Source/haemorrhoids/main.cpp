// COMP710 GP 2D Framework 2020

// Library includes:
#include <SDL.h>
#include <crtdbg.h> 
#include <ctime> 
#include <cstdlib>  

// Local includes:
#include "game.h"
#include "playstate.h"
#include "introstate.h"

#include "gamestate.h"
#include "logmanager.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(unsigned int (time(0)));

	Game& gameInstance = Game::GetInstance();

	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game initialise failed!");

		return (1);
	}

	gameInstance.ChangeState(IntroState::GetInstance());
	
	//start straight from gameplay for debugging
	//gameInstance.ChangeState(PlayState::GetInstance());

	while (gameInstance.DoGameLoop())
	{
		// No body.
	}

	Game::DestroyInstance();
	LogManager::DestroyInstance();

	return (0);
}
