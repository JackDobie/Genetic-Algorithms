#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//32 x 18
#define BOARD_WIDTH_FULL 32
#define BOARD_HEIGHT_FULL 18
#define BOARD_WIDTH 24 // 32 is the full width but after 24 towers cannot attack the track
#define BOARD_HEIGHT 17 // 18 is full width but too low

// number of chroms
#define POP_SIZE 10
// number of bits per chrom
#define CHROM_BITS 6
// number of parents used in crossover
#define CROSSOVER_PARENTS 2
// the index of the crossover point. set to -1 to be random.
#define CROSSOVER_POINT (CHROM_BITS / 2)
// number of chroms to be randomly generated in picknewchroms()
#define NEW_CHROMS 5

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

	// order the chroms in popcurrent
	void PickChroms();
	// crossover parents to the children
	void Crossover();
	// random chance to mutate a bit, changing its tower and position
	bool Mutation();
	// random chance to pick new chroms. creates random bits for the lowest scoring towers. amount defined by NEW_CHROMS
	void PickNewChroms();

	chrom popcurrent[POP_SIZE];
	chrom popnext[POP_SIZE];

	int currentIndex = 0;

	// mutating will be true when checking fitness of mutation. needed to avoid checking all chroms.
	bool mutating = false;
	
	// will be true when just picked new chroms. prevents it from picking new chroms until sorted again
	bool pickedNewChroms = false;
};