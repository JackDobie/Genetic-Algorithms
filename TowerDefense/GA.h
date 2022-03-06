#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::string;
using std::vector;

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

	bool operator ==(chrom c)
	{
		for (int i = 0; i < CHROM_BITS; i++)
		{
			if (this->bit[i] != c.bit[i])
			{
				return false;
			}
			if (this->bitPosX[i] != c.bitPosX[i])
			{
				return false;
			}
			if (this->bitPosY[i] != c.bitPosY[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(chrom c)
	{
		return !(operator==(c));
	}
};

class GA
{
public:
	GA();
	~GA();
	void Update();

	chrom* GetPopCurrent() { return popcurrent; }
	chrom* GetPopNext() { return popnext; }

	void SetCurrentScore(int score);

	int GetCurrentIndex();
private:
	void evpop();

	// order the chroms in popcurrent by fitness
	void PickChroms();
	// select which chroms should be parents
	void Selection();

	void TournamentSelection();
	void RouletteSelection();
	void SteadyStateSelection();
	void ElitismSelection();
	void BoltzmannSelection();
	// the way parents are selected
	// 0=tournament, 1=roulette
	const int selectionType = 1;

	// crossover parents to the children
	void Crossover();
	// the index of the crossover point. set to -1 to be random.
	const int crossoverPoint = CHROM_BITS / 2;

	// random chance to mutate a bit, changing its tower and position
	bool Mutation();

	// random chance to pick new chroms. creates random bits for the lowest scoring towers. amount defined by NEW_CHROMS
	void PickNewChroms();
	// number of chroms to be randomly generated in picknewchroms()
	const int newChroms = 4;

	// save the current best chroms to a log file
	void LogBestChroms();

	chrom popcurrent[POP_SIZE];
	chrom popnext[POP_SIZE];

	// the current index within chromsToTest
	int currentIndex = 0;
	// stores the indexes of chroms that have changed and need testing
	vector<int> chromsToTest = vector<int>();

	// mutating will be true when checking fitness of mutation. needed to avoid checking all chroms.
	bool mutating = false;
	
	// will be true when just picked new chroms. prevents it from picking new chroms until sorted again
	bool pickedNewChroms = false;

	std::ofstream logFile = std::ofstream("Log.txt", std::ios_base::app);
};