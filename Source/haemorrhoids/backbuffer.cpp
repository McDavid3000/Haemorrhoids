// COMP710 GP 2D Framework 2020

// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "texturemanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "texture.h"
#include "vector2.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <cmath>

BackBuffer::BackBuffer()
: m_pTextureManager(0)
, m_pWindow(0)
, m_pRenderer(0)
, m_width(0)
, m_height(0)
, m_clearRed(0)
, m_clearGreen(0)
, m_clearBlue(0)
{

}

BackBuffer::~BackBuffer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	delete m_pTextureManager;
	m_pTextureManager = 0;

	IMG_Quit();
	SDL_Quit();
}

bool 
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("COMP710 2D Game Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
			}
		}
	}

	SetFullscreen(false);
	SDL_Delay(1000);

	TTF_Init();
	m_pDebugFont = TTF_OpenFont("..\\Game\\Assets\\Fonts\\debugfont.ttf", 26);

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	return (true);
}

void 
BackBuffer::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
//		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
		SDL_SetWindowSize(m_pWindow, m_width, m_height);
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, 0);
	}
}

void 
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void 
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	double angle = sprite.GetAngle();
	
	SDL_Point centre;
	centre.x = sprite.GetCenterX();
	centre.y = sprite.GetCenterY();

	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), sprite.GetAlpha());

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, angle, &centre, SDL_FLIP_NONE);
}

void
BackBuffer::DrawAnimatedSprite(AnimatedSprite& animatedSprite)
{
	SDL_Rect dest;

	SDL_Rect source;

	source.y = 0;
	source.h = animatedSprite.GetHeight();
	source.w = animatedSprite.GetFrameWidth();
	source.x = animatedSprite.GetFrameX();

	dest.x = animatedSprite.GetX();
	dest.y = animatedSprite.GetY();
	dest.w = animatedSprite.GetFrameWidth();
	dest.h = animatedSprite.GetHeight();

	double angle = animatedSprite.GetAngle();

	SDL_Point centre;

	int px = animatedSprite.GetCenterX();
	int py = animatedSprite.GetCenterY();

	int cx = animatedSprite.GetCenterX();
	int cy = animatedSprite.GetCenterY();

	centre.x = px;
	centre.y = py;

	SDL_RenderCopyEx(m_pRenderer, animatedSprite.GetTexture()->GetTexture(), &source, &dest, angle, &centre, SDL_FLIP_NONE);
}

void
BackBuffer::DrawRotatingAnimatedSprite(AnimatedSprite& animatedSprite, int centreX, int centreY)
{
	SDL_Rect dest;

	SDL_Rect source;

	source.y = 0;
	source.h = animatedSprite.GetHeight();
	source.w = animatedSprite.GetFrameWidth();
	source.x = animatedSprite.GetFrameX();

	dest.x = animatedSprite.GetX();
	dest.y = animatedSprite.GetY();
	dest.w = animatedSprite.GetFrameWidth();
	dest.h = animatedSprite.GetHeight();

	double angle =  animatedSprite.GetAngle();

	SDL_Point centre;

	centre.x = animatedSprite.GetCenterX();
	centre.y = animatedSprite.GetCenterX();

	SDL_RenderCopyEx(m_pRenderer, animatedSprite.GetTexture()->GetTexture(), &source, &dest, angle, &centre, SDL_FLIP_NONE);
}

void
BackBuffer::DrawShrinkingSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = int(sprite.GetAlteredWidth() * 0.95);
	dest.h = int(sprite.GetAlteredHeight() * 0.95);

	sprite.SetAlteredWidth(int(sprite.GetAlteredWidth() * 0.95));
	sprite.SetAlteredHeight(int(sprite.GetAlteredHeight() * 0.95));

	double angle = sprite.GetAngle();

	SDL_Point centre;
	centre.x = sprite.GetCenterX();
	centre.y = sprite.GetCenterY();

	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), sprite.GetAlpha());

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, angle, &centre, SDL_FLIP_NONE);
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;
	
	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2 - x1;
	fillRect.h = y2 - y1;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void 
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite* 
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

AnimatedSprite*
BackBuffer::CreateAnimatedSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	AnimatedSprite* pAnimatedSprite = new AnimatedSprite();

	if (!pAnimatedSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Animated Sprite Failed to Create!");
	}

	return (pAnimatedSprite);
}

void 
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;

}

void 
BackBuffer::DrawDebugCircles(Vector2 center, float radius)
{
	float _2PI = 6.28318530718f;

	int sides = int(_2PI * radius / 2);

	float d_a = _2PI / sides,
		angle = d_a;

	Vector2 start;
	Vector2 end;

	end.x = radius;
	end.y = 0.0f;
	end = end + center;

	for (int i = 0; i != sides; i++)
	{
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + center;
		angle += d_a;

		DrawLine(int(start.x), int(start.y), int(end.x), int(end.y));
	}
	
}

void BackBuffer::SetTextColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_textRed = r;
	m_textGreen = g;
	m_textBlue = b;
}

void BackBuffer::DrawText(int x, int y, const char * pcText)
{
	SDL_Color colour;
	colour.r = m_textRed;
	colour.g = m_textGreen;
	colour.b = m_textBlue;
	colour.a = 255;

	SDL_Surface * pSDLSurface = TTF_RenderText_Blended(m_pDebugFont, pcText, colour);
  	SDL_Texture* pSDLTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSDLSurface);

	int height;
	int width;
	SDL_QueryTexture(pSDLTexture, 0, 0, &width, &height);//use h and w from sdl surfaace

	SDL_Rect destRect;

	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(m_pRenderer, pSDLTexture, 0, &destRect);
	SDL_DestroyTexture(pSDLTexture);
	SDL_FreeSurface(pSDLSurface);
}
