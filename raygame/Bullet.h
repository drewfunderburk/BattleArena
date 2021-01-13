#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet() {}

    /// <param name="lifeTime">The time the Bullet can travel without colliding with something before it is destroyed</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the Bullet that will be used to detect collisions.</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxSpeed">The largest the magnitude of the Bullets velocity can be.</param>
    Bullet(float x, float y, float collisionRadius, char icon, float maxSpeed);

    /// <param name="lifeTime">The time the Bullet can travel without colliding with something before it is destroyed</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the Bullets that will be used to detect collisions.</param>
    /// <param name="sprite">That sprite that will be drawn in this Bullets draw function.</param>
    Bullet(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed);

    /// <param name="lifeTime">The time the Bullet can travel without colliding with something before it is destroyed</param>
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the Bullets that will be used to detect collisions.</param>
    /// <param name="sprite">That path for the sprite that will be drawn in this Bullets draw function.</param>
    /// <param name="maxSpeed">The largest the magnitude of the Bullets velocity can be.</param>
    Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);

    void update(float deltaTime);
};