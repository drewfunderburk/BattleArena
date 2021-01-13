#include "Player.h"
#include <raylib.h>
#include "Actor.h"

Player::Player(MathLibrary::Vector2 position, float rotation)
{

}

Player::Player(float x, float y, float rotation)
{

}

void Player::boost(float value)
{

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

	// Call super update
	SpaceActor::Actor::update(deltaTime);
}
