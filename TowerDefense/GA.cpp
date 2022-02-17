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
	//for (int i = 0; i < POP_SIZE; i++)
	//{
	//	popnext[i] = popcurrent;
	//}

	PickChroms();
	Crossover();
	Mutation();

	popcurrent = &popnext[currentIndex];

	//for (int i = 0; i < POP_SIZE; i++)
	//{
	//	popcurrent[i] = popnext[i];
	//}
}

void GA::SetCurrentScore(int score)
{
	popcurrent->fit = score;
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
			popnext[i].bit[j] = random;
			random = rand() % BOARD_WIDTH;
			popnext[i].bitPosX[j] = random;
			random = rand() % BOARD_HEIGHT;
			popnext[i].bitPosY[j] = random;
		}
		//value = x(popcurrent[i]);
		//popcurrent[i].fit = y(x(popcurrent[i]));
		//std::cout << "popcurrent[" << i << "] "/*Value: " << value*/ << ", Fitness = " << popcurrent[i].fit << std::endl;
		//printf("\n popcurrent[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i, popcurrent[i].bit[5], popcurrent[i].bit[4], popcurrent[i].bit[3], popcurrent[i].bit[2],	popcurrent[i].bit[1], popcurrent[i].bit[0], value, popcurrent[i].fit);
	}
}

//int GA::x(chrom popcurrent)
//{
//	int z = (popcurrent.bit[0] * 1) + (popcurrent.bit[1] * 2) +(popcurrent.bit[2] * 4) + (popcurrent.bit[3] * 8) + (popcurrent.bit[4] * 16);
//	if (popcurrent.bit[5] == 1)
//	{
//		z = z * (-1);
//	}
//	return(z);
//}
//
//int GA::y(int x)
//{
//	int y = -(x * x) + 5;
//	return(y);
//}

void GA::PickChroms()
{
	chrom temp;
	for (int i = 0; i < POP_SIZE - 1; i++)
	{
		if (popnext[i].fit > popcurrent->fit)
		{
			std::cout << "new chroms picked: " << popnext[i + 1].fit - popnext[i].fit << std::endl;
			currentIndex = i;
			popcurrent = &popnext[i];
			/*temp = popnext[i + 1];
			popnext[i + 1] = popnext[i];
			popnext[i] = temp;*/
		}
	}

	//for (int i = 0; i < POP_SIZE; i++)
	//{
		//std::cout << "\nSorting: popnext[" << i << "] fitness=" << popcurrent[i].fit;
		//printf("\nSorting:popnext[%d] fitness=%d", i, popcurrent[i].fit); // print the result
	//}
	//std::cout << std::endl;
}

void GA::Crossover()
{
	if (POP_SIZE > 1)
	{
		// int random = (rand() % CHROM_BITS) + 1;

		chrom pops[POP_SIZE];
		for (int i = 0; i < POP_SIZE; i++)
		{
			pops[i] = popnext[i];
		}

		// cross over bits
		for (int i = 0; i < POP_SIZE; i += 2)
		{
			/*std::cout << i << std::endl;
			for (int i = 0; i < POP_SIZE; i++)
			{
				for (int j = 0; j < CHROM_BITS; j++)
				{
					std::cout << popnext[i].bit[j];
				}
				std::cout << std::endl;
			}*/

			for (int j = 0; j < CHROM_BITS; j++)
			{
				if (j >= midpoint)
				{
					short tempBit = pops[i].bit[j];
					pops[i].bit[j] = pops[i + 1].bit[j];
					pops[i + 1].bit[j] = tempBit;
				}
			}

			/*std::cout << std::endl;
			for (int i = 0; i < POP_SIZE; i++)
			{
				for (int j = 0; j < CHROM_BITS; j++)
				{
					std::cout << pops[i].bit[j];
				}
				std::cout << std::endl;
			}*/
		}

		for (int i = 0; i < POP_SIZE; i++)
		{
			popnext[i] = pops[i];
		}
	}
}

void GA::Mutation()
{
	int random = rand() % 50;

	if (random == 10)
	{
		int bitIndex = rand() % CHROM_BITS;
		int chromIndex = rand() % POP_SIZE;
		// randomise bit
		std::cout << "Mutation! ";
		for (int i = 0; i < CHROM_BITS; i++)
		{
			std::cout << popnext[chromIndex].bit[i];
		}
		std::cout << " ";
		popnext[chromIndex].bit[bitIndex] = (rand() % towerBit::thrower) + 1;
		for (int i = 0; i < CHROM_BITS; i++)
		{
			std::cout << popnext[chromIndex].bit[i];
		}
		std::cout << std::endl;
		//std::cout << "mutation!" << std::endl;
		currentIndex = chromIndex;
		popcurrent = &popnext[chromIndex];
	}
}