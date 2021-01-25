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


Player::Player(float x, float y, float rotation) : SpaceActor(x, y, 50, "Images/Player.png", 10, 100, 1)
{
	m_boostAmount = 2000;
	m_maxSpeed = 500;

	m_shieldSprite = new Sprite("Images/Shield.png");
	m_shieldSprite->setScale(128);
}

Player::Player(MathLibrary::Vector2 position, float rotation) : Player(position.x, position.y, rotation) {}

void Player::onCollision(Actor* other)
{
	// Get distance to other collider to check if it's hit the shield or the player
	float distanceToOther = (other->getWorldPosition() - getWorldPosition()).getMagnitude();

	// Get the direction to the collided object
	MathLibrary::Vector2 direction = (other->getWorldPosition() - getWorldPosition()).getNormalized();
	// Get the dotproduct of the direction and the player's forward vector
	float dotProduct = MathLibrary::Vector2::dotProduct(direction, getForward());
	// Check if the angle to the other collider would place it on the shield
	float angleToOther = acos(dotProduct);

	if (angleToOther < m_shieldAngle)
	{
		// Collided with shield, destroy the object
		Game::destroy(other);
		m_score++;
		return;
	}

	if (distanceToOther / 2 < m_actualCollisionRadius)
	{
		// Actually collided with the player, game over
		Game::setCurrentScene(2);
		return;
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
	//DrawCircleLines(getWorldPosition().x, getWorldPosition().y, m_actualCollisionRadius, GREEN);
	m_shieldSprite->draw(*m_globalTransform);
}