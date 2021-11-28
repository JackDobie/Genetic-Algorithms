#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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
	short int bit[CHROM_BITS];
	int fit;
};

class GA
{
public:
	GA();
	~GA();
	void Update();
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