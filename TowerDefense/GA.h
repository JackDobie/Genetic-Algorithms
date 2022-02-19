#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//32 x 18
#define BOARD_WIDTH_FULL 32
#define BOARD_HEIGHT_FULL 18
#define BOARD_WIDTH 24 // 32 is the full width but after 24 towers cannot attack the track
#define BOARD_HEIGHT 17 // 18 is full width but too low

#define POP_SIZE 6
#define CHROM_BITS 6

enum towerBit
{
	empty,
	slammer,
	swinger,
	thrower
};

struct chrom
{
	short int bitPosX[CHROM_BITS];
	short int bitPosY[CHROM_BITS];
	short int bit[CHROM_BITS];
	int fit;
};

//const int midpoint = CHROM_BITS > 1 ? CHROM_BITS / 2 : CHROM_BITS;
class GA
{
public:
	GA();
	~GA();
	void Update();

	chrom* GetPopCurrent() { return popcurrent; }
	chrom* GetPopNext() { return popnext; }

	void SetCurrentScore(int score);

	int GetCurrentIndex() { return currentIndex; }
private:
	void evpop();
	//int x(chrom popcurrent);
	//int y(int x);
	void PickChroms();
	void Crossover();
	void Mutation();

	chrom popcurrent[POP_SIZE];
	chrom popnext[POP_SIZE];

	int currentIndex = 0;

	// mutating will be true when checking fitness of mutation. needed to avoid checking all chroms.
	bool mutating = false;
};