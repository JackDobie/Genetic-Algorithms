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
	for (int i = 0; i < POP_SIZE; i++)
	{
		popnext[i] = popcurrent[i];
	}

	PickChroms();
	Crossover();
	Mutation();

	for (int i = 0; i < POP_SIZE; i++)
	{
		popcurrent[i] = popnext[i];
	}
}

void GA::SetCurrentScore(int score)
{
	for (chrom c : popcurrent)
	{
		c.fit = score;
	}
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
	for (int i = 0; i < POP_SIZE - 1; i++)
	{
		if (popnext[i + 1].fit > popnext[i].fit)
		{
			temp = popnext[i + 1];
			popnext[i + 1] = popnext[i];
			popnext[i] = temp;
			std::cout << "new chroms picked" << std::endl;
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
		//int random = (rand() % POP_SIZE) + 1;

		// split popnext into two halfs by looping through and comparing index to half of pop size
		//int midpoint = POP_SIZE / 2;
		//chrom firsthalf[midpoint];
		chrom pops[POP_SIZE];
		for (int i = 0; i < POP_SIZE; i++)
		{
			pops[i] = popnext[i];
			/*for (int j = 0; j < CHROM_BITS; j++)
			{
				if (j > midpoint)
				{
					int index = j % midpoint;
					secondhalf[i] = popnext[j];
				}
			}*/
		}

		// cross over bits

		//for (int i = 0; i < random; i++)
		//{
		//	for (int j = 0; j < midpoint; j++)
		//	{
		//		secondhalf[j].bit[i] = firsthalf[j].bit[i];
		//	}
		//	//secondhalf[0].bit[i] = firsthalf[0].bit[i];
		//	//secondhalf[1].bit[i] = firsthalf[1].bit[i];
		//}

		// loops through secondhalf
		for (int i = 0; i < POP_SIZE; i += 2)
		{
			short tempBits[CHROM_BITS];
			for (int j = 0; j < CHROM_BITS; j++)
			{
				if (j > midpoint)
				{
					tempBits[j] = pops[i].bit[j];
					pops[i].bit[j] == pops[i + 1].bit[j];
					pops[i + 1].bit[j] = tempBits[j];
				}
			}
			//
			//for (int j = 0; j < POP_SIZE; j += 2)
			//{
			//	secondhalf[i].bit
			//	//= firsthalf[j].bit[i];
			//	//secondhalf[j].bit[i] = firsthalf[j].bit[i];
			//}
		}

		for (int i = 0; i < POP_SIZE; i++)
		{
			//if (i < midpoint)
			//{
			//	popnext[i] = firsthalf[i];
			//}
			//else
			//{
			//	int index = i % midpoint;
			//	popnext[i] = secondhalf[midpoint + index];
			//}
			popnext[i] = pops[i];
		}
	}
}

void GA::Mutation()
{
	int random = rand() % 50;

	if (random == 10)
	{
		int col = rand() % CHROM_BITS;
		int row = rand() % POP_SIZE;
		// randomise bit
		popnext[row].bit[col] = (rand() % towerBit::thrower) + 1;

		std::cout << "mutation!" << std::endl;
	}
}