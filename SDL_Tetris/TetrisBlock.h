#pragma once
#include <time.h>
#include <stdlib.h>
#include <array>

using BlockShape = std::array<std::array<bool, 4>, 4>;

class TetrisBlock {
public:
	BlockShape* blockShape;
	int tileID;
	TetrisBlock(BlockShape* blockShape, int tileID) {
		this->blockShape = blockShape;
		this->tileID = tileID;
	}
};

const BlockShape blockI = {
{
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0}
} };

const BlockShape blockL = {
{
	{0,0,0,0},
	{1,0,0,0},
	{1,1,1,0},
	{0,0,0,0}
} };

const BlockShape blockJ = {
{
	{0,0,0,0},
	{0,0,1,0},
	{1,1,1,0},
	{0,0,0,0}
} };

const BlockShape blockO = {
{
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}
} };


const BlockShape blockS = {
{
	{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0}
} };
const BlockShape blockT = {
{
	{0,0,0,0},
	{0,1,0,0},
	{1,1,1,0},
	{0,0,0,0}
} };

const BlockShape blockZ = {
{
	{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0}
} };