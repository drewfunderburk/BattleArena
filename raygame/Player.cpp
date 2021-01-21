#include "Player.h"
#include <raylib.h>
#include "Game.h"

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

void Player::onCollision(Actor* other)
{
	//if (other is in shieldRadius && other is not in collisionRadius)
	//{
	//	Check dot product;
	//	if (other is in shield angle)
	//		delete other;
	//}
	//else if (other is in collision radius)
	//	do normal collision stuffs;
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