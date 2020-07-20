#include "TetrisMap.h"

TetrisMap::TetrisMap(Core* core) : GameObject(core) {
	this->blockController = new BlockController(core, this);
	SDL_Surface* blockSurf = SDL_LoadBMP("assets/tileSet.bmp");
	SDL_Texture* blockTex = SDL_CreateTextureFromSurface(core->renderer, blockSurf);
	SDL_FreeSurface(blockSurf);
	TileImage* blockImage = new TileImage(blockTex, 8, core->blockTileSize);
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 0)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 1)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 2)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 3)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 4)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 5)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 6)));
	blockSet.push_back(new Sprite(core, new SpriteData(blockImage, 7)));
}

void TetrisMap::render() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			int tileID = blockMap[i][j];

			if (tileID == 0) {
				blockSet[0]->position.x = j * blockSet[tileID]->spriteData->tileImage->tileSize.x;
				blockSet[0]->position.y = i * blockSet[tileID]->spriteData->tileImage->tileSize.y;
				blockSet[0]->render();
			}
		}
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			int tileID = blockMap[i][j];
			blockSet[tileID]->position.x = j * blockSet[tileID]->spriteData->tileImage->tileSize.x;
			blockSet[tileID]->position.y = i * blockSet[tileID]->spriteData->tileImage->tileSize.y;

			if (tileID != 0) {
				SDL_Rect* shadowRect = new SDL_Rect;
				shadowRect->w = blockSet[tileID]->spriteData->tileImage->tileSize.x * core->globalScale.x;
				shadowRect->h = blockSet[tileID]->spriteData->tileImage->tileSize.y * core->globalScale.y;
				shadowRect->x = (blockSet[tileID]->position.x + 1) * core->globalScale.x;
				shadowRect->y = (blockSet[tileID]->position.y + 1) * core->globalScale.y;

				SDL_SetRenderDrawColor(core->renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(core->renderer, shadowRect);
				blockSet[tileID]->render();
			}
		}
	}
}