#include "Bullet.h"

Bullet::Bullet(float x, float y, float collisionRadius, char icon, float maxSpeed) : Actor(x, y, collisionRadius, icon, maxSpeed)
{ }

Bullet::Bullet(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed) : Actor(x, y, collisionRadius, sprite, maxSpeed)
{ }

Bullet::Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{ }

void Bullet::update(float deltaTime)
{
	rotate(0.1);
	m_acceleration = getForward() * m_maxSpeed;
	Actor::update(deltaTime);
}