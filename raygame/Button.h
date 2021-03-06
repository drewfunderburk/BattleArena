#pragma once
#include "Actor.h"

class Button : public Actor
{
public:
	Button(const char *text, float x, float y, int fontSize, int sceneIndex);
	~Button();

	void start();
	void update(float deltaTime);
	void draw();

private:
	const char *m_text;
	float m_lastTime;
	int m_xPos;
	int m_yPos;
	int m_fontSize;
	int m_sceneIndex;
};

