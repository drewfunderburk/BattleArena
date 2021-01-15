#include "Player.h"
#include <raylib.h>

Player::Player(MathLibrary::Vector2 position, float rotation) : SpaceActor(position.x, position.y, 10, "/Images/Player.png", 10, 100, 1)
{
	m_boostAmount = 50;
}

Player::Player(float x, float y, float rotation) : SpaceActor(x, y, 10, "/Images/Player.png", 10, 100, 1)
{
	m_boostAmount = 50;
}

void Player::boost(float value)
{

}

void Player::start()
{
	m_shield = new Shield();
	//m_shield->setLocalPosition(MathLibrary::Vector2(20, 0));
	Game::getCurrentScene()->addActor(m_shield);
	addChild(m_shield);
}

void Player::update(float deltaTime)
{
	// Get input from the player and convert to vector
	int xDirection = -RAYLIB_H::IsKeyDown(KEY_A) + RAYLIB_H::IsKeyDown(KEY_D);
	int yDirection = -RAYLIB_H::IsKeyDown(KEY_W) + RAYLIB_H::IsKeyDown(KEY_S);
	MathLibrary::Vector2 direction = MathLibrary::Vector2(xDirection, yDirection);

	// Get fire input from player and attempt to fire
	if (RAYLIB_H::IsKeyDown(KEY_SPACE))
		SpaceActor::fire();

	m_acceleration = direction * m_maxSpeed;

	// Look at mouse cursor
	SpaceActor::lookAt(MathLibrary::Vector2(RAYLIB_H::GetMousePosition().x, RAYLIB_H::GetMousePosition().y));

	// Call super update
	SpaceActor::update(deltaTime);
}