#include "GA.h"

GA::GA()
{
	evpop(popcurrent);
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

	PickChroms(popnext);
	Crossover(popnext);
	Mutation(popnext);

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

void GA::evpop(chrom popcurrent[POP_SIZE])
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

void GA::PickChroms(chrom popcurrent[POP_SIZE])
{
	chrom temp;
	for (int i = 0; i < (POP_SIZE - 1); i++)
	{
		if (popcurrent[i + 1].fit > popcurrent[i].fit)
		{
			temp = popcurrent[i + 1];
			popcurrent[i + 1] = popcurrent[i];
			popcurrent[i] = temp;
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

void GA::Crossover(chrom popnext[POP_SIZE])
{
	int random = (rand() % POP_SIZE) + 1;

	int midpoint = POP_SIZE / 2;
	chrom firsthalf[POP_SIZE / 2];
	chrom secondhalf[POP_SIZE / 2];
	for (int i = 0; i < POP_SIZE; i++)
	{
		if (i < midpoint)
		{
			firsthalf[i] = popnext[i];
		}
		else
		{
			int index = i % midpoint;
			secondhalf[index] = popnext[i];
		}
	}

	for (int i = 0; i < random; i++)
	{
		secondhalf[0].bit[i] = firsthalf[0].bit[i];
		secondhalf[1].bit[i] = firsthalf[1].bit[i];
	}

	for (int i = random; i < CHROM_BITS; i++)
	{
		secondhalf[0].bit[i] = firsthalf[1].bit[i];
		secondhalf[1].bit[i] = firsthalf[0].bit[i];
	}

	for (int i = 0; i < POP_SIZE; i++)
	{
		if (i < midpoint)
		{
			popnext[i] = firsthalf[i];
		}
		else
		{
			int index = i % midpoint;
			popnext[i] = secondhalf[midpoint + index];
		}
	}

	/*for (int i = 0; i < POP_SIZE; i++)
	{
		popnext[i].fit = y(x(popnext[i]));
	}*/

	//for (int i = 0; i < POP_SIZE; i++)
	//{
		//std::cout << "popcurrent[" << i << "] "/*Value: " << x(popnext[i])*/ << ", Fitness = " << popcurrent[i].fit;
		//printf("\nCrossOver popnext[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i, popnext[i].bit[5], popnext[i].bit[4], popnext[i].bit[3], popnext[i].bit[2], popnext[i].bit[1], popnext[i].bit[0], x(popnext[i]), popnext[i].fit);
	//}
}

void GA::Mutation(chrom popnext[POP_SIZE])
{
	int random = rand() % 20;

	if (random == 10)
	{
		int col = rand() % CHROM_BITS;
		int row = rand() % POP_SIZE;

		popnext[row].bit[col] = (rand() % towerBit::thrower) + 1;

		std::cout << "mutation!" << std::endl;

		//if (popnext[row].bit[col] == 0) // invert the bit
		//{
		//	popnext[row].bit[col] = 1;
		//}
		//else if (popnext[row].bit[col] == 1)
		//{
		//	popnext[row].bit[col] = 0;
		//}

		//popnext[row].fit = y(x(popnext[row]));
		//int value = x(popnext[row]);
		//std::cout << "Mutation occurred in popnext[" << row << "] "/*Value: " << value*/ << " Fitness : " << popnext[row].fit;
		//printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   fitness = % d", row, col, popnext[row].bit[5], popnext[row].bit[4], popnext[row].bit[3], popnext[row].bit[2], popnext[row].bit[1], popnext[row].bit[0], value, popnext[row].fit);
	}
}