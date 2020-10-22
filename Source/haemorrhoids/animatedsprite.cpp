// This includes:WHAT?
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{
}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = false;

	Sprite::Initialise(texture);

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	// SS04.10: Add the x coordinate to the frame coordinate container.
	m_vecFrameContainer.push_back(x);
}

void
AnimatedSprite::Process(float deltaTime)
{
	if (!m_paused && m_animating)
	{
		m_timeElapsed += deltaTime;

		if (m_timeElapsed > m_frameSpeed)
		{
			m_currentFrame++;

			m_timeElapsed = 0;

			if (m_currentFrame >= m_vecFrameContainer.size())
			{
				m_currentFrame = 0;

				if (!m_loop)
				{
					m_hasAnimated = true;
					m_paused = true;
				}


			}
		}
	}

	Sprite::Process(deltaTime);
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this);
}

void
AnimatedSprite::DrawRotatingSprite(BackBuffer& backbuffer, int centreX, int centreY)
{
	backbuffer.DrawRotatingAnimatedSprite(*this, centreX, centreY);
}

void 
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

int AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool AnimatedSprite::HasAnimated()
{
	return m_hasAnimated;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int
AnimatedSprite::GetFrameX()
{
	int x = m_vecFrameContainer[m_currentFrame];
	return x;
}
