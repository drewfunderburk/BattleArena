#include "Enemy.h"
#include "Bullet.h"
#include "Game.h"
#include <cmath>
#include <raylib.h>

Enemy::Enemy(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float health, float coolDown) : SpaceActor(x, y, collisionRadius, sprite, maxSpeed, health, coolDown)
{
	calcScore();
}

Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float coolDown) : SpaceActor(x, y, collisionRadius, spriteFilePath, maxSpeed, health, coolDown)
{
	calcScore();
}

void Enemy::calcScore()
{
	m_scoreValue = getHealth() + (m_maxSpeed/10) - getFireDelay();
}

void Enemy::fire()
{
	// Spawn new bullet
	Bullet* bullet = new Bullet(getWorldPosition().x, getWorldPosition().y, 10, ' ', 500);

	// Get angle between bullet forward and enemy forward
	float angle = acos(MathLibrary::Vector2::dotProduct(getForward(), bullet->getForward()));
	MathLibrary::Vector2 perpVector = MathLibrary::Vector2(getForward().y, -getForward().x);
	if (MathLibrary::Vector2::dotProduct(bullet->getForward(), perpVector) > 0)
		angle *= -1;

	// Rotate bullet to face the same way as enemy
	bullet->setRotation(angle);

	// Add bullet to scene
	Game::getCurrentScene()->addActor(bullet);
}

void Enemy::update(float deltaTime)
{
	// Look at target
	if (m_target)
		Actor::lookAt(m_target->getWorldPosition());

	// Move forward
	m_acceleration = getForward() * m_maxSpeed;

	// Fire on timer
	if (RAYLIB_H::GetTime() > (double)getLastFireTime() + (double)getFireDelay())
	{
		setLastFireTime(RAYLIB_H::GetTime());
		fire();
	}

	SpaceActor::update(deltaTime);
}