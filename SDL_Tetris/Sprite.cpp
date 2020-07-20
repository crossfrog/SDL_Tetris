#include "Sprite.h"

void Sprite::setRectScales() {
	this->srcRect = new SDL_Rect;
	srcRect->w = spriteData->tileImage->tileSize.x;
	srcRect->h = spriteData->tileImage->tileSize.y;

	this->dstRect = new SDL_Rect;
	dstRect->w = spriteData->tileImage->tileSize.x * core->globalScale.x;
	dstRect->h = spriteData->tileImage->tileSize.y * core->globalScale.y;
}

void Sprite::render() {
	srcRect->x = (frameIndex % spriteData->tileImage->tilesPerRow) * core->blockTileSize.x;
	srcRect->y = (frameIndex / spriteData->tileImage->tilesPerRow) * core->blockTileSize.y;

	dstRect->x = position.x * core->globalScale.x;
	dstRect->y = position.y * core->globalScale.y;

	SDL_RenderCopy(core->renderer, spriteData->tileImage->texture, srcRect, dstRect);
}