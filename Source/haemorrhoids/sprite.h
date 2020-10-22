// COMP710 GP 2D Framework 2020
#ifndef __SPRITE_H__
#define __SPRITE_H__

// Forward Declarations:
class BackBuffer;
class Texture;

class Sprite
{
	//Member Methods:
public:
	Sprite();
	~Sprite();

	bool Initialise(Texture& texture);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void DrawAndShrink(BackBuffer& backbuffer);

	void SetX(int x);
	void SetY(int y);

	int GetX() const;
	int GetY() const;

	void SetAngle(float angle);
	float GetAngle() const;

	void SetCenter(int x, int y);
	void SetHandleCenter();

	int GetCenterX();
	int GetCenterY();

	int GetAlteredWidth();
	int GetAlteredHeight();
	void SetAlteredWidth(int w);
	void SetAlteredHeight(int h);

	int GetWidth() const;
	int GetHeight() const;

	unsigned char GetAlpha();
	void SetAlpha(unsigned char alpha);

	Texture* GetTexture();

protected:

private:
	Sprite(const Sprite& sprite);
	Sprite& operator=(const Sprite& sprite);

	//Member Data:
public:

protected:
	Texture* m_pTexture;
	int m_x;
	int m_y;

	float m_angle;
	int m_centerX;
	int m_centerY;

	int m_width;
	int m_height;

	int m_alteredWidth;
	int m_alteredHeight;

	unsigned char m_ucAlpha;

private:

};

#endif // __SPRITE_H__
