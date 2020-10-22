// COMP710 GP 2D Framework 2020
#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

// Local includes:

// Forward Declarations:
class BackBuffer;
class Sprite;
class Game;

class GameState
{
	//Member Methods:
public:
	~GameState();

	virtual bool Initialise(Game* game) = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Process(Game* game, float deltaTime) = 0;
	virtual void Draw(Game* game, BackBuffer& backBuffer) = 0;
	virtual void HandleEvents(Game* game) = 0;

	void ChangeState(Game* game, GameState* state);

protected:
	GameState();

private:
	GameState(const GameState& gState);
	GameState& operator=(const GameState& gState);

	//Member Data:
public:

protected:


private:

};

#endif __GAMESTATE_H__
