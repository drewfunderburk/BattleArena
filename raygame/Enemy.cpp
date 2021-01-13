#include "Enemy.h"

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