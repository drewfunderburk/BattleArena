#include "SpaceActor.h"

SpaceActor::SpaceActor(float health, float coolDown, float x, float y, float collisionRadius, char icon, float maxSpeed) : Actor(x, y, collisionRadius, icon, maxSpeed)
{
    m_health = health;
    m_fireDelay = coolDown;
}

SpaceActor::SpaceActor(float health, float coolDown, float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed) : Actor(x, y, collisionRadius, sprite, maxSpeed)
{
    m_health = health;
    m_fireDelay = coolDown;
}

SpaceActor::SpaceActor(float health, float coolDown, float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
    m_health = health;
    m_fireDelay = coolDown;
}

void SpaceActor::takeDamage(float damageVal)
{
	m_health -= damageVal;
}

void SpaceActor::fire()
{
}