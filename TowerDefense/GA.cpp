#include "GA.h"

GA::GA()
{
	evpop();
}

GA::~GA()
{
}

void GA::Update()
{
	// setting currentindex to -1 shows that it is ready to do GA again, otherwise it is checking fitness of each chrom
	if (currentIndex != -1)
	{
		std::cout << "Index: " << currentIndex << ", Score: " << popnext[currentIndex].fit << std::endl;
		if (mutating) // if mutating, only want to check fitness of that one chrom, so can change back to -1 after fitness was found
		{
			mutating = false;
			popcurrent[currentIndex] = popnext[currentIndex]; // update popcurrent. only need to update currentindex chrom because only that was changed
			currentIndex = -1;
		}
		else if (++currentIndex >= POP_SIZE) // update index. if index greater than max, check for mutation which will change currentindex once finished
		{
			Mutation();

			for (int i = 0; i < POP_SIZE; i++)
			{
				popcurrent[i] = popnext[i]; // update popcurrent before it sorts again in pickchroms
			}
		}
	}
	
	if (currentIndex == -1)
	{
		PickChroms(); // sort popcurrent to have the highest scoring at the front to be used as parents

		for (int i = 0; i < POP_SIZE; i++)
		{
			popnext[i] = popcurrent[i]; // update popnext with the sorted chroms
		}

		Crossover();
	}
}

void GA::SetCurrentScore(int score)
{
	popnext[currentIndex].fit = score;
}

void GA::evpop()
{
	int random;
	//int value;
	srand(time(NULL));
	for (int i = 0; i < POP_SIZE; i++)
	{
		for (int j = 0; j < CHROM_BITS; j++)
		{
			random = (rand() % towerBit::thrower) + 1;
			popcurrent[i].bit[j] = random;
			random = rand() % BOARD_WIDTH;
			popcurrent[i].bitPosX[j] = random;
			random = rand() % BOARD_HEIGHT;
			popcurrent[i].bitPosY[j] = random;
			popcurrent[i].fit = 0;
		}

		popnext[i] = popcurrent[i];
	}
}

void GA::PickChroms()
{
	chrom temp;
	for (int i = 0; i < POP_SIZE; i++)
	{
		for (int j = i + 1; j <= POP_SIZE; j++)
		{
			if (popcurrent[j].fit > popcurrent[i].fit)
			{
				std::cout << "new chroms picked: " << popcurrent[j].fit << std::endl;
				temp = popcurrent[j];
				popcurrent[j] = popcurrent[i];
				popcurrent[i] = temp;
			}
		}
	}

	std::cout << std::endl;
	for (int i = 0; i < POP_SIZE; i++)
	{
		std::cout << "Chrom: ";
		for (int j = 0; j < CHROM_BITS; j++)
		{
			std::cout << popcurrent[i].bit[j] << " ";
		}
		std::cout << std::endl;
		std::cout << "Score: " << popcurrent[i].fit << std::endl;
	}
}

void GA::Crossover()
{
	if (POP_SIZE > 1)
	{
		int random = (rand() % CHROM_BITS) + 1;

		for (int i = 1; i < random; i++) // crossing bits below the cross point
		{
			popnext[2].bit[i] = popnext[0].bit[i];
			popnext[3].bit[i] = popnext[1].bit[i];
		}
		for (int i = random; i < CHROM_BITS; i++) // crossing bits above the cross point
		{
			popnext[2].bit[i] = popnext[1].bit[i];
			popnext[3].bit[i] = popnext[0].bit[i];
		}
		currentIndex = 0;
	}
}

void GA::Mutation()
{
	int random = rand() % 4;

	if (random == 1)
	{
		int bitIndex = rand() % CHROM_BITS;
		int chromIndex = rand() % POP_SIZE;
		// randomise bit
		std::cout << "Mutation! ";
		for (int i = 0; i < CHROM_BITS; i++)
		{
			std::cout << popnext[chromIndex].bit[i];
		}
		std::cout << " -> ";
		short newBit = (rand() % towerBit::thrower) + 1;
		while (newBit == popnext[chromIndex].bit[bitIndex])
		{
			newBit = (rand() % towerBit::thrower) + 1;
		}
		popnext[chromIndex].bit[bitIndex] = newBit;
		for (int i = 0; i < CHROM_BITS; i++)
		{
			std::cout << popnext[chromIndex].bit[i];
		}
		std::cout << std::endl;
		//std::cout << "mutation!" << std::endl;
		currentIndex = chromIndex;
		mutating = true;
	}
	else
	{
		currentIndex = -1;
	}
}