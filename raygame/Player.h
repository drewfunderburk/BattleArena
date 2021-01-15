#pragma once

#include <Vector2.h>
#include"SpaceActor.h"

class Player : public SpaceActor
{
private:
	float m_boostAmount;

private:
	/// <summary>
	/// Propel the player along their forward axis at a given speed
	/// </summary>
	void fire();

public:
	/// <param name="position">Position</param>
	/// <param name="rotation">Rotation</param>
	Player(MathLibrary::Vector2 position, float rotation);

	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="rotation">Rotation</param>
	Player(float x, float y, float rotation);

	void update(float deltaTime);

private:
	float m_health = 10;
	float m_fireDelay = 1;
	float m_lastFireTime = 0;
	float m_speed = 10;
};