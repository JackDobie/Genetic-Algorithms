#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//32 x 18
#define BOARD_WIDTH 24 // 32 is the full width but after 24 towers cannot attack the track
#define BOARD_HEIGHT 18

#define POP_SIZE 4
#define CHROM_BITS 5

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

class GA
{
public:
	GA();
	~GA();
	void Update();

	chrom* GetPop() { return popcurrent; }

	void SetCurrentScore(int score);
private:
	void evpop(chrom popcurrent[POP_SIZE]);
	//int x(chrom popcurrent);
	//int y(int x);
	void PickChroms(chrom popcurrent[POP_SIZE]);
	void Crossover(chrom popnext[POP_SIZE]);
	void Mutation(chrom popnext[POP_SIZE]);

	chrom popcurrent[POP_SIZE];
	chrom popnext[POP_SIZE];
};