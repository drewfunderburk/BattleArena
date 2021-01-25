#include "SpaceActor.h"
#include <raylib.h>

SpaceActor::SpaceActor(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float health, float coolDown) : Actor(x, y, collisionRadius, sprite, maxSpeed)
{
    m_health = health;
    m_fireDelay = coolDown;
}

SpaceActor::SpaceActor(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float coolDown) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
    m_health = health;
    m_fireDelay = coolDown;
}

void SpaceActor::update(float deltaTime)
{
    m_velocity = m_velocity - m_velocity / 100;

    //Call super update
    Actor::update(deltaTime);
}

void SpaceActor::takeDamage(float damageVal)
{
	m_health -= damageVal;
}

void SpaceActor::fire()
{
    if (RAYLIB_H::GetTime() > (double)m_lastFireTime + (double)m_fireDelay)
    {
        m_lastFireTime = RAYLIB_H::GetTime();
    }
}