// COMP710 GP 2D Framework 2020

// This include:
#include "sprite.h"

// Local includes:
#include "backbuffer.h"
#include "texture.h"

Sprite::Sprite()
: m_pTexture(0)
, m_x(0)
, m_y(0)
, m_width(0)
, m_height(0)
, m_angle(0.0f)
, m_centerX(0)
, m_centerY(0)
, m_ucAlpha(255)
{
}

Sprite::~Sprite()
{
}

bool 
Sprite::Initialise(Texture& texture)
{
	m_pTexture = &texture;
	
	m_width = m_pTexture->GetWidth();
	m_height = m_pTexture->GetHeight();

	SetAlteredWidth(m_width);
	SetAlteredHeight(m_height);

	return (true);
}

void 
Sprite::Process(float deltaTime)
{
}

void 
Sprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawSprite(*this);
}

void
Sprite::DrawAndShrink(BackBuffer& backbuffer)
{
	backbuffer.DrawShrinkingSprite(*this);
}

void 
Sprite::SetX(int x)
{
      	m_x = x;
}

void 
Sprite::SetY(int y)
{
	m_y = y;
}

int
Sprite::GetX() const
{
	return (m_x);
}

int
Sprite::GetY() const
{
	return (m_y);
}

void
Sprite::SetAngle(float angle)
{
	m_angle = angle;
}

float
Sprite::GetAngle() const
{
	return (m_angle);
}

void
Sprite::SetCenter(int x, int y)
{
	m_centerX = x;
	m_centerY = y;
}

void
Sprite::SetHandleCenter()
{
	m_centerX = m_width / 2; 
	m_centerY = m_height / 2;
}

int
Sprite::GetCenterX()
{
	return m_centerX; 
}

int
Sprite::GetCenterY()
{
	return m_centerY;
}

unsigned char Sprite::GetAlpha()
{
	return m_ucAlpha;
}

void Sprite::SetAlpha(unsigned char alpha)
{
       	m_ucAlpha = alpha;
}

Texture*
Sprite::GetTexture()
{
	return (m_pTexture);
}

int 
Sprite::GetWidth() const
{
	return (m_width);
}

int
Sprite::GetHeight() const
{
	return (m_height);
}


int 
Sprite::GetAlteredWidth()
{
	return m_alteredWidth;
}

int 
Sprite::GetAlteredHeight()
{
	return m_alteredHeight;
}

void 
Sprite::SetAlteredWidth(int w)
{
	m_alteredWidth = w;
}

void 
Sprite::SetAlteredHeight(int h)
{
	m_alteredHeight = h;
}