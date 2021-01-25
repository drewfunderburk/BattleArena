#include "TextBox.h"

TextBox::TextBox(const char* text)
{
	m_text = text;
}

TextBox::TextBox(float x, float y, const char* text) : Actor(x, y, 1, ' ', 1)
{
	m_xPos = x;
	m_yPos = y;
	m_text = text;
}

TextBox::TextBox(float x, float y, const char* text, float size) : Actor(x, y, size, ' ', 1)
{
	m_xPos = x;
	m_yPos = y;
	m_text = text;
	m_size = size;
}

void TextBox::update(float deltaTime)
{

}

void TextBox::draw()
{
	RAYLIB_H::DrawText(m_text, m_xPos, m_yPos, m_size, BLACK);
}