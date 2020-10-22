#include "gamestate.h"
#include "game.h"

void GameState::ChangeState(Game * game, GameState * state)
{
	game->ChangeState(state);
}

GameState::GameState()
{
}

GameState::~GameState()
{
}
