#pragma once
#include "GameObject.h"
#include "TetrisBlock.h"
#include "TetrisMap.h"

class TetrisMap;

class BlockController : public GameObject {
public:
	TetrisBlock* currentBlock;
	TetrisMap* tetrisMap;

	BlockController(Core* core, TetrisMap* tetrisMap) : GameObject(core) {
		this->tetrisMap = tetrisMap;
		srand(time(NULL));
		startNewBlock();
	}
	
	const int moveDownInterval = 5;
	const int moveDownIntervalFast = 1;

	int currentMoveDownInterval = moveDownInterval;

	void startNewBlock();
	void destroyRow(int rowID);

	bool prevPrimaryPress = false;

	bool checkLeftCollision(BlockShape* shape);
	bool checkRightCollision(BlockShape* shape);
	
	Uint32 moveTimeSample = 0;
	const int moveWaitTime = 1;

	void update() override;
	void render() override;

	const std::array<TetrisBlock, 7> allBlocks{
	TetrisBlock(const_cast<BlockShape*>(&blockI), 1),
	TetrisBlock(const_cast<BlockShape*>(&blockL), 2),
	TetrisBlock(const_cast<BlockShape*>(&blockJ), 3),
	TetrisBlock(const_cast<BlockShape*>(&blockO), 4),
	TetrisBlock(const_cast<BlockShape*>(&blockS), 5),
	TetrisBlock(const_cast<BlockShape*>(&blockT), 6),
	TetrisBlock(const_cast<BlockShape*>(&blockZ), 7)
	};
};