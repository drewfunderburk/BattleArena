#pragma once
#include "Actor.h"

class SpaceActor : public Actor
{
public:
	SpaceActor() {}

    /// <param name="health">Amount of hits this SpaceActor can take before being destroyed</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
	SpaceActor(float health, float coolDown, float x, float y, float collisionRadius, char icon, float maxSpeed);

    /// <param name="health">Amount of hits this SpaceActor can take before being destroyed</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="sprite">That sprite that will be drawn in this actors draw function.</param>
    SpaceActor(float health, float coolDown, float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed);

    /// <param name="health">The value this SpaceActor can lose before being destroyed</param>
    /// <param name="coolDown">The time the SpaceActor must wait before being able to fire again</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="sprite">That path for the sprite that will be drawn in this actors draw function.</param>
    /// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
    SpaceActor(float health, float coolDown, float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);

    /// <summary>
    /// Subtracts the passed in float from m_health
    /// </summary>
    /// <param name="damageVal">The amount being taken from m_health</param>
    void takeDamage(float damageVal);

private:
    /// <summary>
    /// Will create a Bullet
    /// </summary>
    void fire();

private:
    float m_health = 10;
    float m_fireDelay = 1;
};