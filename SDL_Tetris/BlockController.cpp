#include "BlockController.h"
#include <iostream>

void BlockController::update() {
	if (core->inputDown) {
		currentMoveDownInterval = moveDownIntervalFast;
	}
	else {
		currentMoveDownInterval = moveDownInterval;
	}

	if (core->inputRight && core->passedTime - moveTimeSample > moveWaitTime) {
		moveTimeSample = core->passedTime;
		bool canMoveRight = checkRightCollision(currentBlock->blockShape);
		

		if (canMoveRight) { position.x += core->blockTileSize.x; }
	}

	else if (core->inputLeft && core->passedTime - moveTimeSample > moveWaitTime) {
		moveTimeSample = core->passedTime;
		bool canMoveLeft = checkLeftCollision(currentBlock->blockShape);
		

		if (canMoveLeft) { position.x -= core->blockTileSize.x; }
	}

	bool canMoveDown = true;
	if (core->passedTime % currentMoveDownInterval == 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (currentBlock->blockShape->at(i).at(j)) { // if current tile on controlled block is solid
					if (tetrisMap->blockMap[(position.y / core->blockTileSize.y) + i + 1][(position.x / core->blockTileSize.x) + j]) { // if one below the tile is solid on map
						canMoveDown = false;
					}
				}
			}
		}
		if (canMoveDown) { position.y += core->blockTileSize.y; }
		else { startNewBlock(); }
	}

	if (core->inputPrimary && !prevPrimaryPress) {

		BlockShape* blockBuffer = new BlockShape;

		bool rotationAcceptable = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				blockBuffer->at(j).at(3 - i) = currentBlock->blockShape->at(i).at(j);
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (tetrisMap->blockMap[(position.y / core->blockTileSize.y) + i][(position.x / core->blockTileSize.x) + j] && blockBuffer->at(i).at(j)) {
					rotationAcceptable = false;
				}
			}
		}
		if (rotationAcceptable) {
			bool rotationNotOnWall = checkLeftCollision(blockBuffer) && checkRightCollision(blockBuffer);

			if (rotationNotOnWall) {
				currentBlock->blockShape = blockBuffer;
			}
		}
	}

	prevPrimaryPress = core->inputPrimary;
}

bool BlockController::checkLeftCollision(BlockShape* shape) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape->at(i).at(j)) { // if tile on moving block is solid
				if (tetrisMap->blockMap[(position.y / core->blockTileSize.y) + i][(position.x / core->blockTileSize.x) + j - 1]) { // if block is already occupied on map
					return false;
				}
				if (j + (position.x / core->blockTileSize.x) < 1) { // if block hits edge
					return false;
				}
			}
		}
	}
	return true;
}

bool BlockController::checkRightCollision(BlockShape* shape) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape->at(i).at(j)) { // if tile on moving block is solid
				if (tetrisMap->blockMap[(position.y / core->blockTileSize.y) + i][(position.x / core->blockTileSize.x) + j + 1]) { // if block is already occupied on map
					return false;
				}
				if (j + (position.x / core->blockTileSize.x) > 8) { // if block hits edge
					return false;
				}
			}
		}
	}
	return true;
}

void BlockController::startNewBlock() {

	if (currentBlock) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (currentBlock->blockShape->at(i).at(j)) {
					tetrisMap->blockMap[(position.y / core->blockTileSize.y) + i][(position.x / core->blockTileSize.x) + j] = currentBlock->tileID;
				}
			}
		}
	}
	this->currentBlock = const_cast<TetrisBlock*>(&allBlocks[rand() % 7]);
	this->position.x = core->blockTileSize.x * 3;
	this->position.y = 0;

	for (int i = 0; i < 20; i++) {
		bool rowFull = true;
		for (int j = 0; j < 10; j++) {
			if (tetrisMap->blockMap[i][j] == 0) {
				rowFull = false;
			}
		}
		if (rowFull) {
			destroyRow(i);
		}
	}
}

void BlockController::destroyRow(int rowID) {
	for (int i = rowID; i > 0; i--) {
		for (int j = 0; j < 10; j++) {
			tetrisMap->blockMap[i][j] = tetrisMap->blockMap[i - 1][j];
		}
	}
}

void BlockController::render() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (currentBlock->blockShape->at(i).at(j)) {
				Sprite* workingTile = tetrisMap->blockSet[currentBlock->tileID];
				workingTile->position.x = position.x + j * workingTile->spriteData->tileImage->tileSize.x;
				workingTile->position.y = position.y + i * workingTile->spriteData->tileImage->tileSize.y;

				SDL_Rect* shadowRect = new SDL_Rect;
				shadowRect->w = core->blockTileSize.x * core->globalScale.x;
				shadowRect->h = core->blockTileSize.y * core->globalScale.y;
				shadowRect->x = (tetrisMap->blockSet[currentBlock->tileID]->position.x + 1) * core->globalScale.x;
				shadowRect->y = (tetrisMap->blockSet[currentBlock->tileID]->position.y + 1) * core->globalScale.y;

				SDL_SetRenderDrawColor(core->renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(core->renderer, shadowRect);

				workingTile->render();
			}
		}
	}
}