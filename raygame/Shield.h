#pragma once

#include "Actor.h"
#include "Game.h"
#include <Vector2.h>

class Shield : public Actor
{
public:
	Shield() {}

	void onCollision(Actor* other);
};

