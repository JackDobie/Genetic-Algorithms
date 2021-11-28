#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define BOARD_WIDTH 32
#define BOARD_HEIGHT 18
#define POP_SIZE BOARD_WIDTH*BOARD_HEIGHT

struct chrom
{
	short int bit[6];
	int fit;
};

class GA
{
public:
	GA();
	~GA();
	void Update();
private:
	void evpop(chrom popcurrent[4]);
	int x(chrom popcurrent);
	int y(int x);
	void PickChroms(chrom popcurrent[4]);
	void Crossover(chrom popnext[4]);
	void Mutation(chrom popnext[4]);

	chrom popcurrent[4];
	chrom popnext[4];
};