#pragma once

#include <Vector2.h>
class Player
{
private:
	float m_fireDelay;
	float m_boostAmount;

private:
	void boost();

public:
	Player(MathLibrary::Vector2 position, float rotation);
};

