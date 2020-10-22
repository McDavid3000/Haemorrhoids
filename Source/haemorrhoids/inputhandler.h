// COMP710 GP 2D Framework 2020
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class Game;
class PlayState;
class MenuState;
class HighScoreState;
class ControlState;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessPlayInput(PlayState& game);
	void ProcessMenuInput(MenuState& game);
	void ProcessHighScoreInput(HighScoreState & game);
	void ProcessControlStateInput(ControlState & game);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_GameController* m_pGameController;

private:

};

#endif // __INPUTHANDER_H__
