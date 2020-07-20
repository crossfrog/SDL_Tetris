#pragma once
#include "GameObject.h"
#include "SpriteData.h"
#include "Vector2.h"

class Sprite : public GameObject {
public:
	SpriteData* spriteData;
	int frameIndex;

	SDL_Rect* srcRect;
	SDL_Rect* dstRect;

	Sprite(Core* core, SpriteData* spriteData) : GameObject(core) {
		this->spriteData = spriteData;
		this->frameIndex = spriteData->frameStart;
		setRectScales();
	}
	void setRectScales();
	void update() override {}
	void render() override;
};