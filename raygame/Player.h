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
	/// <param name="value">How much force to add</param>
	void boost(float value);

public:
	/// <param name="position">Position</param>
	/// <param name="rotation">Rotation</param>
	Player(MathLibrary::Vector2 position, float rotation);

	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="rotation">Rotation</param>
	Player(float x, float y, float rotation);

	void update(float deltaTime);
};