#pragma once

#include <Vector2.h>
#include"SpaceActor.h"
#include <raylib.h>
#include <typeinfo>
#include "Sprite.h"

class Player : public SpaceActor
{
private:
	/// <summary>
	/// Propel the player along their forward axis at a given speed
	/// </summary>
	void fire();

public:
	~Player();
	/// <param name="position">Position</param>
	/// <param name="rotation">Rotation</param>
	Player(MathLibrary::Vector2 position, float rotation);

	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="rotation">Rotation</param>
	Player(float x, float y, float rotation);

	void onCollision(Actor* other);
	void update(float deltaTime);
	void draw();

	int getScore() { return m_score; }

private:
	Sprite* m_shieldSprite;
	float m_actualCollisionRadius = 15;
	float m_shieldAngle = PI / 2.5;
	int m_score = 0;
	float m_boostAmount;
	float m_health = 10;
	float m_fireDelay = 0.3;
	float m_lastFireTime = 0;
	float m_speed = 30;
};