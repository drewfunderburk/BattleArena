#include "Bullet.h"
#include "Game.h"
#include "raylib.h"

Bullet::Bullet(float x, float y, float collisionRadius, char icon, float maxSpeed) : Actor(x, y, collisionRadius, icon, maxSpeed)
{ }

Bullet::Bullet(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed) : Actor(x, y, collisionRadius, sprite, maxSpeed)
{ }

Bullet::Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{ }

void Bullet::update(float deltaTime)
{
	// If this bullet has left the playable area, delete it
	float offset = 50;
	if (getWorldPosition().x < -offset ||
		getWorldPosition().x > RAYLIB_H::GetScreenWidth() + offset ||
		getWorldPosition().y < -offset ||
		getWorldPosition().y > RAYLIB_H::GetScreenHeight() + offset)
	{
		Game::destroy(this);
		return;
	}

	m_acceleration = getForward() * m_maxSpeed;
	Actor::update(deltaTime);
}