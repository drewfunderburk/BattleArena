#include "Player.h"
#include "Game.h"
#include <cmath>
#include <iostream>

void Player::fire()
{
	if (RAYLIB_H::GetTime() > (double)m_lastFireTime + (double)m_fireDelay)
	{
		m_lastFireTime = RAYLIB_H::GetTime();
		m_acceleration = MathLibrary::Vector2(getForward() * m_boostAmount);
	}
}


Player::Player(float x, float y, float rotation) : SpaceActor(x, y, 70, "/Images/Player.png", 10, 100, 1)
{
	m_boostAmount = 2000;
	m_maxSpeed = 500;
}

Player::Player(MathLibrary::Vector2 position, float rotation) : Player(position.x, position.y, rotation) {}

void Player::onCollision(Actor* other)
{
	float distanceToOther = (other->getWorldPosition() - getWorldPosition()).getMagnitude();

	if (distanceToOther / 2 < m_actualCollisionRadius)
	{
		// Actually collided with the player, game over
		//Game::setGameOver(true);
		std::cout << "Player" << std::endl;
		return;
	}
	
	float angleToOther = acos(MathLibrary::Vector2::dotProduct(other->getWorldPosition().getNormalized(), getForward()));
	if (angleToOther < m_shieldAngle)
	{
		std::cout << "Shield" << std::endl;
		Game::destroy(other);
	}
}

void Player::update(float deltaTime)
{
	// Get input from the player and convert to vector
	MathLibrary::Vector2 direction = getForward() * RAYLIB_H::IsKeyDown(KEY_W);

	m_acceleration = direction * m_speed;

	// Get boost input from player and attempt to boost
	if (RAYLIB_H::IsKeyDown(KEY_SPACE))
		fire();

	// Look at mouse cursor
	SpaceActor::lookAt(MathLibrary::Vector2(RAYLIB_H::GetMousePosition().x, RAYLIB_H::GetMousePosition().y));

	// Call super update
	SpaceActor::update(deltaTime);
}

void Player::draw()
{
	Actor::draw();

	// Show actual collision
	DrawCircleLines(getWorldPosition().x, getWorldPosition().y, m_actualCollisionRadius, GREEN);
}