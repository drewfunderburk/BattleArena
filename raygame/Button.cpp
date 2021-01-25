#include "Button.h"
#include "raylib.h"
#include "Game.h"
#include <iostream>

Button::Button(const char* text, float x, float y, int fontSize, int sceneIndex) : Actor(x, y, 1, ' ', 1)
{
	m_xPos = x;
	m_yPos = y;
	m_text = text;
	m_fontSize = fontSize;
	m_sceneIndex = sceneIndex;
}

Button::~Button()
{
	delete m_text;
}

void Button::update(float deltaTime)
{
	if (m_sceneIndex == -1)
	{
		Game::setGameOver(true);
		return;
	}
	if (RAYLIB_H::GetKeyPressed())
		Game::setCurrentScene(m_sceneIndex);
}

void Button::draw()
{
	RAYLIB_H::DrawText(m_text, m_xPos, m_yPos, m_fontSize, BLACK);
}
