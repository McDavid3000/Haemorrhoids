#include "playstate.h"
#include "game.h"
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
#include "menustate.h"

#include <iostream>
#include<string>

// Static Members:
PlayState PlayState::sm_pPlayStateInstance;

PlayState::PlayState()
	: m_debrisManager()
	, m_level()
	, m_paused(false)
{
}

PlayState*
PlayState::GetInstance()
{
	return &sm_pPlayStateInstance;
}

void
PlayState::DestroyInstance()
{
}

bool PlayState::Initialise(Game* game)
{
	FMOD_RESULT result;

	m_pGameEngine = game;

	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\poopsplat.wav", FMOD_DEFAULT, 0, &m_pSplatSound);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\haemorrhoiddestroyed1.wav", FMOD_DEFAULT, 0, &m_pExplosionSound);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\musicloop.wav", FMOD_LOOP_NORMAL, 0, &m_pMusicLoop);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\laser.wav", FMOD_DEFAULT, 0, &m_pLaserSound);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\deathfart.wav", FMOD_DEFAULT, 0, &m_pDeathSound);
	result = game->GetFMODPtr()->createSound("..\\Game\\Assets\\Sound\\scream.wav", FMOD_DEFAULT, 0, &m_pScreamSound);

	result = game->GetFMODPtr()->playSound(m_pMusicLoop, 0, false, &m_pChannel2);

	m_pbackground = new Background();
	if (!m_pbackground->Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\background1.png")))
	{
		LogManager::GetInstance().Log("Background Init Fail!");
		return (false);
	}

	m_pPlayership = new Playership();
	if (!m_pPlayership->Initialise(game->GetBackBufferPtr()->CreateSprite("..\\Game\\Assets\\Art\\ship.png")))
	{
		LogManager::GetInstance().Log("Playership Init Fail!");
		return (false);
	}

	m_pPlayership->SetCenter();

	if (!m_pPlayership->InitialiseBullets(game->GetBackBufferPtr()))
	{
		LogManager::GetInstance().Log("Playerbullet Init Fail!");
		return (false);
	}

	m_pHaemorrhoid = new Haemorrhoid();
	if (!m_pHaemorrhoid->Initialise(game->GetBackBufferPtr()->CreateAnimatedSprite("..\\Game\\Assets\\Animations\\haemorrhoidanimation.png")))
	{
		LogManager::GetInstance().Log("Haemorrhoid Init Fail!");
		return (false);
	}

	if (!m_pPlayership->InitialiseSmokeAnimation(game->GetBackBufferPtr()->CreateAnimatedSprite("..\\Game\\Assets\\Animations\\smokeanimation.png")))
	{
		LogManager::GetInstance().Log("Smoke animation Init Fail!");
		return (false);
	}


	if (!m_debrisManager.Initialise(game->GetBackBufferPtr()))
	{
		LogManager::GetInstance().Log("Debris Init Fail!");
		return (false);
	}

	char buffer[64];
	sprintf_s(buffer, "Playership %d", sizeof(m_pPlayership->m_smokeAnimation));
	LogManager::GetInstance().Log(buffer);

	sprintf_s(buffer, "Background %d", sizeof(m_pbackground));
	LogManager::GetInstance().Log(buffer);

	sprintf_s(buffer, "Engine %d", sizeof(m_pGameEngine));
	LogManager::GetInstance().Log(buffer);

	m_level = 1;
	m_pHaemorrhoid->Spawn();

	return true;
}

void PlayState::Process(Game * game, float deltaTime)
{
	if (!m_paused)
	{
		game->GetFMODPtr()->update();
		m_pPlayership->Process(deltaTime);
		m_pHaemorrhoid->Process(deltaTime);

		for (PooParticleEmitter* pEmitter : m_vecPooPartEmitterContainer)
		{
			pEmitter->Process(deltaTime);
		}

		for (BloodParticleEmitter* pEmitter : m_vecBloodPartEmitterContainer)
		{
			pEmitter->Process(deltaTime);
		}

        m_pPlayership->ProcessBullets(deltaTime);
		m_debrisManager.Process(deltaTime);

		if (!m_pPlayership->IsDead() && !m_pPlayership->IsInvincible())
		{
			if (m_pHaemorrhoid->CheckCollision(*m_pPlayership) || m_debrisManager.CheckDebrisCollisionWithPlayer(*m_pPlayership))
			{
				FMOD_RESULT result = game->GetFMODPtr()->playSound(m_pDeathSound, 0, false, &m_pChannel1);

				m_pPlayership->SetLives(m_pPlayership->GetLives() - 1);

				m_pPlayership->SetDead(true);

			}
		}

		std::vector<Entity*> vecDebris;
		for (int i = 0; i < 10; i++)
		{
			if (!m_pPlayership->GetBulletPool()->GetBullets()[i].IsDead())
			{
				vecDebris = m_debrisManager.CheckDebrisCollisionWithBullet(m_pPlayership->GetBulletPool()->GetBullets()[i]);

				if (!m_pHaemorrhoid->IsDead())
				{
					if (m_pHaemorrhoid->CheckCollision(m_pPlayership->GetBulletPool()->GetBullets()[i]))
					{
						if (m_pHaemorrhoid->IsDead())
						{
							CreateBloodParticles((m_pHaemorrhoid->GetCentre().x + m_pHaemorrhoid->GetPositionX()), (m_pHaemorrhoid->GetCentre().y + m_pHaemorrhoid->GetPositionY()), m_pHaemorrhoid->GetHorizontalVelocity(), m_pHaemorrhoid->GetVerticalVelocity(), game);
							FMOD_RESULT result = game->GetFMODPtr()->playSound(m_pExplosionSound, 0, false, &m_pChannel1);
							result = game->GetFMODPtr()->playSound(m_pScreamSound, 0, false, &m_pChannel1);

							m_pPlayership->SetScore(1000);
						}
						else
						{
							FMOD_RESULT result = game->GetFMODPtr()->playSound(m_pSplatSound, 0, false, &m_pChannel1);
						}
					}
				}

				for (Entity* e : vecDebris)
				{
					CreatePooParticles(e->GetPositionX(), e->GetPositionY(), e->GetHorizontalVelocity(), e->GetVerticalVelocity(), game);
					FMOD_RESULT result = game->GetFMODPtr()->playSound(m_pSplatSound, 0, false, &m_pChannel1);

					m_pPlayership->SetScore(100);
				}
			}
		}
		if (m_debrisManager.AllDead() && m_pHaemorrhoid->IsDead())
		{
			m_pPlayership->SetCenter();
			m_level++;
			m_debrisManager.SpawnDebris(DebrisManager::Size::Large, (m_level + 1), 0, 0);
            m_pHaemorrhoid->Spawn();
		}

		if (m_pPlayership->IsDead())
		{
			if (!m_debrisManager.DebrisWithinSpawnRadius())
			{
				m_pPlayership->SetCenter();
				m_pPlayership->SetDead(false);
			}
		}

		if (m_pPlayership->GetLives() <= 0)
		{
			HighScore highScore;
			highScore.score = m_pPlayership->GetScore();
		//	InputPlayerName();

			sprintf_s(highScore.name, "Dr S. Hooper");
			m_pGameEngine->SetHighScores(highScore);

			m_pMusicLoop->release();
			m_pGameEngine->ChangeState(MenuState::GetInstance());
		}
	}
}

void PlayState::Draw(Game * game, BackBuffer & backBuffer)
{
	m_pbackground->Draw(backBuffer);
	m_pHaemorrhoid->Draw(backBuffer);
	m_pPlayership->DrawBullets(backBuffer);
	m_debrisManager.Draw(backBuffer);
	m_pPlayership->Draw(backBuffer);

	for (PooParticleEmitter* pEmitter : m_vecPooPartEmitterContainer)
	{
		pEmitter->Draw(backBuffer);
	}

	for (BloodParticleEmitter* pEmitter : m_vecBloodPartEmitterContainer)
	{
		pEmitter->Draw(backBuffer);
	}

	backBuffer.SetTextColour(0, 0, 0);

	char buffer[64];
	sprintf_s(buffer, "Lives: %d", m_pPlayership->GetLives());
	backBuffer.DrawText(25, 25, buffer);

	sprintf_s(buffer, "Score: %d", m_pPlayership->GetScore());
	backBuffer.DrawText(25, 550, buffer);

	sprintf_s(buffer, "Level: %d", m_level);
	backBuffer.DrawText(25, 500, buffer);

	if (m_paused)
	{
		sprintf_s(buffer, "Paused");
		m_pGameEngine->GetBackBufferPtr()->DrawText(350, 260, buffer);

	}

	//if in debug mode
	if (m_debugMode)
	{
		sprintf_s(buffer, "Debug Mode");
		m_pGameEngine->GetBackBufferPtr()->DrawText(330, 10, buffer);

		sprintf_s(buffer, "Press number keys 1-6 for level select");
		m_pGameEngine->GetBackBufferPtr()->DrawText(230, 50, buffer);

		sprintf_s(buffer, "Press *i* to toggle invincibility");
		m_pGameEngine->GetBackBufferPtr()->DrawText(230, 100, buffer);

		//if numbers pressed choose level and respwns
		sprintf_s(buffer, "FPS: %d", m_pGameEngine->GetFPS());
		m_pGameEngine->GetBackBufferPtr()->DrawText(700, 550, buffer);
	}
}

void PlayState::HandleEvents(Game* game)
{
	game->GetInputHandlerPtr()->ProcessPlayInput(*this);
}

void PlayState::CleanUp()
{
	delete m_pPlayership;
	m_pPlayership = 0;

	delete m_pHaemorrhoid;
	m_pHaemorrhoid = 0;

	delete m_pbackground;
	m_pbackground = 0;

	m_debrisManager.~DebrisManager();

	// Particles
	for (PooParticleEmitter* pEmitter : m_vecPooPartEmitterContainer)
	{
		delete pEmitter;
		pEmitter = 0;
	}
	m_vecPooPartEmitterContainer.clear();

	for (BloodParticleEmitter* pEmitter : m_vecBloodPartEmitterContainer)
	{
		delete pEmitter;
		pEmitter = 0;
	}
	m_vecBloodPartEmitterContainer.clear();
}

void PlayState::Pause()
{
	m_pChannel2->setPaused(true);
	m_paused = true;
}

void PlayState::Resume()
{
	m_pChannel2->setPaused(false);
	m_paused = false;
}

void PlayState::SetDebug(bool debug)
{
	m_debugMode = debug;
}

void
PlayState::SpaceshipThrust()
{
	if (!m_pPlayership->IsDead() && !m_paused)
	{
		m_pPlayership->Thrust();
	}
}

void
PlayState::TurnSpaceshipLeft()
{
	if (!m_pPlayership->IsDead() && !m_paused)
	{
		m_pPlayership->TurnSpaceshipLeft();
	}
}

//rename from spaceship
void
PlayState::TurnSpaceshipRight()
{
	if (!m_pPlayership->IsDead() && !m_paused)
	{
		m_pPlayership->TurnSpaceshipRight();

	}
}

void
PlayState::FirePlayerBullet()
{
	if (!m_pPlayership->IsDead() && !m_paused)
	{
		m_pPlayership->FireBullet();
		FMOD_RESULT result = m_pGameEngine->GetFMODPtr()->playSound(m_pLaserSound, 0, false, &m_pChannel1);
	}
}

void
PlayState::CreatePooParticles(float x, float y, float velx, float vely, Game * game)
{
	PooParticleEmitter* partEmitter = new PooParticleEmitter();
	partEmitter->InitialiseParticles(game->GetBackBufferPtr());
	partEmitter->SpawnParticles(x, y, velx, vely);

	m_vecPooPartEmitterContainer.push_back(partEmitter);
}

void
PlayState::CreateBloodParticles(float x, float y, float velx, float vely, Game * game)
{
	BloodParticleEmitter* partEmitter = new BloodParticleEmitter();
	partEmitter->InitialiseParticles(game->GetBackBufferPtr());
	partEmitter->SpawnParticles(x, y, velx, vely);

	m_vecBloodPartEmitterContainer.push_back(partEmitter);
}

void PlayState::Quit()
{
	m_pGameEngine->Quit();
}

void PlayState::InputPlayerName()
{
	char buffer[64];
	sprintf_s(buffer, "High score!");

	m_pGameEngine->GetBackBufferPtr()->DrawText(25, 25, buffer);
	std::cout << "Please enter your name\n";
	std::cin.get(m_playerName, sizeof(m_playerName));

}

void PlayState::ChangeLevel(int level)
{
	if (m_debugMode)
	{
		m_pPlayership->SetCenter();
		m_level = level;
		m_debrisManager.SpawnDebris(DebrisManager::Size::Large, (level), 0, 0);
		m_pHaemorrhoid->Spawn();
	}
}

void PlayState::ToggleInvincibility()
{
	if (m_debugMode)
	{
		if (m_pPlayership->IsInvincible())
		{
			m_pPlayership->SetInvincible(false);
		}
		else
		{
			m_pPlayership->SetInvincible(true);
		}
	}
}

void PlayState::BackToMenu()
{
	m_pMusicLoop->release();

	m_pGameEngine->ChangeState(MenuState::GetInstance());
}

