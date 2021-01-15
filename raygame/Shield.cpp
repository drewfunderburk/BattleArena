#include "Shield.h"


void Shield::onCollision(Actor* other)
{
	Game::destroy(other);
}