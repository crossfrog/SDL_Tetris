#pragma once
#include "Core.h"
#include "Vector2.h"

class GameObject {
public:
	Core* core;
	Vector2 position;

	GameObject(Core* core, Vector2 position = Vector2(0, 0)) { this->core = core; this->position = position; }
	virtual void update() {}
	virtual void render() {}
};