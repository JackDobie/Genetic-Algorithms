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
		if (mutating)
		{
			mutating = false;
			currentIndex = -1;
		}
		else if (++currentIndex > POP_SIZE)
		{
			Mutation();
		}
	}
	
	if (currentIndex == -1)
	{
		for (int i = 0; i < POP_SIZE; i++)
		{
			popnext[i] = popcurrent[i];
		}

		PickChroms();
		Crossover();
		//Mutation();

		for (int i = 0; i < POP_SIZE; i++)
		{
			popcurrent[i] = popnext[i];
		}
	}
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
			popcurrent[i].bit[j] = random;
			random = rand() % BOARD_WIDTH;
			popcurrent[i].bitPosX[j] = random;
			random = rand() % BOARD_HEIGHT;
			popcurrent[i].bitPosY[j] = random;
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
	for (int i = 0; i <= (POP_SIZE / 2); i++)
	{
		for (int j = 0; j <= (POP_SIZE / 2); j++)
		{
			if (popcurrent[i + 1].fit > popcurrent[i].fit)
			{
				std::cout << "new chroms picked: " << popcurrent[i + 1].fit - popcurrent[i].fit << std::endl;
				temp = popcurrent[i + 1];
				popcurrent[i + 1] = popcurrent[i];
				popcurrent[i] = temp;
			}
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
		int random = (rand() % CHROM_BITS) + 1;

		for (int i = 0; i < random; i++) // crossing bits below the cross point
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

		//chrom pops[POP_SIZE];
		//for (int i = 0; i < POP_SIZE; i++)
		//{
		//	pops[i] = popnext[i];
		//}

		//// cross over bits
		//for (int i = 0; i < POP_SIZE; i += 2)
		//{
		//	/*std::cout << i << std::endl;
		//	for (int i = 0; i < POP_SIZE; i++)
		//	{
		//		for (int j = 0; j < CHROM_BITS; j++)
		//		{
		//			std::cout << popnext[i].bit[j];
		//		}
		//		std::cout << std::endl;
		//	}*/

		//	for (int j = 0; j < CHROM_BITS; j++)
		//	{
		//		if (j >= midpoint)
		//		{
		//			short tempBit = pops[i].bit[j];
		//			pops[i].bit[j] = pops[i + 1].bit[j];
		//			pops[i + 1].bit[j] = tempBit;
		//		}
		//	}

		//	/*std::cout << std::endl;
		//	for (int i = 0; i < POP_SIZE; i++)
		//	{
		//		for (int j = 0; j < CHROM_BITS; j++)
		//		{
		//			std::cout << pops[i].bit[j];
		//		}
		//		std::cout << std::endl;
		//	}*/
		//}

		//for (int i = 0; i < POP_SIZE; i++)
		//{
		//	popnext[i] = pops[i];
		//}
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
		mutating = true;
	}
	else
	{
		currentIndex = -1;
	}
}