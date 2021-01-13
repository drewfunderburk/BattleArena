#pragma once
#include "SpaceActor.h"

class Enemy : public SpaceActor
{
public:
	Enemy() {}

    /// <param name="health">Amount of hits this Enemy can take before being destroyed</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the Enemy that will be used to detect collisions.</param>
    /// <param name="sprite">That sprite that will be drawn in this Enemys draw function.</param>
    Enemy(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float health, float fireDelay);

    /// <param name="health">The value this Enemy can lose before being destroyed</param>
    /// <param name="coolDown">The time the Enemy must wait before being able to fire again</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the Enemy that will be used to detect collisions.</param>
    /// <param name="sprite">That path for the sprite that will be drawn in this Enemy draw function.</param>
    /// <param name="maxSpeed">The largest the magnitude of the Enemys velocity can be.</param>
    Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float fireDelay);

private:
    /// <summary>
    /// Calculates the score the Player would get if this Enemy is destroyed
    /// </summary>
    void calcScore();

private:
    int m_scoreValue = 1;
};