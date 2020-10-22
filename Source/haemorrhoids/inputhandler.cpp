// COMP710 GP 2D Framework 2020

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "playstate.h"
#include "logmanager.h"
#include "menustate.h"
#include "highscorestate.h"
#include "controlstate.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
	: m_pGameController(0)
{
}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_GameControllerClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_GameControllerOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}


//changed to state
void
InputHandler::ProcessPlayInput(PlayState& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{

		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.BackToMenu();
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				game.TurnSpaceshipLeft();
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				game.TurnSpaceshipRight();
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				game.SpaceshipThrust();
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				game.FirePlayerBullet();
			}
			else if (event.key.keysym.sym == SDLK_1)
			{
				game.ChangeLevel(1);
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				game.ChangeLevel(2);
			}
			else if (event.key.keysym.sym == SDLK_3)
			{
				game.ChangeLevel(3);
			}
			else if (event.key.keysym.sym == SDLK_4)
			{
				game.ChangeLevel(4);
			}
			else if (event.key.keysym.sym == SDLK_5)
			{
				game.ChangeLevel(5);
			}
			else if (event.key.keysym.sym == SDLK_6)
			{
				game.ChangeLevel(6);
			}
			else if (event.key.keysym.sym == SDLK_i)
			{
				game.ToggleInvincibility();
			}
			else if (event.key.keysym.sym == SDLK_p)
			{
				if (game.m_paused)
				{
					game.Resume();
				}
				else
				{
					game.Pause();
				}
			}
		}
		else if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			 if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				game.SpaceshipThrust();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
			{
				game.FirePlayerBullet();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			{
				game.TurnSpaceshipLeft();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				game.TurnSpaceshipRight();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
			 {
				 if (game.m_paused)
				 {
					 game.Resume();
				 }
				 else
				 {
					 game.Pause();
				 }
			 }
		}
		else if (event.type == SDL_CONTROLLERAXISMOTION)
		{
			if (event.jaxis.axis == 0)
			{
				if (event.jaxis.value < -10000)
				{
					game.TurnSpaceshipLeft();
				}
				else if (event.jaxis.value > 10000)
				{
					game.TurnSpaceshipRight();
				}
			}
		}
	}
}

void
InputHandler::ProcessMenuInput(MenuState& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.Quit();
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//quit
			if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 10 && event.button.x < 110 && event.button.y > 560 && event.button.y < 590)
			{
				game.Quit();
			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 325 && event.button.x < 475 && event.button.y > 400 && event.button.y < 445)
			{
				game.StartGame();
			}
			//settings
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 325 && event.button.x < 475 && event.button.y > 530 && event.button.y < 575)
			{
				game.ShowControls();
			}
			//highscores 
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 325 && event.button.x < 475 && event.button.y > 465 && event.button.y < 510)
			{
				game.ShowHighScores();
			}
			//credits 
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 690 && event.button.x < 790 && event.button.y > 560 && event.button.y < 590)
			{
				//game.StartGame();
			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 690 && event.button.x < 790 && event.button.y > 0 && event.button.y < 100)
			{
				game.StartGameDebug();
			}
		}
	}
}

void
InputHandler::ProcessHighScoreInput(HighScoreState& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{

		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.Quit();
			}
			//quit
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 10 && event.button.x < 110 && event.button.y > 560 && event.button.y < 590)
			{
				game.Back();
			}
		}
	}
}

void
InputHandler::ProcessControlStateInput(ControlState& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{

		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.Quit();
			}
			//quit
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 10 && event.button.x < 110 && event.button.y > 560 && event.button.y < 590)
			{
				game.Back();
			}
		}
	}
}
