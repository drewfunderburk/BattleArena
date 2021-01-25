#pragma once
#include "Actor.h"
#include "raylib.h"

class TextBox : public Actor
{
public:
	TextBox() {};
	TextBox(const char* text);
	TextBox(float x, float y, const char* text);
	TextBox(float x, float y, const char* text, float size);

	void update(float deltaTime);
	void draw();

private:
	int m_xPos = 1;
	int m_yPos = 1;
	const char* m_text;
	float m_size = 10;
};