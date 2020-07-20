#pragma once
#include "TileImage.h"
#include "Vector2.h"

class SpriteData {
public:
	TileImage* tileImage;
	int frameStart;
	SpriteData(TileImage* tileImage, int frameStart) { this->tileImage = tileImage; this->frameStart = frameStart; }
};