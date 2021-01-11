#include "Player.h"
#include <raylib.h>
#include "Actor.h"

class Player : private Actor
{
public:
	Player() {}

private:
	void boost()
	{

	}

	void Update(float deltaTime)
	{
		// Get input from the player and convert to vector
		int xDirection = -RAYLIB_H::IsKeyDown(KEY_A) + RAYLIB_H::IsKeyDown(KEY_D);
		int yDirection = -RAYLIB_H::IsKeyDown(KEY_W) + RAYLIB_H::IsKeyDown(KEY_S);
		MathLibrary::Vector2 direction = MathLibrary::Vector2(xDirection, yDirection);
	}
};