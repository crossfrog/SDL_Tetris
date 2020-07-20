#pragma once
#include "SDL.h"

class TileImage {
public:
	SDL_Texture* texture;
	int tilesPerRow;
	Vector2 tileSize;
	TileImage(SDL_Texture* texture, int tilesPerRow, Vector2 tileSize) { this->texture = texture; this->tilesPerRow = tilesPerRow; this->tileSize = tileSize; }
};