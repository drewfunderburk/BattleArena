#include "Player.h"
#include "Game.h"
#include <cmath>

void Player::fire()
{
	if (RAYLIB_H::GetTime() > (double)m_lastFireTime + (double)m_fireDelay)
	{
		m_lastFireTime = RAYLIB_H::GetTime();
		m_acceleration = MathLibrary::Vector2(getForward() * m_boostAmount);
	}
}

Player::Player(MathLibrary::Vector2 position, float rotation) : SpaceActor(position.x, position.y, 10, "/Images/Player.png", 10, 100, 1)
{
	m_shield = new Actor();
	m_boostAmount = 2000;
}

Player::Player(float x, float y, float rotation) : SpaceActor(x, y, 10, "/Images/Player.png", 10, 100, 1)
{
	m_shield = new Actor(getWorldPosition().x, getWorldPosition().y, 1, "/Images/Player.png", 10);
	m_boostAmount = 2000;
	m_maxSpeed = 500;
}

bool Player::checkCollision(Actor* other)
{
	//float distance = (other->getWorldPosition() - getWorldPosition()).getMagnitude();

	if (other->checkCollision(m_shield) && !other->checkCollision(this))
	{
		MathLibrary::Vector2 direction = other->getWorldPosition() - getWorldPosition();
		float angle = acos(MathLibrary::Vector2::dotProduct(getForward(), direction));

		//Check to see if the collision is on the shield side of the Player
		if (angle < m_shieldLHS && angle > m_shieldRHS)
		{
			//delete(other);
			return true;
		}
	}

	Actor::checkCollision(other);
}

void Player::start()
{
	m_shield->setLocalPosition(MathLibrary::Vector2(20, 0));
	Game::getCurrentScene()->addActor(m_shield);
	addChild(m_shield);

	//Call super
	Actor::start();
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